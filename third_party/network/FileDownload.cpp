#include "FileDownload.h"
#include <curl/curl.h>

namespace network {

typedef std::lock_guard<std::mutex> LockHolder;


// CurlDownloadManager -------------------------------------------------------------------

CurlDownloadManager::CurlDownloadManager()
    : m_curlMultiHandle(0)
    , m_runThread(false)
{
    curl_global_init(CURL_GLOBAL_ALL);
    m_curlMultiHandle = curl_multi_init();
}

CurlDownloadManager::~CurlDownloadManager()
{
    stopThread();
    curl_multi_cleanup(m_curlMultiHandle);
    curl_global_cleanup();
}

bool CurlDownloadManager::add(CURL* curlHandle)
{
    {
        LockHolder locker(m_mutex);
        m_pendingHandleList.push_back(curlHandle);
    }

    startThreadIfNeeded();

    return true;
}

bool CurlDownloadManager::remove(CURL* curlHandle)
{
    LockHolder locker(m_mutex);

    m_removedHandleList.push_back(curlHandle);

    return true;
}

int CurlDownloadManager::getActiveDownloadCount() const
{
    LockHolder locker(m_mutex);
    return m_activeHandleList.size();
}

int CurlDownloadManager::getPendingDownloadCount() const
{
    LockHolder locker(m_mutex);
    return m_pendingHandleList.size();
}

void CurlDownloadManager::startThreadIfNeeded()
{
    if (!runThread()) {
        if (m_thread) {
            m_thread->join();
            m_thread = nullptr;
        }
        setRunThread(true);
        m_thread.reset(new std::thread(std::bind(&CurlDownloadManager::downloadThread, this)));
    }
}

void CurlDownloadManager::stopThread()
{
    setRunThread(false);
    if (m_thread) {
        m_thread->join();
        m_thread = nullptr;
    }
}

void CurlDownloadManager::stopThreadIfIdle()
{
    if (!getActiveDownloadCount() && !getPendingDownloadCount())
        setRunThread(false);
}

void CurlDownloadManager::updateHandleList()
{
    LockHolder locker(m_mutex);

    // Remove curl easy handles from multi list 
    int size = m_removedHandleList.size();
    for (int i = 0; i < size; i++) {
        removeFromCurl(m_removedHandleList[0]);
        m_removedHandleList.erase(m_removedHandleList.begin());
    }

    // Add pending curl easy handles to multi list 
    size = m_pendingHandleList.size();
    for (int i = 0; i < size; i++) {
        addToCurl(m_pendingHandleList[0]);
        m_pendingHandleList.erase(m_pendingHandleList.begin());
    }
}

bool CurlDownloadManager::addToCurl(CURL* curlHandle)
{
    CURLMcode retval = curl_multi_add_handle(m_curlMultiHandle, curlHandle);
    if (retval == CURLM_OK) {
        m_activeHandleList.push_back(curlHandle);
        return true;
    }
    return false;
}

bool CurlDownloadManager::removeFromCurl(CURL* curlHandle)
{
    auto handlePos = m_activeHandleList.end();
    for (auto itr = m_activeHandleList.begin(); itr != m_activeHandleList.end(); ++itr) {
        if (*itr == curlHandle) {
            handlePos == itr;
            break;
        }
    }

    if (handlePos == m_activeHandleList.end())
        return true;

    CURLMcode retval = curl_multi_remove_handle(m_curlMultiHandle, curlHandle);
    if (retval == CURLM_OK) {
        m_activeHandleList.erase(handlePos);
        curl_easy_cleanup(curlHandle);
        return true;
    }
    return false;
}

void CurlDownloadManager::downloadThread()
{
    CurlDownloadManager* downloadManager = this;

    while (downloadManager->runThread()) {

        downloadManager->updateHandleList();

        // Retry 'select' if it was interrupted by a process signal.
        int rc = 0;
        do {
            fd_set fdread;
            fd_set fdwrite;
            fd_set fdexcep;

            int maxfd = 0;

            const int selectTimeoutMS = 5;

            struct timeval timeout;
            timeout.tv_sec = 0;
            timeout.tv_usec = selectTimeoutMS * 1000; // select waits microseconds

            FD_ZERO(&fdread);
            FD_ZERO(&fdwrite);
            FD_ZERO(&fdexcep);
            curl_multi_fdset(downloadManager->getMultiHandle(), &fdread, &fdwrite, &fdexcep, &maxfd);
            // When the 3 file descriptors are empty, winsock will return -1
            // and bail out, stopping the file download. So make sure we
            // have valid file descriptors before calling select.
            if (maxfd >= 0)
                rc = ::select(maxfd + 1, &fdread, &fdwrite, &fdexcep, &timeout);
        } while (rc == -1 && errno == EINTR);

        int activeDownloadCount = 0;
        while (curl_multi_perform(downloadManager->getMultiHandle(), &activeDownloadCount) == CURLM_CALL_MULTI_PERFORM) {}

        int messagesInQueue = 0;
        CURLMsg* msg = curl_multi_info_read(downloadManager->getMultiHandle(), &messagesInQueue);

        if (!msg)
            continue;

        CurlDownload* download = 0;
        CURLcode err = curl_easy_getinfo(msg->easy_handle, CURLINFO_PRIVATE, &download);

        if (msg->msg == CURLMSG_DONE) {
            if (download) {
                if (msg->data.result == CURLE_OK) {
                    download->didFinish();
                    download->Release(); // This matches the ref() in CurlDownload::start().
                }
                else {
                    download->didFail();
                    download->Release(); // This matches the ref() in CurlDownload::start().
                }
            }
            downloadManager->removeFromCurl(msg->easy_handle);
        }

        downloadManager->stopThreadIfIdle();
    }
}

// CurlDownload --------------------------------------------------------------------------

CurlDownloadManager CurlDownload::m_downloadManager;


RefCountedPtr<CurlDownload> CurlDownload::create(CurlDownloadListener* listener,
    const std::string& url, const std::string& path) {
    RefCountedPtr<CurlDownload> download = new RefCountedObject<CurlDownload>();
    download->init(listener, url, path);
    return download;
}

CurlDownload::CurlDownload()
    : m_curlHandle(nullptr)
    , m_customHeaders(nullptr)
    , m_tempHandle(nullptr)
    , m_deletesFileUponFailure(false)
    , m_listener(nullptr)
{
}


CurlDownload::~CurlDownload()
{
    {
        LockHolder locker(m_mutex);

        if (m_customHeaders)
            curl_slist_free_all(m_customHeaders);
    }

    closeFile();
    moveFileToDestination();
}

void CurlDownload::init(CurlDownloadListener* listener, const std::string& url,const std::string& path)
{
    if (!listener)
        return;

    LockHolder locker(m_mutex);

    m_curlHandle = curl_easy_init();
    m_url = url;
    m_destination = path;

    //httpsÑéÖ¤
    curl_easy_setopt(m_curlHandle, CURLOPT_SSL_VERIFYPEER, 0);
    curl_easy_setopt(m_curlHandle, CURLOPT_SSL_VERIFYHOST, 0);

    curl_easy_setopt(m_curlHandle, CURLOPT_URL, m_url.c_str());
    curl_easy_setopt(m_curlHandle, CURLOPT_PRIVATE, this);
    curl_easy_setopt(m_curlHandle, CURLOPT_WRITEFUNCTION, writeCallback);
    curl_easy_setopt(m_curlHandle, CURLOPT_WRITEDATA, this);
    curl_easy_setopt(m_curlHandle, CURLOPT_HEADERFUNCTION, headerCallback);
    curl_easy_setopt(m_curlHandle, CURLOPT_WRITEHEADER, this);
    curl_easy_setopt(m_curlHandle, CURLOPT_FOLLOWLOCATION, 1);
    curl_easy_setopt(m_curlHandle, CURLOPT_MAXREDIRS, 10);
    curl_easy_setopt(m_curlHandle, CURLOPT_HTTPAUTH, CURLAUTH_ANY);

    //const char* certPath = getenv("CURL_CA_BUNDLE_PATH");
    //if (certPath)
    //    curl_easy_setopt(m_curlHandle, CURLOPT_CAINFO, certPath);

    //CURLSH* curlsh = ResourceHandleManager::sharedInstance()->getCurlShareHandle();
    //if (curlsh)
    //    curl_easy_setopt(m_curlHandle, CURLOPT_SHARE, curlsh);

    m_listener = listener;
}

bool CurlDownload::start()
{
    AddRef(); // CurlDownloadManager::downloadThread will call deref when the download has finished.
    return m_downloadManager.add(m_curlHandle);
}

bool CurlDownload::cancel()
{
    return m_downloadManager.remove(m_curlHandle);
}

std::string CurlDownload::getTempPath() const
{
    LockHolder locker(m_mutex);
    return m_tempPath;
}

std::string CurlDownload::getUrl() const
{
    LockHolder locker(m_mutex);
    return m_url;
}

void CurlDownload::closeFile()
{
    LockHolder locker(m_mutex);

    if (m_tempHandle != nullptr) {
        fclose(m_tempHandle);
        m_tempHandle = nullptr;
    }
}

void CurlDownload::moveFileToDestination()
{
    LockHolder locker(m_mutex);

    if (m_destination.empty())
        return;

    moveFile(m_tempPath.c_str(), m_destination.c_str());
}

void CurlDownload::writeDataToFile(const char* data, int size)
{
    if (m_tempPath.empty()) {
        m_tempPath = openTemporaryFile(m_destination);
        m_tempHandle = openFile(m_tempPath.c_str(), "wb");
    }

    if (m_tempHandle != nullptr)
        fwrite(data, size,1 ,m_tempHandle);
}

void CurlDownload::addHeaders(const HeaderMap& header)
{
    LockHolder locker(m_mutex);

    if (!header.empty()) {
        struct curl_slist* headers = nullptr;
        for (HeaderMap::const_iterator it = header.begin(); it != header.end(); ++it) {
            const std::string& value = it->second;
            std::string headerString(it->first);
            if (value.empty())
                // Insert the ; to tell curl that this header has an empty value.
                headerString.append(";");
            else {
                headerString.append(": ");
                headerString.append(value);
            }
            headers = curl_slist_append(headers, headerString.c_str());
        }

        if (headers) {
            curl_easy_setopt(m_curlHandle, CURLOPT_HTTPHEADER, headers);
            m_customHeaders = headers;
        }
    }
}

void CurlDownload::didReceiveHeader(const std::string& header)
{

}

void CurlDownload::didReceiveData(void* data, int size)
{
    LockHolder locker(m_mutex);

    RefCountedPtr<CurlDownload> protectedThis(this);
    didReceiveDataOfLength(size);
    writeDataToFile(static_cast<const char*>(data), size);
}

void CurlDownload::didReceiveResponse()
{
    if (m_listener)
        m_listener->didReceiveResponse();
}

void CurlDownload::didReceiveDataOfLength(int size)
{
    if (m_listener)
        m_listener->didReceiveDataOfLength(size);
}

void CurlDownload::didFinish()
{
    closeFile();
    moveFileToDestination();

    if (m_listener)
        m_listener->didFinish();
}

void CurlDownload::didFail()
{
    closeFile();

    LockHolder locker(m_mutex);

    if (m_deletesFileUponFailure)
        deleteFile(m_tempPath.c_str());

    if (m_listener)
        m_listener->didFail();
}

size_t CurlDownload::writeCallback(void* ptr, size_t size, size_t nmemb, void* data)
{
    size_t totalSize = size * nmemb;
    CurlDownload* download = reinterpret_cast<CurlDownload*>(data);

    if (download)
        download->didReceiveData(ptr, totalSize);

    return totalSize;
}

size_t CurlDownload::headerCallback(char* ptr, size_t size, size_t nmemb, void* data)
{
    size_t totalSize = size * nmemb;
    CurlDownload* download = reinterpret_cast<CurlDownload*>(data);

    std::string header(static_cast<const char*>(ptr), totalSize);

    if (download)
        download->didReceiveHeader(header);

    return totalSize;
}

void CurlDownload::downloadFinishedCallback(CurlDownload* download)
{
    if (download)
        download->didFinish();
}

void CurlDownload::downloadFailedCallback(CurlDownload* download)
{
    if (download)
        download->didFail();
}

void CurlDownload::receivedDataCallback(CurlDownload* download, int size)
{
    if (download)
        download->didReceiveDataOfLength(size);
}

void CurlDownload::receivedResponseCallback(CurlDownload* download)
{
    if (download)
        download->didReceiveResponse();
}

}


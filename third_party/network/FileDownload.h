#ifndef CurlDownload_h
#define CurlDownload_h

#include <mutex>
#include <thread>
#include <vector>
#include <memory>
#include <string>
#include <map>
#include "RefCount.h"
#include "FileUtil.h"
#include "RateTracker.h"

typedef void CURLM;
typedef void CURL;
struct curl_slist;

namespace network {

class CurlDownloadManager {
public:
    CurlDownloadManager();
    ~CurlDownloadManager();

    bool add(CURL* curlHandle);
    bool remove(CURL* curlHandle);

    int getActiveDownloadCount() const;
    int getPendingDownloadCount() const;

private:
    void startThreadIfNeeded();
    void stopThread();
    void stopThreadIfIdle();

    void updateHandleList();

    CURLM* getMultiHandle() const { return m_curlMultiHandle; }

    bool runThread() const { std::lock_guard<std::mutex> locker(m_mutex); return m_runThread; }
    void setRunThread(bool runThread) { std::lock_guard<std::mutex> locker(m_mutex); m_runThread = runThread; }

    bool addToCurl(CURL* curlHandle);
    bool removeFromCurl(CURL* curlHandle);

    void downloadThread();

    std::unique_ptr<std::thread> m_thread;
    CURLM* m_curlMultiHandle;
    std::vector<CURL*> m_pendingHandleList;
    std::vector<CURL*> m_activeHandleList;
    std::vector<CURL*> m_removedHandleList;
    mutable std::mutex m_mutex;
    bool m_runThread;
};

class CurlDownloadListener {
public:
    virtual void didProgress(int total,int size) { }
    virtual void didFinish() { }
    virtual void didFail() { }
};

typedef std::map<std::string, std::string> HeaderMap;

class CurlDownload : public RefCountedBase {
public:
    CurlDownload();
    ~CurlDownload();

    static RefCountedPtr<CurlDownload> create(CurlDownloadListener*, 
        const std::string& url, const std::string& path);

    void init(CurlDownloadListener*, const std::string& url, const std::string& path);

    void setListener(CurlDownloadListener* listener) { m_listener = listener; }

    bool start();
    bool cancel();

    std::string getTempPath() const;
    std::string getUrl() const;
    std::string getDestination() const;

    bool deletesFileUponFailure() const { return m_deletesFileUponFailure; }
    void setDeletesFileUponFailure(bool deletesFileUponFailure) { m_deletesFileUponFailure = deletesFileUponFailure; }

private:
    void closeFile();
    void moveFileToDestination();
    void writeDataToFile(const char* data, int size);

    void addHeaders(const HeaderMap&);

    // Called on download thread.
    void didReceiveHeader(const std::string& header);
    void didReceiveData(void* data, int size);


    void didReceiveDataOfLength(int size);
    void didFinish();
    void didFail();

    static size_t writeCallback(void* ptr, size_t, size_t nmemb, void* data);
    static size_t headerCallback(char* ptr, size_t, size_t nmemb, void* data);

    static void downloadFinishedCallback(CurlDownload*);
    static void downloadFailedCallback(CurlDownload*);

    CURL* m_curlHandle;
    curl_slist* m_customHeaders;
    std::string m_url;
    std::string m_tempPath;
    std::string m_destination;
    FILE* m_tempHandle;
    bool m_deletesFileUponFailure;
    mutable std::mutex m_mutex;
    CurlDownloadListener *m_listener;
    int m_fileSize;
    int m_download;
    RateTracker m_rateTracker;

    static CurlDownloadManager m_downloadManager;

    friend class CurlDownloadManager;
};



}//namespace

#endif


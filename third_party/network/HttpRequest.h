#pragma once
#include <string>
#include <vector>
#include <functional>
#include "RefCount.h"

/**
 * @addtogroup network
 * @{
 */

namespace network {

class HttpClient;
class HttpResponse;

typedef std::function<void(HttpClient* client, HttpResponse* response)> ccHttpRequestCallback;


/**
 * Defines the object which users must packed for HttpClient::send(HttpRequest*) method.
 * Please refer to tests/test-cpp/Classes/ExtensionTest/NetworkTest/HttpClientTest.cpp as a sample
 * @since v2.0.2
 *
 * @lua NA
 */

class HttpRequest : public RefCountedBase
{
public:
    /**
     * The HttpRequest type enum used in the HttpRequest::setRequestType.
     */
    enum class Type
    {
        kGET,
        kPOST,
        kPUT,
        kDELETE,
        kUNKNOWN,
    };

    /**
     *  Constructor.
     *   Because HttpRequest object will be used between UI thead and network thread,
         requestObj->autorelease() is forbidden to avoid crashes in AutoreleasePool
         new/retain/release still works, which means you need to release it manually
         Please refer to HttpRequestTest.cpp to find its usage.
     */
    HttpRequest()
    : _requestType(Type::kGET)
    , _pCallback(nullptr)
    , _pUserData(nullptr)
    {
    }

    /** Destructor. */
    virtual ~HttpRequest()
    {
    }

    // setter/getters for properties

    /**
     * Set request type of HttpRequest object before being sent,now it support the enum value of HttpRequest::Type.
     *
     * @param type the request type.
     */
    inline void setRequestType(Type type)
    {
        _requestType = type;
    }

    /**
     * Get the request type of HttpRequest object.
     *
     * @return HttpRequest::Type.
     */
    inline Type getRequestType() const
    {
        return _requestType;
    }

    /**
     * Set the url address of HttpRequest object.
     * The url value could be like these: "http://httpbin.org/ip" or "https://httpbin.org/get"
     *
     * @param url the string object.
     */
    inline void setUrl(const std::string& url)
    {
        _url = url;
    }

    /**
     * Get the url address of HttpRequest object.
     *
     * @return const char* the pointer of _url.
     */
    inline const char* getUrl() const
    {
        return _url.c_str();
    }

    /**
     * Set the request data of HttpRequest object.
     *
     * @param buffer the buffer of request data, it support binary data.
     * @param len    the size of request data.
     */
    inline void setRequestData(const char* buffer, size_t len)
    {
        _requestData.assign(buffer, buffer + len);
    }

    /**
     * Get the request data pointer of HttpRequest object.
     *
     * @return char* the request data pointer.
     */
    inline char* getRequestData()
    {
        if(!_requestData.empty())
            return _requestData.data();

        return nullptr;
    }

    /**
     * Get the size of request data
     *
     * @return ssize_t the size of request data
     */
    inline size_t getRequestDataSize() const
    {
        return _requestData.size();
    }

    /**
     * Set a string tag to identify your request.
     * This tag can be found in HttpResponse->getHttpRequest->getTag().
     *
     * @param tag the string object.
     */
    inline void setTag(const std::string& tag)
    {
        _tag = tag;
    }

    /**
     * Get the string tag to identify the request.
     * The best practice is to use it in your MyClass::onMyHttpRequestCompleted(sender, HttpResponse*) callback.
     *
     * @return const char* the pointer of _tag
     */
    inline const char* getTag() const
    {
        return _tag.c_str();
    }

    /**
     * Set user-customed data of HttpRequest object.
     * You can attach a customed data in each request, and get it back in response callback.
     * But you need to new/delete the data pointer manully.
     *
     * @param pUserData the string pointer
     */
    inline void setUserData(void* pUserData)
    {
        _pUserData = pUserData;
    }

    /**
     * Get the user-customed data pointer which were pre-setted.
     * Don't forget to delete it. HttpClient/HttpResponse/HttpRequest will do nothing with this pointer.
     *
     * @return void* the pointer of user-customed data.
     */
    inline void* getUserData() const
    {
        return _pUserData;
    }

    /**
     * Set response callback function of HttpRequest object.
     * When response come back, we would call _pCallback to process response data.
     *
     * @param callback the ccHttpRequestCallback function.
     */
    inline void setResponseCallback(const ccHttpRequestCallback& callback)
    {
        _pCallback = callback;
    }

    /**
     * Get ccHttpRequestCallback callback function.
     *
     * @return const ccHttpRequestCallback& ccHttpRequestCallback callback function.
     */
    inline const ccHttpRequestCallback& getCallback() const
    {
        return _pCallback;
    }

    /**
     * Set custom-defined headers.
     *
     * @param pHeaders the string vector of custom-defined headers.
     */
    inline void setHeaders(const std::vector<std::string>& headers)
       {
           _headers = headers;
       }

    /**
     * Get custom headers.
     *
     * @return std::vector<std::string> the string vector of custom-defined headers.
     */
    inline std::vector<std::string> getHeaders() const
    {
        return _headers;
    }

    REF_IMPLEMENT_COUNTING(HttpRequest);
protected:
    // properties
    Type                        _requestType;    /// kHttpRequestGet, kHttpRequestPost or other enums
    std::string                 _url;            /// target url that this request is sent to
    std::vector<char>           _requestData;    /// used for POST
    std::string                 _tag;            /// user defined tag, to identify different requests in response callback
    ccHttpRequestCallback       _pCallback;      /// C++11 style callbacks
    void*                       _pUserData;      /// You can add your customed data here
    std::vector<std::string>    _headers;              /// custom http headers
};

typedef RefCountedPtr<HttpRequest> HttpRequestPtr;

}


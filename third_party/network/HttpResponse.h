#pragma once
#include "HttpRequest.h"
#include "RefCount.h"

namespace network {

/**
 * @brief defines the object which users will receive at onHttpCompleted(sender, HttpResponse) callback.
 * Please refer to samples/TestCpp/Classes/ExtensionTest/NetworkTest/HttpClientTest.cpp as a sample.
 * @since v2.0.2.
 * @lua NA
 */
class HttpResponse : public RefCountedBase
{
public:
    /**
     * Constructor, it's used by HttpClient internal, users don't need to create HttpResponse manually.
     * @param request the corresponding HttpRequest which leads to this response.
     */
    HttpResponse(HttpRequestPtr request)
    : _pHttpRequest(request)
    , _succeed(false)
    {

    }

    /**
     * Destructor, it will be called in HttpClient internal.
     * Users don't need to destruct HttpResponse object manually.
     */
    virtual ~HttpResponse()
    {
    }

    // getters, will be called by users

    /**
     * Get the corresponding HttpRequest object which leads to this response.
     * There's no paired setter for it, because it's already setted in class constructor
     * @return HttpRequest* the corresponding HttpRequest object which leads to this response.
     */
    inline HttpRequest* getHttpRequest() const
    {
        return _pHttpRequest;
    }

    /**
     * To see if the http request is returned successfully.
     * Although users can judge if (http response code = 200), we want an easier way.
     * If this getter returns false, you can call getResponseCode and getErrorBuffer to find more details.
     * @return bool the flag that represent whether the http request return successfully or not.
     */
    inline bool isSucceed() const
    {
        return _succeed;
    };

    /**
     * Get the http response data.
     * @return std::vector<char>* the pointer that point to the _responseData.
     */
    inline std::vector<char>* getResponseData()
    {
        return &_responseData;
    }

    /**
     * Get the response headers.
     * @return std::vector<char>* the pointer that point to the _responseHeader.
     */
    inline std::vector<char>* getResponseHeader()
    {
        return &_responseHeader;
    }

    /**
     * Get the http response code to judge whether response is successful or not.
     * I know that you want to see the _responseCode is 200.
     * If _responseCode is not 200, you should check the meaning for _responseCode by the net.
     * @return long the value of _responseCode
     */
    inline long getResponseCode() const
    {
        return _responseCode;
    }

    /**
     * Get the error buffer which will tell you more about the reason why http request failed.
     * @return const char* the pointer that point to _errorBuffer.
     */
    inline const char* getErrorBuffer() const
    {
        return _errorBuffer.c_str();
    }

    // setters, will be called by HttpClient
    // users should avoid invoking these methods


    /**
     * Set whether the http request is returned successfully or not,
     * This setter is mainly used in HttpClient, users mustn't set it directly
     * @param value the flag represent whether the http request is successful or not.
     */
    inline void setSucceed(bool value)
    {
        _succeed = value;
    }

    /**
     * Set the http response data buffer, it is used by HttpClient.
     * @param data the pointer point to the response data buffer.
     */
    inline void setResponseData(std::vector<char>* data)
    {
        _responseData = *data;
    }

    /**
     * Set the http response headers buffer, it is used by HttpClient.
     * @param data the pointer point to the response headers buffer.
     */
    inline void setResponseHeader(std::vector<char>* data)
    {
        _responseHeader = *data;
    }


    /**
     * Set the http response code.
     * @param value the http response code that represent whether the request is successful or not.
     */
    inline void setResponseCode(long value)
    {
        _responseCode = value;
    }


    /**
     * Set the error buffer which will tell you more the reason why http request failed.
     * @param value a string pointer that point to the reason.
     */
    inline void setErrorBuffer(const char* value)
    {
        _errorBuffer.clear();
        _errorBuffer.assign(value);
    }


    REF_IMPLEMENT_COUNTING(HttpResponse);
protected:
    // properties
    HttpRequestPtr      _pHttpRequest;  /// the corresponding HttpRequest pointer who leads to this response
    bool                _succeed;       /// to indicate if the http request is successful simply
    std::vector<char>   _responseData;  /// the returned raw data. You can also dump it as a string
    std::vector<char>   _responseHeader;  /// the returned raw header data. You can also dump it as a string
    long                _responseCode;    /// the status code returned from libcurl, e.g. 200, 404
    std::string         _errorBuffer;   /// if _responseCode != 200, please read _errorBuffer to find the reason

};

typedef RefCountedPtr<HttpResponse> HttpResponsePtr;

}


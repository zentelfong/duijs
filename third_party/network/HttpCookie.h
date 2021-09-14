#pragma once
#include <vector>
#include <string>

namespace network {

struct CookiesInfo
{
    std::string domain;
    bool tailmatch;
    std::string path;
    bool secure;
    std::string name;
    std::string value;
    std::string expires;
};

class HttpCookie
{
public:
    void readFile();

    void writeFile();
    void setCookieFileName(const std::string& fileName);

    const std::vector<CookiesInfo>* getCookies()const;
    const CookiesInfo* getMatchCookie(const std::string& url) const;
    void updateOrAddCookie(CookiesInfo* cookie);

private:
    std::string _cookieFileName;
    std::vector<CookiesInfo> _cookies;
};

}

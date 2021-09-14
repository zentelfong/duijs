#include "HttpCookie.h"
#include <sstream>
#include <stdio.h>

namespace network {

std::string ReadFileString(const std::string& path) {
    FILE* file = fopen(path.c_str(),"rb");
    if (!file) {
        return "";
    }

    fseek(file, 0, SEEK_END);
    int len = ftell(file);
    fseek(file, 0, SEEK_SET);
    std::string str;
    str.resize(len);
    fread(&str[0], len, 1, file);
    fclose(file);
    return str;
}



void HttpCookie::readFile()
{
    std::string inString = ReadFileString(_cookieFileName);
    if(!inString.empty())
    {
        std::vector<std::string> cookiesVec;
        cookiesVec.clear();

        std::stringstream stream(inString);
        std::string item;
        while(std::getline(stream, item, '\n'))
        {
            cookiesVec.push_back(item);
        }

        if(cookiesVec.empty())
            return;

        _cookies.clear();

        for(auto iter = cookiesVec.begin();iter != cookiesVec.end(); iter++)
        {
            std::string cookie = *iter;

            if(cookie.length() == 0)
                continue;

            if(cookie.find("#HttpOnly_") != std::string::npos)
            {
                cookie = cookie.substr(10);
            }

            if(cookie.at(0) == '#')
                continue;

            CookiesInfo co;
            std::stringstream streamInfo(cookie);
            std::vector<std::string> elems;
            std::string elemsItem;

            while (std::getline(streamInfo, elemsItem, '\t'))
            {
                elems.push_back(elemsItem);
            }

            co.domain = elems[0];
            if (co.domain.at(0) == '.')
            {
                co.domain = co.domain.substr(1);
            }
            co.tailmatch = strcmp("TRUE", elems[1].c_str())?true: false;
            co.path   = elems[2];
            co.secure = strcmp("TRUE", elems[3].c_str())?true: false;
            co.expires = elems[4];
            co.name = elems[5];
            co.value = elems[6];
            _cookies.push_back(co);
        }
    }
}

const std::vector<CookiesInfo>* HttpCookie::getCookies() const
{
    return &_cookies;
}

const CookiesInfo* HttpCookie::getMatchCookie(const std::string& url) const
{
    for(auto iter = _cookies.begin(); iter != _cookies.end(); iter++)
    {
        if(url.find(iter->domain) != std::string::npos)
            return &(*iter);
    }

    return nullptr;
}

void HttpCookie::updateOrAddCookie(CookiesInfo* cookie)
{
    for(auto iter = _cookies.begin(); iter != _cookies.end(); iter++)
    {
        if(cookie->domain == iter->domain)
        {
            *iter = *cookie;
            return;
        }
    }
    _cookies.push_back(*cookie);
}

void HttpCookie::writeFile()
{
    FILE *out;
    out = fopen(_cookieFileName.c_str(), "w");
    fputs("# Netscape HTTP Cookie File\n"
          "# http://curl.haxx.se/docs/http-cookies.html\n"
          "# This file was generated by cocos2d-x! Edit at your own risk.\n"
          "# Test cocos2d-x cookie write.\n\n",
          out);

    std::string line;
    for(auto iter = _cookies.begin(); iter != _cookies.end(); iter++)
    {
        line.clear();
        line.append(iter->domain);
        line.append(1, '\t');
        iter->tailmatch ? line.append("TRUE") : line.append("FALSE");
        line.append(1, '\t');
        line.append(iter->path);
        line.append(1, '\t');
        iter->secure ? line.append("TRUE") : line.append("FALSE");
        line.append(1, '\t');
        line.append(iter->expires);
        line.append(1, '\t');
        line.append(iter->name);
        line.append(1, '\t');
        line.append(iter->value);
        //line.append(1, '\n');

        fprintf(out, "%s\n", line.c_str());
    }

    fclose(out);
}

void HttpCookie::setCookieFileName(const std::string& filename)
{
    _cookieFileName = filename;
}

}//namespace 


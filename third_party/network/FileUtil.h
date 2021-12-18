#pragma once
#include <stdio.h>
#include <string>

namespace network {

FILE* openFile(const char* file,const char* mode);

bool deleteFile(const char* file);
bool moveFile(const char* srcfile, const char* destfile);

std::string openTemporaryFile(const std::string& filepath);

}//namespace



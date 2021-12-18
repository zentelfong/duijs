#include "FileUtil.h"

#define WIN32_LEAN_AND_MEAN 1
#include <Windows.h>

namespace network {

std::wstring toUnicode(const std::string& str)
{
	int  len = 0;
	len = str.length();
	int  unicodeLen = ::MultiByteToWideChar(CP_UTF8,
		0,
		str.c_str(),
		-1,
		NULL,
		0);
	wchar_t* pUnicode;
	pUnicode = new  wchar_t[unicodeLen + 1];
	memset(pUnicode, 0, (unicodeLen + 1) * sizeof(wchar_t));
	::MultiByteToWideChar(CP_UTF8,
		0,
		str.c_str(),
		-1,
		(LPWSTR)pUnicode,
		unicodeLen);
	std::wstring  rt;
	rt = (wchar_t*)pUnicode;
	delete[]  pUnicode;
	return  rt;
}

std::string toUtf8(const std::wstring& str)
{
	char* pElementText;
	int    iTextLen;
	// wide char to multi char
	iTextLen = WideCharToMultiByte(CP_UTF8,
		0,
		str.c_str(),
		-1,
		NULL,
		0,
		NULL,
		NULL);
	pElementText = new char[iTextLen + 1];
	memset((void*)pElementText, 0, sizeof(char) * (iTextLen + 1));
	::WideCharToMultiByte(CP_UTF8,
		0,
		str.c_str(),
		-1,
		pElementText,
		iTextLen,
		NULL,
		NULL);
	std::string strText;
	strText = pElementText;
	delete[] pElementText;
	return strText;
}


FILE* openFile(const char* file, const char* mode) {
	std::wstring wfile = toUnicode(file);
	std::wstring wmode = toUnicode(mode);
	return _wfopen(wfile.c_str(), wmode.c_str());
}

bool deleteFile(const char* file) {
	std::wstring wfile = toUnicode(file);
	return !! ::DeleteFileW(wfile.c_str());
}


bool moveFile(const char* srcfile, const char* destfile) {
	std::wstring wsrcfile = toUnicode(srcfile);
	std::wstring wdestfile = toUnicode(destfile);

	return !! ::MoveFileExW(wsrcfile.c_str(), wdestfile.c_str(), 
		MOVEFILE_COPY_ALLOWED | MOVEFILE_REPLACE_EXISTING);
}

std::string openTemporaryFile(const std::string& filepath) {
	if (filepath.empty()) {
		wchar_t buffer[MAX_PATH] = {0};
		wchar_t dest[MAX_PATH] = { 0 };

		GetTempPathW(MAX_PATH,buffer);
		GetTempFileNameW(buffer, L"FILE", 0, dest);
		return toUtf8(dest);
	} else {
		std::wstring wfilepath = toUnicode(filepath);
		std::wstring wtmppath;

		auto find = wfilepath.rfind(L'\\');
		if (find != std::string::npos) {
			wtmppath = wfilepath.substr(find);
		} else {
			wchar_t buffer[MAX_PATH] = { 0 };
			GetTempPathW(MAX_PATH, buffer);
			wtmppath = buffer;
		}

		wchar_t dest[MAX_PATH] = { 0 };
		GetTempFileNameW(wtmppath.c_str(), L"FILE", 0, dest);
		return toUtf8(dest);
	}
}

}//namespace


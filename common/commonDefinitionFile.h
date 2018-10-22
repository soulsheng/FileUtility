
#pragma once 

#include <functional>
#include <vector>
#include <string>
#include <map>

#include <sstream>

#ifdef _UNICODE
#define tstring std::wstring
#define tstream std::wostringstream
#define tstrstr	std::wcsstr
#define tstrcmp	std::wcscmp

#else
#define tstring std::string
#define tstream std::ostringstream
#define tstrstr	std::strstr
#define tstrcmp	std::strcmp

#endif


typedef std::pair<tstring, tstring>	FilesPair;
typedef std::map<tstring, tstring>	FilesMap;



#pragma once 

#include <functional>
#include <algorithm>

#include <vector>
#include <string>
#include <map>

#include <sstream>
#include <fstream>

using namespace std;

#ifdef _UNICODE
#define tstring std::wstring
#define tstream std::wostringstream
#define tstrstr	std::wcsstr
#define tstrcmp	std::wcscmp
#define tfstream std::wfstream

#else
#define tstring std::string
#define tstream std::ostringstream
#define tstrstr	std::strstr
#define tstrcmp	std::strcmp
#define tfstream std::fstream;

#endif

typedef std::vector<tstring>	StringVec;

typedef std::pair<tstring, int>	ClassesPair;
typedef std::map<tstring, int>	ClassesMap;

typedef std::pair<tstring, tstring>	FilesPair;
typedef std::map<tstring, tstring>	FilesMap;


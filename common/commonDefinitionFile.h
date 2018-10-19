
#pragma once 

#include <functional>
#include <vector>
#include <string>
#include <map>

#include <sstream>

#ifdef _UNICODE
#define tstring std::wstring
#define tstream std::wostringstream

#else
#define tstring std::string
#define tstream std::ostringstream

#endif


typedef std::pair<tstring, tstring>	FilesPair;
typedef std::map<tstring, tstring>	FilesMap;


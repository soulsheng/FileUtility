
#pragma once 

#include <vector>
#include <string>
#include <sstream>

#ifdef _UNICODE
#define tstring std::wstring
#define tstream std::wostringstream

#else
#define tstring std::string
#define tstream std::ostringstream

#endif


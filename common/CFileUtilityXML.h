#pragma once
#include "commonDefinitionFile.h"
#include "stdio.h"

class CFileUtilityXML
{
public:
	CFileUtilityXML(){}
	~CFileUtilityXML(){}

public:
	static bool findObjectNames(tstring& file, StringVec& strVec);
	static bool editObjectNames(tstring fileIn, tstring fileOut, tstring str);
};

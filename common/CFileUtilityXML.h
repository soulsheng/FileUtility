#pragma once
#include "commonDefinitionFile.h"
#include "stdio.h"
#include "pugixml.hpp"

class CFileUtilityXML
{
public:
	CFileUtilityXML(tstring& fileXML);
	~CFileUtilityXML(){}

public:
	static bool findObjectNames(tstring& file, StringVec& strVec);
	static bool editObjectNames(tstring fileIn, tstring fileOut, tstring str);
	
	tstring getStringBBox(tstring str = _T("face"));

protected:
	tstring getNodeValueAll(pugi::xml_node node);

protected:
	pugi::xml_document doc;

};

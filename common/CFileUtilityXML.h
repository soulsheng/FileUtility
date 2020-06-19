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
	
	int getStringBBox(tstring str, tstring& line, tstring& line_gt);

protected:
	tstring getNodeValueAll(pugi::xml_node node);
	tstring xy2wh(tstring& val);

protected:
	pugi::xml_document doc;

};

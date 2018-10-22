
#pragma once
#include "commonDefinitionFile.h"

class CFileUtilitySTL
{
public:
	CFileUtilitySTL(){}
	~CFileUtilitySTL(){}

public:
	static tstring getShortFileName(tstring& fullpath);

	static tstring getPathFileName(tstring& fullpath);

	static void		writeFilelist(tstring filename, FilesMap& filesMap);

};
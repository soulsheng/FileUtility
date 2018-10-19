
#pragma once
#include "commonDefinitionFile.h"

class CFileUtilityWIN
{
public:
	CFileUtilityWIN(){}
	~CFileUtilityWIN(){}

public:
	static void CFileUtilityWIN::getFileListFromPath(tstring &path, tstring fmt, std::vector<tstring> &list);

	static void CFileUtilityWIN::getFilePathFromDialog(tstring &path);


};
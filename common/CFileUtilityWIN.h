
#pragma once
#include "commonDefinitionFile.h"

class CFileUtilityWIN
{
public:
	CFileUtilityWIN(){}
	~CFileUtilityWIN(){}

public:
	static void getFileListFromPath(tstring &path, tstring fmt, std::vector<tstring> &list);
	
	static void getFileListFromPathNest(tstring path, tstring pathSub, tstring fmt, std::vector<tstring> &list);

	static void getFilePathFromDialog(tstring &path);


};
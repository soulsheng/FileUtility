
#pragma once
#include "commonDefinitionFile.h"
#include "stdio.h"

class CFileUtilitySTL
{
public:
	CFileUtilitySTL(){}
	~CFileUtilitySTL(){}

public:
	static tstring getShortFileName(tstring& fullpath);

	static tstring getPathFileName(tstring& fullpath);

	static void		writeFilelist(tstring filename, FilesMap& filesMap, int index = -1, bool rewrite = true);

	static bool		readFilelist(tstring filename, StringVec& lines);

	static void		convertList2Map(ClassesMap& classes, StringVec& lines);

	// return 0, success 
	static int		removeFile(tstring filename);

};
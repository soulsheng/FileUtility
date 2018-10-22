#include "stdafx.h"
#include "CFileUtilitySTL.h"

tstring CFileUtilitySTL::getShortFileName(tstring& fullpath)
{
	int indexEnd = fullpath.find_last_of('\\');
	return fullpath.substr(indexEnd + 1);
}

tstring CFileUtilitySTL::getPathFileName(tstring& fullpath)
{
	int indexEnd = fullpath.find_last_of('\\');
	return fullpath.substr(0, indexEnd + 1);
}

void CFileUtilitySTL::writeFilelist(tstring filename, FilesMap& filesMap)
{
	std::locale oNewLocale(std::locale(), "", std::locale::ctype);
	std::locale oPreviousLocale = std::locale::global(oNewLocale);

	tfstream fileOut(filename);

	for (FilesMap::iterator itr = filesMap.begin(); itr != filesMap.end(); itr++)
	{
		fileOut << itr->first << std::endl;
	}

	fileOut.close();
	

	std::locale::global(oPreviousLocale);

}


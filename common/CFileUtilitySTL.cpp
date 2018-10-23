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

void CFileUtilitySTL::writeFilelist(tstring filename, FilesMap& filesMap, int index/* = -1*/, bool rewrite/* = true*/)
{
	std::locale oNewLocale(std::locale(), "", std::locale::ctype);
	std::locale oPreviousLocale = std::locale::global(oNewLocale);

	tfstream fileOut;
		
	if (rewrite)
		fileOut.open(filename, ios::out);
	else
		fileOut.open(filename, ios::out | ios ::app );

	for (FilesMap::iterator itr = filesMap.begin(); itr != filesMap.end(); itr++)
	{
		if (index==-1)
			fileOut << itr->first << std::endl;
		else
			fileOut << itr->first << _T(" ") << index << std::endl;

	}

	fileOut.close();
	

	std::locale::global(oPreviousLocale);

}

bool CFileUtilitySTL::readFilelist(tstring filename, StringVec& lines)
{
	std::locale oNewLocale(std::locale(), "", std::locale::ctype);
	std::locale oPreviousLocale = std::locale::global(oNewLocale);

	tfstream file(filename);

	//检查文件是否打开成功
	if (!file)
	{//如果没成功

		throw runtime_error("file cannot open");
		return false;
	}
	else
	{//文件打开成功，开始进行读文件操作
		tstring s;
		//fstream类中也有getline成员函数，不要弄错
		//getline(infile,s);
		while (!file.eof())
		{
			//infile >> s;
			getline(file, s);
			lines.push_back(s);
		}
	}
	file.close();

	std::locale::global(oPreviousLocale);

	return true;
}

void CFileUtilitySTL::convertList2Map(ClassesMap& classes, StringVec& lines)
{
	int index = 0;
	for (StringVec::iterator itr = lines.begin(); itr != lines.end();itr++)
		classes.insert(ClassesPair(*itr, index++));
	
}

int CFileUtilitySTL::removeFile(tstring filename)
{
	return _tremove(filename.c_str());
}

bool CFileUtilitySTL::generateVal(tstring filename, tstring filenameVal)
{
	std::locale oNewLocale(std::locale(), "", std::locale::ctype);
	std::locale oPreviousLocale = std::locale::global(oNewLocale);

	tfstream file(filename);

	StringVec lines;

	//检查文件是否打开成功
	if (!file)
	{//如果没成功

		throw runtime_error("file cannot open");
		return false;
	}
	else
	{//文件打开成功，开始进行读文件操作
		tstring s;
		//fstream类中也有getline成员函数，不要弄错
		//getline(infile,s);
		while (!file.eof())
		{
			getline(file, s);
			if (s.length()>4)// ignore empty line
				lines.push_back(s);
		}
	}
	file.close();

	std::srand(unsigned(time(0))); 
	random_shuffle(lines.begin(), lines.end());

	tfstream fileVal(filenameVal, ios::out);

	for (StringVec::iterator itr = lines.begin(); itr != lines.end(); itr++)
		fileVal << *itr << std::endl;

	fileVal.close();

	std::locale::global(oPreviousLocale);

	return true;
}


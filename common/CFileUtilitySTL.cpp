#include "stdafx.h"
#include "CFileUtilitySTL.h"

tstring CFileUtilitySTL::getShortFileName(tstring& fullpath)
{
	int indexEnd = fullpath.find_last_of(_T("\\/"));
	return fullpath.substr(indexEnd + 1);
}

tstring CFileUtilitySTL::getOnlyFileName(tstring& fullpath)
{
	tstring shortname = getShortFileName(fullpath);
	int indexEnd = shortname.find_last_of('.');
	return shortname.substr(0, indexEnd);
}

tstring CFileUtilitySTL::getPathFileName(tstring& fullpath)
{
	int indexEnd = fullpath.find_last_of(_T("\\/"));
	return fullpath.substr(0, indexEnd + 1);
}

tstring CFileUtilitySTL::getPathSub(tstring& fullpath, tstring& lastdir)
{
	int indexEnd = fullpath.find(lastdir);
	return fullpath.substr(0, indexEnd );
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

bool CFileUtilitySTL::writeFilelist(tstring filename, StringVec& lines)
{
	std::locale oNewLocale(std::locale(), "", std::locale::ctype);
	std::locale oPreviousLocale = std::locale::global(oNewLocale);

	tfstream fileOut;

	fileOut.open(filename, ios::out);
	if (!fileOut)
	{//如果没成功
		return false;
	}

	for (StringVec::iterator itr = lines.begin(); itr != lines.end(); itr++)
		fileOut << *itr << std::endl;

	fileOut.close();

	std::locale::global(oPreviousLocale);

	return true;
}

bool CFileUtilitySTL::mixStringVec(StringVec& lineMix, StringVec& lines1, StringVec& lines2)
{
	lineMix.clear();

	StringVec::iterator itr1 = lines1.begin();
	StringVec::iterator itr2 = lines2.begin();

	for (; itr1 != lines1.end(); itr1++, itr2++)
	{
		tstring str = *itr1 + _T(" ") + *itr2;
		lineMix.push_back(str);
	}

	return true;
}

bool CFileUtilitySTL::writeFilelist(tstring filename, StringIDMap& lines)
{
	std::locale oNewLocale(std::locale(), "", std::locale::ctype);
	std::locale oPreviousLocale = std::locale::global(oNewLocale);

	tfstream fileOut;

	fileOut.open(filename, ios::out);
	if (!fileOut)
	{//如果没成功
		return false;
	}

	for (StringIDMap::iterator itr = lines.begin(); itr != lines.end(); itr++)
		fileOut << itr->first << _T(" ") << itr->second << std::endl;

	fileOut.close();

	std::locale::global(oPreviousLocale);

	return true;
}

bool CFileUtilitySTL::readFilelist(tstring filename, StringVec& lines)
{
	std::locale oNewLocale(std::locale(), "", std::locale::ctype);
	std::locale oPreviousLocale = std::locale::global(oNewLocale);

	tfstream file(filename);

	//检查文件是否打开成功
	if (!file)
	{//如果没成功

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

bool CFileUtilitySTL::readFilelist(tstring filename, StringIDMap& lines)
{
	std::locale oNewLocale(std::locale(), "", std::locale::ctype);
	std::locale oPreviousLocale = std::locale::global(oNewLocale);

	tfstream file;

	file.open(filename, ios::in);
	if (!file)
	{//如果没成功
		return false;
	}

	tstring s;
	//fstream类中也有getline成员函数，不要弄错
	//getline(infile,s);
	while (!file.eof())
	{
		//infile >> s;
		getline(file, s);

		int indexBlank = s.find_last_of(_T(" "));
		if( -1 == indexBlank)
			continue;
		tstring lastID = s.substr(indexBlank);
		int id = _ttoi(lastID.c_str());
		lines.insert(StringIDPair(s.substr(0, s.find_first_of(_T(" "))), id));
	}

	file.close();

	std::locale::global(oPreviousLocale);

	return true;
}

void CFileUtilitySTL::convertList2Map(StringIDMap& classes, StringVec& lines)
{
	int index = 0;
	for (StringVec::iterator itr = lines.begin(); itr != lines.end();itr++)
		classes.insert(StringIDPair(*itr, index++));
	
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

bool CFileUtilitySTL::copyFilelist(tstring& fromPath, tstring& toPath, StringIDMap& lines)
{
	StringIDMap::iterator itr = lines.begin();

	for (; itr!=lines.end(); itr++)
		copyFile(fromPath + itr->first, toPath + itr->first);

	return true;
}

bool CFileUtilitySTL::copyFilelist(tstring& fromPath, tstring& toPath, StringVec& fromLines, StringVec& toLines)
{
	StringVec::iterator itrFrom = fromLines.begin();
	StringVec::iterator itrTo = toLines.begin();

	for (; itrFrom != fromLines.end(); itrFrom++, itrTo++)
		copyFile(fromPath + *itrFrom, toPath + *itrTo);

	return true;
}

bool CFileUtilitySTL::copyFilelist(tstring& fromPath, tstring& toPath, StringVec& lines)
{
	StringVec::iterator itr = lines.begin();

	for (; itr != lines.end(); itr++)
		copyFile(fromPath + *itr, toPath + *itr);

	return true;
}

bool CFileUtilitySTL::copyFilelistRename(tstring& fromPath, tstring& toPath, StringVec& lines,
	tstring pre, bool rename)
{
	StringVec::iterator itr = lines.begin();

	int baseIndex = 0;
	for (; itr != lines.end(); itr++)
	{
		tsstream  os;
		if (rename)
			os << pre << std::setw(4) << std::setfill(_T('0')) << ++baseIndex << _T(".jpg");
		else
			os << *itr;
		copyFile(fromPath + *itr, toPath + os.str());

	}

	return true;
}

bool CFileUtilitySTL::copyFilelistRename(tstring& fromPath, tstring& toPath, StringIDMap& lines)
{
	StringIDMap::iterator itr = lines.begin();

	for (; itr != lines.end(); itr++)
	{
		tstring filenameNew = unfoldRelativePath(itr->first);

		copyFile(fromPath + itr->first, toPath + filenameNew);

	}

	return true;
}

tstring CFileUtilitySTL::unfoldRelativePath(tstring path)
{
	StringVec resultVec = CFileUtilitySTL::split(path, _T("\\/"));

	tstring pathNew;
	for (StringVec::iterator itr = resultVec.begin(); itr != resultVec.end(); itr++)
	{
		pathNew += _T("-");
		pathNew += *itr;
	}
	return pathNew;
}

bool CFileUtilitySTL::copyFile(tstring& fromPath, tstring& toPath)
{
	// ref: https://www.cnblogs.com/endenvor/p/6819043.html 
	using namespace std;
	ifstream in(fromPath, ios::binary);
	ofstream out(toPath, ios::binary);
	if (!in.is_open()) {
		return false;
	}
	if (!out.is_open()) {
		return false;
	}
	if (fromPath == toPath) {	
		return false;
	}
	char buf[2048];
	long long totalBytes = 0;
	while (in)
	{
		//read从in流中读取2048字节，放入buf数组中，同时文件指针向后移动2048字节
		//若不足2048字节遇到文件结尾，则以实际提取字节读取。
		in.read(buf, 2048);
		//gcount()用来提取读取的字节数，write将buf中的内容写入out流。
		out.write(buf, in.gcount());
		totalBytes += in.gcount();
	}
	in.close();
	out.close();
	return true;
}

StringVec CFileUtilitySTL::split(const tstring &str, const tstring &pattern)
{
	//const char* convert to char*
	TCHAR * strc = new TCHAR[_tcslen(str.c_str()) + 1];
	_tcscpy(strc, str.c_str());
	StringVec resultVec;
	TCHAR* tmpStr = _tcstok(strc, pattern.c_str());
	while (tmpStr != NULL)
	{
		resultVec.push_back(tstring(tmpStr));
		tmpStr = _tcstok(NULL, pattern.c_str());
	}

	delete[] strc;

	return resultVec;
}

bool CFileUtilitySTL::selectLableNoEqualMinusOne(StringIDMap& lines, StringVec& filelist)
{
	StringIDMap::iterator itr = lines.begin();

	for (; itr != lines.end(); itr++)
	{
		if (itr->second != -1)
			filelist.push_back(itr->first);
	}

	return true;
}

bool CFileUtilitySTL::convertString(StringVec& lines, StringVec& linesOut, tstring& prefix, tstring& suffix)
{
	//in:	000695
	//out:	VOC2007/JPEGImages/000695.jpg VOC2007/Annotations/000695.xml
	for (StringVec::iterator itr = lines.begin(); itr != lines.end(); itr++)
	{
		tstring lineNew = prefix + *itr + suffix;
		linesOut.push_back(lineNew);
	}

	return true;
}

tstring CFileUtilitySTL::getFileExt(tstring& fullpath)
{
	int indexEnd = fullpath.find_last_of(_T("."));
	tstring str = fullpath.substr(indexEnd + 1);

	std::transform(str.begin(), str.end(), str.begin(), ::toupper);

	return str;
}
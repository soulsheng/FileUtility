#include "stdafx.h"
#include "CFileUtilityWIN.h"


void CFileUtilityWIN::getFileListFromPath(tstring &path, tstring fmt, std::vector<tstring> &list)
{
	tstring csDirPath = path + _T("*.") + fmt;
	HANDLE file=0;
	WIN32_FIND_DATA fileData;
	char line[1024];
	char fn[1000];
	//mbstowcs(fn,csDirPath.GetBuffer(),999);
	file = FindFirstFile(csDirPath.c_str(), &fileData);
	if (INVALID_HANDLE_VALUE == file)
		return;

	list.push_back(fileData.cFileName);
	bool bState = false;
	bState = FindNextFile(file, &fileData);
	while (bState)
	{
		//wcstombs(line,(const char*)fileData.cFileName,259);
		list.push_back(fileData.cFileName);
		bState = FindNextFile(file, &fileData);
	}

}

void CFileUtilityWIN::getFileListFromPathNest(tstring path, tstring pathSub, tstring fmt, std::vector<tstring> &list)
{
	tstring csDirPath = path + pathSub + _T("\\*.*");// +fmt;
	HANDLE file=0;
	WIN32_FIND_DATA fileData;

	//mbstowcs(fn,csDirPath.GetBuffer(),999);
	file = FindFirstFile(csDirPath.c_str(), &fileData);
	if (INVALID_HANDLE_VALUE == file)
		return;

	do
	{
		if (!(fileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))//判断查找的是不是文件夹，通过位于运算，dwFileAttributes有很多属性
		{
			tstring filename(fileData.cFileName);
			transform(filename.begin(), filename.end(), filename.begin(), toupper);
			transform(fmt.begin(), fmt.end(), fmt.begin(), toupper);

			if (NULL != tstrstr(filename.c_str(), fmt.c_str()))
				list.push_back(pathSub + _T("/") + fileData.cFileName);
		}
		else
		{
			if (!tstrcmp(_T("."), fileData.cFileName) || !tstrcmp(_T(".."), fileData.cFileName) )
				continue;

			tstring pathSubNest = pathSub + _T("/") + fileData.cFileName;
			getFileListFromPathNest(path, pathSubNest, fmt, list);
		}

	} while (FindNextFile(file, &fileData));
	

}

void CFileUtilityWIN::getFilePathFromDialog(tstring &path)
{
	BROWSEINFO bi;
	TCHAR Buffer[MAX_PATH];

	//初始化入口参数bi开始
	bi.hwndOwner = NULL;
	bi.pidlRoot = NULL;//初始化制定的root目录很不容易
	bi.pszDisplayName = Buffer;//此参数如为NULL则不能显示对话框
	bi.lpszTitle = _T("选择路径");
	bi.ulFlags = BIF_EDITBOX;//带编辑框的风格
	bi.lpfn = NULL;
	bi.lParam = 0;
	bi.iImage = 0;
	//初始化入口参数bi结束

	LPITEMIDLIST pIDList = SHBrowseForFolder(&bi);//调用显示选择对话框

	if (pIDList)
	{
		SHGetPathFromIDList(pIDList, Buffer);

		//取得文件夹路径到Buffer里
		path = tstring(Buffer) + _T("\\");
	}


	// free memory used   
	IMalloc * imalloc = 0;
	if (SUCCEEDED(SHGetMalloc(&imalloc)))
	{
		imalloc->Free(pIDList);
		imalloc->Release();
	}
}

void CFileUtilityWIN::getSubPathFromPath(tstring &path, std::vector<tstring> &list)
{
	tstring csDirPath = path + _T("\\*.*");// +fmt;
	HANDLE file = 0;
	WIN32_FIND_DATA fileData;

	//mbstowcs(fn,csDirPath.GetBuffer(),999);
	file = FindFirstFile(csDirPath.c_str(), &fileData);
	if (INVALID_HANDLE_VALUE == file)
		return;

	do
	{
		if (fileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)//判断查找的是不是文件夹，通过位于运算，dwFileAttributes有很多属性
		{

			if (!tstrcmp(_T("."), fileData.cFileName) || !tstrcmp(_T(".."), fileData.cFileName))
				continue;

			list.push_back(fileData.cFileName);
		}

	} while (FindNextFile(file, &fileData));

}

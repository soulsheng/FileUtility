#include "stdafx.h"
#include "CFileUtilityWIN.h"


void CFileUtilityWIN::getFileListFromPath(tstring &path, tstring fmt, std::vector<tstring> &list)
{
	tstring csDirPath = path + _T("*.") + fmt;
	HANDLE file;
	WIN32_FIND_DATA fileData;
	char line[1024];
	char fn[1000];
	//mbstowcs(fn,csDirPath.GetBuffer(),999);
	file = FindFirstFile(csDirPath.c_str(), &fileData);
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

void CFileUtilityWIN::getFilePathFromDialog(tstring &path)
{
	BROWSEINFO bi;
	TCHAR Buffer[MAX_PATH];

	//��ʼ����ڲ���bi��ʼ
	bi.hwndOwner = NULL;
	bi.pidlRoot = NULL;//��ʼ���ƶ���rootĿ¼�ܲ�����
	bi.pszDisplayName = Buffer;//�˲�����ΪNULL������ʾ�Ի���
	bi.lpszTitle = _T("ѡ��·��");
	bi.ulFlags = BIF_EDITBOX;//���༭��ķ��
	bi.lpfn = NULL;
	bi.lParam = 0;
	bi.iImage = 0;
	//��ʼ����ڲ���bi����

	LPITEMIDLIST pIDList = SHBrowseForFolder(&bi);//������ʾѡ��Ի���

	if (pIDList)
	{
		SHGetPathFromIDList(pIDList, Buffer);

		//ȡ���ļ���·����Buffer��
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
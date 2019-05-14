// DlgVocGenTrainList.cpp : 实现文件
//

#include "stdafx.h"
#include "FileUtility.h"
#include "DlgVocGenTrainList.h"
#include "afxdialogex.h"

#include "CFileUtilityWIN.h"
#include "CFileUtilitySTL.h"

// DlgVocGenTrainList 对话框

IMPLEMENT_DYNAMIC(DlgVocGenTrainList, CDialogEx)

DlgVocGenTrainList::DlgVocGenTrainList(CWnd* pParent /*=NULL*/)
	: CDialogEx(DlgVocGenTrainList::IDD, pParent)
	, m_subRootPath(_T("Path Of Samples Subset..."))
	, m_pathImg(_T("JPEGImages"))
	, m_pathXml(_T("Annotations"))
	, m_fileList(_T("trainval.txt"))
	, m_strImgFmt(_T("jpg"))
{

}

DlgVocGenTrainList::~DlgVocGenTrainList()
{
}

void DlgVocGenTrainList::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_subRootPath);
	DDX_Text(pDX, IDC_EDIT2, m_pathImg);
	DDX_Text(pDX, IDC_EDIT3, m_pathXml);
	DDX_Text(pDX, IDC_EDIT4, m_fileList);
	DDX_CBString(pDX, IDC_COMBO1, m_strImgFmt);
}


BEGIN_MESSAGE_MAP(DlgVocGenTrainList, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_OPEN_PATH, &DlgVocGenTrainList::OnBnClickedBtnOpenPath)
	ON_BN_CLICKED(IDOK, &DlgVocGenTrainList::OnBnClickedOk)
END_MESSAGE_MAP()


// DlgVocGenTrainList 消息处理程序


void DlgVocGenTrainList::OnBnClickedBtnOpenPath()
{
	// TODO:  在此添加控件通知处理程序代码
	tstring filepath;
	CFileUtilityWIN::getFilePathFromDialog(filepath);

	m_subRootPath = filepath.c_str();// CString(filepath.c_str());
	UpdateData(FALSE);
}


void DlgVocGenTrainList::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);

	tstring strPathRoot(m_subRootPath.GetBuffer());

	tstring strPathXml = strPathRoot + _T("\\");
	strPathXml += m_pathXml.GetBuffer();

	StringVec fileListXml;
	//StringVec fmts;
	//fmts.push_back(tstring(_T("xml")));
	CFileUtilityWIN::getFileListFromPath(strPathXml, _T("xml"), fileListXml);

	if (fileListXml.empty())
		return;

	tstring strPathMid = strPathRoot.substr(strPathRoot.find(_T("VOCLAB6")) );
	strPathMid += _T("\\");

	StringVec trainList;

	for each (tstring file in fileListXml)
	{
		tstring fileNoExt = CFileUtilitySTL::getOnlyFileName(file);
		tstring trainLine = strPathMid + m_pathImg.GetBuffer();
		trainLine += _T("\\");
		trainLine += fileNoExt;
		trainLine += _T(".");
		trainLine += m_strImgFmt.GetBuffer();

		trainLine += _T(" ");

		trainLine += strPathMid + m_pathXml.GetBuffer();
		trainLine += file;

		trainList.push_back(trainLine);
	}

	tstring fileTrainList(strPathRoot);
	fileTrainList += _T("\\");
	fileTrainList += m_fileList.GetBuffer();

	CFileUtilitySTL::writeFilelist(fileTrainList, trainList);

	CDialogEx::OnOK();
}

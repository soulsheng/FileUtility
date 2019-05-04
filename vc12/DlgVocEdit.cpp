// DlgVocEdit.cpp : 实现文件
//

#include "stdafx.h"
#include "FileUtility.h"
#include "DlgVocEdit.h"
#include "afxdialogex.h"


#include "CFileUtilityMFC.h"
#include "CFileUtilityWIN.h"
#include "CFileUtilitySTL.h"
#include "CFileUtilityXML.h"

// DlgVocEdit 对话框

IMPLEMENT_DYNAMIC(DlgVocEdit, CDialogEx)

DlgVocEdit::DlgVocEdit(CWnd* pParent /*=NULL*/)
	: CDialogEx(DlgVocEdit::IDD, pParent)
	, m_strPathXml(_T(""))
{

}

DlgVocEdit::~DlgVocEdit()
{
}

void DlgVocEdit::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_strPathXml);
	DDX_Control(pDX, IDC_COMBO_TYPE_LIST, m_typeList);
}


BEGIN_MESSAGE_MAP(DlgVocEdit, CDialogEx)
	ON_BN_CLICKED(IDOK, &DlgVocEdit::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BTN_OPEN_PATH_XML, &DlgVocEdit::OnBnClickedBtnOpenPathXml)
END_MESSAGE_MAP()


// DlgVocEdit 消息处理程序


void DlgVocEdit::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);

	CString type2Edit ;
	m_typeList.GetLBText(m_typeList.GetCurSel(), type2Edit);

	StringVec fileList;
	tstring strPathXml(m_strPathXml.GetBuffer());
	bool bXML = CFileUtilitySTL::getFileExt(strPathXml)==_T("xml");
	if (bXML)
		fileList.push_back(strPathXml);
	else//path
	{
		StringVec fmts;
		fmts.push_back(tstring(_T("xml")));
		CFileUtilityWIN::getFileListFromPathNest(strPathXml, _T(""), fmts, fileList);

		if (fileList.empty())
			return;
	}

	//outputInfo(fileList.c_str());
	for each (tstring file in fileList)
	{
		CFileUtilityXML::editObjectNames(strPathXml + file, strPathXml + file, type2Edit.GetBuffer());
	}

	CDialogEx::OnOK();
}


void DlgVocEdit::OnBnClickedBtnOpenPathXml()
{
	// TODO:  在此添加控件通知处理程序代码
	tstring filepath;
	CFileUtilityWIN::getFilePathFromDialog(filepath);

	m_strPathXml = filepath.c_str();// CString(filepath.c_str());
	UpdateData(FALSE);
}

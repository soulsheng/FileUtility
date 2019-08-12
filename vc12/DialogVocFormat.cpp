// DialogVocFormat.cpp : 实现文件
//

#include "stdafx.h"
#include "FileUtility.h"
#include "DialogVocFormat.h"
#include "afxdialogex.h"

#include "CFileUtilityMFC.h"
#include "CFileUtilityWIN.h"
#include "CFileUtilitySTL.h"
#include "CFileUtilityXML.h"

// CDialogVocFormat 对话框

IMPLEMENT_DYNAMIC(CDialogVocFormat, CDialogEx)

CDialogVocFormat::CDialogVocFormat(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDialogVocFormat::IDD, pParent)
	, m_PathVocRoot(_T("PathOfVOCdevkit..."))
	, m_ClassName(_T("boat"))
	, m_nSizeList(0)
	, m_FilenameSave(_T("filelist"))
	, m_sVocVersion(_T("VOC2007"))
	, m_sJpgDir(_T("JPEGImages"))
	, m_sXmlDir(_T("Annotations"))
	, m_voc_subset(_T("trainval"))
{

}

CDialogVocFormat::~CDialogVocFormat()
{
}

void CDialogVocFormat::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_VOC_ROOT, m_PathVocRoot);
	DDX_Text(pDX, IDC_EDIT_CLASS_NAME, m_ClassName);
	DDX_Control(pDX, IDC_LIST_FILE, m_ListBox);
	DDX_Text(pDX, IDC_EDIT3, m_nSizeList);
	DDX_Text(pDX, IDC_EDIT4, m_FilenameSave);
	DDX_CBString(pDX, IDC_COMBO_VOC_VER, m_sVocVersion);
	DDX_Text(pDX, IDC_EDIT_JPG_DIR, m_sJpgDir);
	DDX_Text(pDX, IDC_EDIT_XML_DIR, m_sXmlDir);
	DDX_CBString(pDX, IDC_COMBO_VOC_SUBSET, m_voc_subset);
}


BEGIN_MESSAGE_MAP(CDialogVocFormat, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_VOC_ROOT_PATH, &CDialogVocFormat::OnBnClickedBtnVocRootPath)
	ON_BN_CLICKED(IDC_BTN_GET_FILE_ID, &CDialogVocFormat::OnBnClickedBtnGetFileId)
	ON_BN_CLICKED(IDC_BTN_FORMAT_TRAIN_LIST, &CDialogVocFormat::OnBnClickedBtnFormatTrainList)
	ON_BN_CLICKED(IDC_BTN_SAVE_LIST, &CDialogVocFormat::OnBnClickedBtnSaveList)
	ON_BN_CLICKED(IDC_BTN_FILTER_ONLY, &CDialogVocFormat::OnBnClickedBtnFilterOnly)
	ON_BN_CLICKED(IDC_BTN_COPY_FILES, &CDialogVocFormat::OnBnClickedBtnCopyFiles)
END_MESSAGE_MAP()


// CDialogVocFormat 消息处理程序


void CDialogVocFormat::OnBnClickedBtnVocRootPath()
{
	// TODO:  在此添加控件通知处理程序代码
	tstring filepath;
	CFileUtilityWIN::getFilePathFromDialog(filepath);

	m_PathVocRoot = filepath.c_str();// CString(filepath.c_str());
	UpdateData(FALSE);
}

void CDialogVocFormat::fillListBox(StringVec& fileVec)
{
	m_ListBox.ResetContent();

	for (StringVec::iterator itr = fileVec.begin(); itr != fileVec.end(); itr++)
	{
		m_ListBox.AddString(itr->c_str());
	}

	m_nSizeList = fileVec.size();

	UpdateData(FALSE);
}

void CDialogVocFormat::OnBnClickedBtnGetFileId()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);

	pathRelativeJpg = m_sVocVersion.GetBuffer();
	pathRelativeJpg += _T("/");
	pathRelativeJpg += m_sJpgDir.GetBuffer();
	pathRelativeJpg += _T("/");

	pathRelativeXml = m_sVocVersion.GetBuffer();
	pathRelativeXml += _T("/");
	pathRelativeXml += m_sXmlDir.GetBuffer();
	pathRelativeXml += _T("/");

	CString filelistMix = m_PathVocRoot;
	filelistMix += "\\";
	filelistMix += m_sVocVersion;
	filelistMix += "\\ImageSets\\Main\\";
	filelistMix += m_ClassName;
	if (!m_ClassName.IsEmpty())
		filelistMix += "_";
	filelistMix += m_voc_subset.GetBuffer();
	filelistMix += ".txt";

	if (!m_ClassName.IsEmpty())
	{
		StringIDMap	valMap;
		CFileUtilitySTL::readFilelist(tstring(filelistMix.GetBuffer()), valMap);

		m_strVecCurrent.clear();
		CFileUtilitySTL::selectLableNoEqualMinusOne(valMap, m_strVecCurrent);
	}
	else
	{
		CFileUtilitySTL::readFilelist(tstring(filelistMix.GetBuffer()), m_strVecCurrent);
	}

	fillListBox(m_strVecCurrent);

	AfxMessageBox(_T("FileID ok"));

}


void CDialogVocFormat::OnBnClickedBtnFormatTrainList()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);

	StringVec linesJpg, linesXml;

	StringVec fileVec = m_strVecCurrent;

	CFileUtilitySTL::convertString(fileVec, linesJpg, pathRelativeJpg, tstring(_T(".jpg")));
	CFileUtilitySTL::convertString(fileVec, linesXml, pathRelativeXml, tstring(_T(".xml")));

	CFileUtilitySTL::mixStringVec(m_strVecCurrent, linesJpg, linesXml);

	fillListBox(m_strVecCurrent);

	AfxMessageBox(_T("TrainList ok"));
}


void CDialogVocFormat::OnBnClickedBtnSaveList()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);

	CString filename = m_PathVocRoot;
	filename += "\\";
	filename += m_sVocVersion;
	filename += "-";
	filename += m_ClassName;
	filename += "-";	
	filename += m_FilenameSave;
	filename += ".txt";

	CFileUtilitySTL::writeFilelist(filename.GetBuffer(), m_strVecCurrent);
	AfxMessageBox(_T("SaveList ok"));
}


void CDialogVocFormat::OnBnClickedBtnFilterOnly()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);

	tstring filePath = m_PathVocRoot.GetBuffer();
	filePath += _T("\\");
	
	StringVec fileVec = m_strVecCurrent;

	m_strVecCurrent.clear();
	for (StringVec::iterator itr = fileVec.begin(); itr != fileVec.end();itr++)
	{
		tstring filename = pathRelativeXml + *itr + tstring(_T(".xml"));
		StringVec obs;
		CFileUtilityXML::findObjectNames(filePath + filename, obs);

		bool bNotBoat = false;
		for each (tstring name in obs)
		{
			if (name != tstring(m_ClassName.GetBuffer()))
			{
				bNotBoat = true;
				break;
			}
		}

		if (!bNotBoat)
			m_strVecCurrent.push_back(*itr);
	}

	fillListBox(m_strVecCurrent);

	AfxMessageBox(_T("Filter ok"));

}


void CDialogVocFormat::OnBnClickedBtnCopyFiles()
{
	if (m_strVecCurrent.empty())
	{
		AfxMessageBox(_T("CopyFiles failed, list empty"));
		return;
	}

	if (tstring::npos != m_strVecCurrent[0].find(_T(" ")))
	{
		tstring msg(m_strVecCurrent[0] + _T("CopyFiles failed, list invalid"));
		AfxMessageBox(msg.c_str());
		return;
	}

	// TODO:  在此添加控件通知处理程序代码
	tstring filePath = m_PathVocRoot.GetBuffer();
	filePath += _T("\\");

	StringVec fileVec = m_strVecCurrent;

	StringVec linesJpg, linesXml, linesJpgName, linesXmlName, linesMix;

	CFileUtilitySTL::convertString(fileVec, linesJpg, pathRelativeJpg, tstring(_T(".jpg")));
	CFileUtilitySTL::convertString(fileVec, linesXml, pathRelativeXml, tstring(_T(".xml")));
	CFileUtilitySTL::convertString(fileVec, linesJpgName, tstring(_T("")), tstring(_T(".jpg")));
	CFileUtilitySTL::convertString(fileVec, linesXmlName, tstring(_T("")), tstring(_T(".xml")));


	tstring toPath = filePath + _T("\\select\\");

	CFileUtilityWIN::createPath(toPath);

	tstring toPathJpg = toPath + m_sJpgDir.GetBuffer() + _T("\\");
	tstring toPathXml = toPath + m_sXmlDir.GetBuffer() + _T("\\");
	CFileUtilityWIN::createPath(toPathJpg);
	CFileUtilityWIN::createPath(toPathXml);

	CFileUtilitySTL::copyFilelist(filePath, toPathJpg, linesJpg, linesJpgName);
	CFileUtilitySTL::copyFilelist(filePath, toPathXml, linesXml, linesXmlName);

	AfxMessageBox(_T("CopyFiles ok"));

}

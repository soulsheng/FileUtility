#pragma once
#include "afxwin.h"
#include "commonDefinitionFile.h"


// CDialogVocFormat �Ի���

class CDialogVocFormat : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogVocFormat)

public:
	CDialogVocFormat(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDialogVocFormat();

// �Ի�������
	enum { IDD = IDD_DIALOG_VOC };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
protected:
	CString m_PathVocRoot;
	CString m_ClassName;
	CListBox m_ListBox;
	int m_nSizeList;
	StringVec m_strVecCurrent;

protected:
	void fillListBox(StringVec& fileVec);

public:
	afx_msg void OnBnClickedBtnVocRootPath();
	afx_msg void OnBnClickedBtnGetFileId();
	afx_msg void OnBnClickedBtnFormatTrainList();
	CString m_FilenameSave;
	afx_msg void OnBnClickedBtnSaveList();
	afx_msg void OnBnClickedBtnFilterOnly();
	afx_msg void OnBnClickedBtnCopyFiles();
protected:
	CString m_sVocVersion;
	CString m_sJpgDir;
	CString m_sXmlDir;
	tstring pathRelativeJpg, pathRelativeXml;

	// trainval or test
	CString m_voc_subset;
};

#pragma once
#include "afxwin.h"


// DlgVocEdit 对话框

class DlgVocEdit : public CDialogEx
{
	DECLARE_DYNAMIC(DlgVocEdit)

public:
	DlgVocEdit(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~DlgVocEdit();

// 对话框数据
	enum { IDD = IDD_DLG_VOC_EDIT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	CString m_strPathXml;
	CComboBox m_typeList;
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedBtnOpenPathXml();
};

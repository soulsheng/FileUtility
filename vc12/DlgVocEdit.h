#pragma once
#include "afxwin.h"


// DlgVocEdit �Ի���

class DlgVocEdit : public CDialogEx
{
	DECLARE_DYNAMIC(DlgVocEdit)

public:
	DlgVocEdit(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~DlgVocEdit();

// �Ի�������
	enum { IDD = IDD_DLG_VOC_EDIT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	CString m_strPathXml;
	CComboBox m_typeList;
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedBtnOpenPathXml();
};

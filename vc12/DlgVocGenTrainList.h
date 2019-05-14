#pragma once


// DlgVocGenTrainList �Ի���

class DlgVocGenTrainList : public CDialogEx
{
	DECLARE_DYNAMIC(DlgVocGenTrainList)

public:
	DlgVocGenTrainList(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~DlgVocGenTrainList();

// �Ի�������
	enum { IDD = IDD_DLG_VOC_GEN_TRAIN_LIST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	// sub root path of jpeg & xml
	CString m_subRootPath;
	CString m_pathImg;
	CString m_pathXml;
	CString m_fileList;
public:
	afx_msg void OnBnClickedBtnOpenPath();
	afx_msg void OnBnClickedOk();
protected:
	CString m_strImgFmt;
};


// FileUtilityView.h : CFileUtilityView ��Ľӿ�
//

#pragma once


class CFileUtilityView : public CView
{
protected: // �������л�����
	CFileUtilityView();
	DECLARE_DYNCREATE(CFileUtilityView)

// ����
public:
	CFileUtilityDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// ʵ��
public:
	virtual ~CFileUtilityView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnCollectFiles2Root();
};

#ifndef _DEBUG  // FileUtilityView.cpp �еĵ��԰汾
inline CFileUtilityDoc* CFileUtilityView::GetDocument() const
   { return reinterpret_cast<CFileUtilityDoc*>(m_pDocument); }
#endif


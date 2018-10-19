
// FileUtilityView.h : CFileUtilityView 类的接口
//

#pragma once


class CFileUtilityView : public CView
{
protected: // 仅从序列化创建
	CFileUtilityView();
	DECLARE_DYNCREATE(CFileUtilityView)

// 特性
public:
	CFileUtilityDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// 实现
public:
	virtual ~CFileUtilityView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnCollectFiles2Root();
};

#ifndef _DEBUG  // FileUtilityView.cpp 中的调试版本
inline CFileUtilityDoc* CFileUtilityView::GetDocument() const
   { return reinterpret_cast<CFileUtilityDoc*>(m_pDocument); }
#endif


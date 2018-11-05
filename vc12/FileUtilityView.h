
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
	afx_msg void OnGenerateTrainList();
	afx_msg void OnGetFileList();

public:
	void	outputInfo(const TCHAR* message, int value = -1);	// print to output window or status bar
	void	AddFileViewBranch(tstring fileNameShort, tstring root=_T("") );
	void	AddFileViewBranch(StringVec fileNameShort, tstring root = _T(""));
	void	switchBilViewByName(tstring name);

	void	kernelSelectSample(bool rename=false);

protected:
	CImage image;

	FilesMap	m_FilesMap;

	tstring		imagePath;

public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnGetFileListNest();
	afx_msg void OnShinkValList();
	afx_msg void OnSelectSample();
	afx_msg void OnSubPathMix();
};

#ifndef _DEBUG  // FileUtilityView.cpp 中的调试版本
inline CFileUtilityDoc* CFileUtilityView::GetDocument() const
   { return reinterpret_cast<CFileUtilityDoc*>(m_pDocument); }
#endif


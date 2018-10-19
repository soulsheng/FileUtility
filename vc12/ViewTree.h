
#pragma once

/////////////////////////////////////////////////////////////////////////////
// CViewTree 窗口

class CViewTree : public CTreeCtrl
{
// 构造
public:
	CViewTree();

// 重写
protected:
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);

// 实现
public:
	virtual ~CViewTree();
	afx_msg void OnSelChanged(NMHDR* pNMHDR, LRESULT* pResult);

protected:
	DECLARE_MESSAGE_MAP()
};

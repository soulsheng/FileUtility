
// FileUtilityView.cpp : CFileUtilityView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "FileUtility.h"
#endif

#include "MainFrm.h"

#include "FileUtilityDoc.h"
#include "FileUtilityView.h"

#include "CFileUtilityMFC.h"
#include "CFileUtilityWIN.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CFileUtilityView

IMPLEMENT_DYNCREATE(CFileUtilityView, CView)

BEGIN_MESSAGE_MAP(CFileUtilityView, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_COLLECT_FILES_2ROOT, &CFileUtilityView::OnCollectFiles2Root)
	ON_COMMAND(ID_GET_FILE_LIST, &CFileUtilityView::OnGetFileList)
END_MESSAGE_MAP()

// CFileUtilityView ����/����

CFileUtilityView::CFileUtilityView()
{
	// TODO:  �ڴ˴���ӹ������

}

CFileUtilityView::~CFileUtilityView()
{
}

BOOL CFileUtilityView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CFileUtilityView ����

void CFileUtilityView::OnDraw(CDC* /*pDC*/)
{
	CFileUtilityDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO:  �ڴ˴�Ϊ����������ӻ��ƴ���
}

void CFileUtilityView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CFileUtilityView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CFileUtilityView ���

#ifdef _DEBUG
void CFileUtilityView::AssertValid() const
{
	CView::AssertValid();
}

void CFileUtilityView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CFileUtilityDoc* CFileUtilityView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CFileUtilityDoc)));
	return (CFileUtilityDoc*)m_pDocument;
}
#endif //_DEBUG


// CFileUtilityView ��Ϣ�������


void CFileUtilityView::OnCollectFiles2Root()
{
	// TODO:  �ڴ���������������
	

}

void CFileUtilityView::outputInfo(const TCHAR* message, int value /*= -1*/)
{
	CMainFrame* pMFram = (CMainFrame*)AfxGetMainWnd();

	tstream os;
	os << message;

	if (-1 != value)
		os << _T(" = ") << value;

	pMFram->FillBuildWindow(os.str());
}


void CFileUtilityView::OnGetFileList()
{
	// TODO:  �ڴ���������������
	tstring		imagePath;

	CFileUtilityWIN::getFilePathFromDialog(imagePath);

	if (imagePath.empty())
		return;

	std::vector<tstring>		imageList;

	CFileUtilityWIN::getFileListFromPath(imagePath, _T("jpeg"), imageList);

	outputInfo(imagePath.c_str());
	for each (tstring file in imageList)
	{
		outputInfo(file.c_str());
		AddFileViewBranch(file);
	}
}
void CFileUtilityView::AddFileViewBranch(tstring fileNameShort)
{
	// MainFrame
	CMainFrame *pMain = (CMainFrame *)AfxGetMainWnd();
	pMain->AddFileViewBranch(fileNameShort);
}

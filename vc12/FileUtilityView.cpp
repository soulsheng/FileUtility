
// FileUtilityView.cpp : CFileUtilityView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "FileUtility.h"
#endif

#include "MainFrm.h"

#include "FileUtilityDoc.h"
#include "FileUtilityView.h"

#include "CFileUtilityMFC.h"
#include "CFileUtilityWIN.h"
#include "CFileUtilitySTL.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CFileUtilityView

IMPLEMENT_DYNCREATE(CFileUtilityView, CView)

BEGIN_MESSAGE_MAP(CFileUtilityView, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_GENERATE_TRAIN_LIST, &CFileUtilityView::OnGenerateTrainList)
	ON_COMMAND(ID_GET_FILE_LIST, &CFileUtilityView::OnGetFileList)
	ON_WM_TIMER()
	ON_WM_CREATE()
	ON_COMMAND(ID_GET_FILE_LIST_NEST, &CFileUtilityView::OnGetFileListNest)
END_MESSAGE_MAP()

// CFileUtilityView 构造/析构

CFileUtilityView::CFileUtilityView()
{
	// TODO:  在此处添加构造代码

}

CFileUtilityView::~CFileUtilityView()
{
}

BOOL CFileUtilityView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CFileUtilityView 绘制

void CFileUtilityView::OnDraw(CDC* /*pDC*/)
{
	CFileUtilityDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO:  在此处为本机数据添加绘制代码
	if (image.IsNull())
		return;

	CRect rect;
	CDC *pDC = this->GetDC();
	GetClientRect(rect);
	HDC hDC = pDC->GetSafeHdc();

	::SetStretchBltMode(hDC, HALFTONE);
	::SetBrushOrgEx(hDC, 0, 0, NULL);

	image.Draw(hDC, rect);

	ReleaseDC(pDC);//释放picture控件的DC
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


// CFileUtilityView 诊断

#ifdef _DEBUG
void CFileUtilityView::AssertValid() const
{
	CView::AssertValid();
}

void CFileUtilityView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CFileUtilityDoc* CFileUtilityView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CFileUtilityDoc)));
	return (CFileUtilityDoc*)m_pDocument;
}
#endif //_DEBUG


// CFileUtilityView 消息处理程序


void CFileUtilityView::OnGenerateTrainList()
{
	// TODO:  在此添加命令处理程序代码
	tstring		imagePath;

	CFileUtilityWIN::getFilePathFromDialog(imagePath);

	if (imagePath.empty())
		return;

	//std::vector<tstring>		subPathList;

	//CFileUtilityWIN::getSubPathFromPath(imagePath, subPathList);

	ClassesMap	classMap;
	StringVec	classList;
	CFileUtilitySTL::readFilelist(imagePath+_T("classIndex.txt"), classList);

	CFileUtilitySTL::convertList2Map(classMap, classList);

	tstring filelistName(imagePath + _T("/train.txt"));
	outputInfo(filelistName.c_str());
	if (CFileUtilitySTL::removeFile(filelistName))
		outputInfo(_T("无法删除"));
	else
		outputInfo(_T("已删除"));

	outputInfo(imagePath.c_str());
	for each (tstring subPath in classList)
	{
	
		std::vector<tstring>		imageList;
		m_FilesMap.clear();

		CFileUtilityWIN::getFileListFromPathNest(imagePath + _T("/") + subPath, _T(""), _T("jpg"), imageList);

		for each (tstring file in imageList)
		{
			m_FilesMap.insert(FilesPair(file, imagePath + file));

			outputInfo(file.c_str());
			AddFileViewBranch(file, subPath);
		}

		if (!image.IsNull())
			image.Destroy();

		tstring filepath = imagePath + m_FilesMap.rbegin()->first;
		image.Load(filepath.c_str());

		//CFileUtilitySTL::writeFilelist(imagePath + _T("/") + subPath + _T("filelist.txt"), m_FilesMap, classMap[subPath]);
		
		CFileUtilitySTL::writeFilelist(filelistName, m_FilesMap, classMap[subPath], false);
	}

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


void CFileUtilityView::OnGetFileListNest()
{
	// TODO:  在此添加命令处理程序代码
	tstring		imagePath;

	CFileUtilityWIN::getFilePathFromDialog(imagePath);

	if (imagePath.empty())
		return;

	std::vector<tstring>		imageList;

	CFileUtilityWIN::getFileListFromPathNest(imagePath, _T(""), _T("jpg"), imageList);

	if (imageList.empty())
		return;

	outputInfo(imagePath.c_str());
	for each (tstring file in imageList)
	{
		m_FilesMap.insert(FilesPair(file, imagePath + file));

		outputInfo(file.c_str());
		AddFileViewBranch(file, imagePath);
	}

	if (!image.IsNull())
		image.Destroy();

	tstring filepath = imagePath + m_FilesMap.rbegin()->first;
	image.Load(filepath.c_str());

	CFileUtilitySTL::writeFilelist(imagePath + _T("filelist.txt"), m_FilesMap);
}

void CFileUtilityView::AddFileViewBranch(tstring fileNameShort, tstring root)
{
	// MainFrame
	CMainFrame *pMain = (CMainFrame *)AfxGetMainWnd();
	pMain->AddFileViewBranch(fileNameShort, root);
}

void CFileUtilityView::switchBilViewByName(tstring name)
{
	tstring filepath = m_FilesMap[name];
	if (filepath.empty())
		return;

	if (!image.IsNull())
		image.Destroy();

	image.Load(filepath.c_str());
}

void CFileUtilityView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	OnDraw(NULL);

	CView::OnTimer(nIDEvent);
}


int CFileUtilityView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	SetTimer(0, 30, NULL);	//定时显示，一个30毫秒触发一次的定时器，30帧/秒 

	return 0;
}


void CFileUtilityView::OnGetFileList()
{
	// TODO:  在此添加命令处理程序代码
	tstring		imagePath;

	CFileUtilityWIN::getFilePathFromDialog(imagePath);

	if (imagePath.empty())
		return;

	std::vector<tstring>		imageList;

	CFileUtilityWIN::getFileListFromPath(imagePath, _T("jpg"), imageList);

	outputInfo(imagePath.c_str());
	for each (tstring file in imageList)
	{
		m_FilesMap.insert(FilesPair(file, imagePath + file));

		outputInfo(file.c_str());
		AddFileViewBranch(file, imagePath);
	}

	CFileUtilitySTL::writeFilelist(imagePath + _T("filelist.txt"), m_FilesMap);
}

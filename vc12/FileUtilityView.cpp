
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
	ON_COMMAND(ID_SHINK_VAL_LIST, &CFileUtilityView::OnShinkValList)
	ON_COMMAND(ID_SELECT_SAMPLE, &CFileUtilityView::OnSelectSample)
	ON_COMMAND(ID_SUB_PATH_MIX, &CFileUtilityView::OnSubPathMix)
	ON_COMMAND(MENU_FILE_RENAME_BAT, &CFileUtilityView::OnFileRenameBat)
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

	StringIDMap	classMap;
	StringVec	classList;
	CFileUtilitySTL::readFilelist(imagePath+_T("classIndex.txt"), classList);

	if (classList.empty())
	{
		outputInfo(_T("类索引文件无法找到或是空的，classIndex.txt"));
		return;
	}

	CFileUtilitySTL::convertList2Map(classMap, classList);

	tstring filelistTrain(imagePath + _T("/train.txt"));
	tstring filelistVal(imagePath + _T("/val.txt"));
	outputInfo(filelistTrain.c_str());
	if (CFileUtilitySTL::removeFile(filelistTrain))
		outputInfo(_T("无法删除"));
	else
		outputInfo(_T("已删除"));

	std::map<tstring, StringVec> supperFileList;

	outputInfo(imagePath.c_str());
	for each (tstring subPath in classList)
	{
	
		std::vector<tstring>		imageList;
		m_FilesMap.clear();

		StringVec fmts;
		fmts.push_back(tstring(_T("jpg")));
		fmts.push_back(tstring(_T("jpeg")));
		CFileUtilityWIN::getFileListFromPathNest(imagePath + _T("/"), subPath, fmts, imageList);
		
		if (imageList.empty())
		{
			tstring pathTemp(imagePath + _T("/") + subPath);
			outputInfo(pathTemp.c_str());
			outputInfo(_T("目录有误或是空的"));
			continue;
		}

		for each (tstring file in imageList)
		{
			m_FilesMap.insert(FilesPair(file, imagePath + file));

			outputInfo(file.c_str());
		}
		//AddFileViewBranch(imageList, subPath);
		supperFileList.insert(std::make_pair(subPath, imageList));

		if (!image.IsNull())
			image.Destroy();

		tstring filepath = imagePath + m_FilesMap.rbegin()->first;
		image.Load(filepath.c_str());

		//CFileUtilitySTL::writeFilelist(imagePath + _T("/") + subPath + _T("filelist.txt"), m_FilesMap, classMap[subPath]);
		
		CFileUtilitySTL::writeFilelist(filelistTrain, m_FilesMap, classMap[subPath], false);
	}

	//CFileUtilitySTL::generateVal(filelistTrain, filelistVal);

	outputInfo(_T(""));
	outputInfo(filelistTrain.c_str());
	outputInfo(filelistVal.c_str());
	outputInfo(_T("成功生成"));

	// update ui once 
	for (std::map<tstring, StringVec>::iterator itr = supperFileList.begin(); itr != supperFileList.end();itr++)
		AddFileViewBranch(itr->second, itr->first);

}

void CFileUtilityView::outputInfo(const TCHAR* message, int value /*= -1*/)
{
	CMainFrame* pMFram = (CMainFrame*)AfxGetMainWnd();

	tsstream os;
	os << message;

	if (-1 != value)
		os << _T(" = ") << value;

	pMFram->FillBuildWindow(os.str());
}


void CFileUtilityView::OnGetFileListNest()
{
	// TODO:  在此添加命令处理程序代码

	CFileUtilityWIN::getFilePathFromDialog(imagePath);

	if (imagePath.empty())
		return;

	std::vector<tstring>		imageList;

	StringVec fmts;
	fmts.push_back(tstring(_T("jpg")));
	fmts.push_back(tstring(_T("jpeg")));
	CFileUtilityWIN::getFileListFromPathNest(imagePath, _T(""), fmts, imageList);

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

void CFileUtilityView::AddFileViewBranch(StringVec fileNameShort, tstring root /*= _T("")*/)
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


void CFileUtilityView::OnShinkValList()
{
	// TODO:  在此添加命令处理程序代码
	tstring		filePath;

	CFileUtilityWIN::getFilePathFromDialog(filePath);

	if (filePath.empty())
		return;

	StringVec	classNoList;
	CFileUtilitySTL::readFilelist(filePath + _T("classNo.txt"), classNoList);

	StringIDMap	classMap;
	CFileUtilitySTL::convertList2Map(classMap, classNoList);

	if (classNoList.empty())
	{
		tstring pathTemp(filePath + _T("classNo.txt"));
		outputInfo(pathTemp.c_str());
		outputInfo(_T("文件有误或是空的"));
		return;
	}

	StringVec	valFulList;
	CFileUtilitySTL::readFilelist(filePath + _T("val-full.txt"), valFulList);

	if (classNoList.empty())
	{
		tstring pathTemp(filePath + _T("val-full.txt"));
		outputInfo(pathTemp.c_str());
		outputInfo(_T("文件有误或是空的"));
		return;
	}

	StringIDMap	valMap;
	for each (tstring valLine in valFulList)
	{
		if (valLine.empty())
			continue;

		int classNoMatch = 0;
		for (StringIDMap::iterator itr = classMap.begin(); itr != classMap.end();itr++)
		{
			int indexBlank = valLine.find_last_of(_T(" "));
			tstring lastID = valLine.substr( indexBlank );
			
			if (tstring::npos == lastID.find(itr->first))
				continue;
			else
			{
				valMap.insert(StringIDPair(valLine.substr(0, indexBlank + 1), itr->second));
				break;
			}
		}
	}

	CFileUtilitySTL::writeFilelist(filePath + _T("val.txt"), valMap);

}

void CFileUtilityView::OnSelectSample()
{
	kernelSelectSample();
}

void CFileUtilityView::kernelSelectSample(bool rename)
{
	// TODO:  在此添加命令处理程序代码
	tstring		filePath;

	CFileUtilityWIN::getFilePathFromDialog(filePath);

	if (filePath.empty())
		return;

	StringIDMap	valMap;
	CFileUtilitySTL::readFilelist(filePath + _T("val.txt"), valMap);

	tstring toPath = filePath + _T("/select/");

	CFileUtilityWIN::createPath(toPath);

	CFileUtilityWIN::createPath(toPath, valMap);

	if (rename)
		CFileUtilitySTL::copyFilelistRename(filePath, toPath, valMap);
	else
		CFileUtilitySTL::copyFilelist(filePath, toPath, valMap);

	outputInfo(_T(""));
	outputInfo(_T("样本挑选完成！目标目录："));
	outputInfo(toPath.c_str());
}


void CFileUtilityView::OnSubPathMix()
{
	// TODO:  在此添加命令处理程序代码
	kernelSelectSample(true);
	
}


void CFileUtilityView::OnFileRenameBat()
{
	// TODO:  在此添加命令处理程序代码
	tstring		imagePath;

	CFileUtilityWIN::getFilePathFromDialog(imagePath);

	if (imagePath.empty())
		return;

	std::vector<tstring>		imageList;

	CFileUtilityWIN::getFileListFromPath(imagePath, _T("jpeg"), imageList);


	tstring toPath = imagePath + _T("/select/");

	CFileUtilityWIN::createPath(toPath);

	CFileUtilitySTL::copyFilelistRename(imagePath, toPath, imageList);

	outputInfo(_T(""));
	outputInfo(_T("样本挑选完成！目标目录："));
	outputInfo(toPath.c_str());
}


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
	if (image.IsNull())
		return;

	CRect rect;
	CDC *pDC = this->GetDC();
	GetClientRect(rect);
	HDC hDC = pDC->GetSafeHdc();

	::SetStretchBltMode(hDC, HALFTONE);
	::SetBrushOrgEx(hDC, 0, 0, NULL);

	image.Draw(hDC, rect);

	ReleaseDC(pDC);//�ͷ�picture�ؼ���DC
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


void CFileUtilityView::OnGenerateTrainList()
{
	// TODO:  �ڴ���������������
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
		outputInfo(_T("�������ļ��޷��ҵ����ǿյģ�classIndex.txt"));
		return;
	}

	CFileUtilitySTL::convertList2Map(classMap, classList);

	tstring filelistTrain(imagePath + _T("/train.txt"));
	tstring filelistVal(imagePath + _T("/val.txt"));
	outputInfo(filelistTrain.c_str());
	if (CFileUtilitySTL::removeFile(filelistTrain))
		outputInfo(_T("�޷�ɾ��"));
	else
		outputInfo(_T("��ɾ��"));

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
			outputInfo(_T("Ŀ¼������ǿյ�"));
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
	outputInfo(_T("�ɹ�����"));

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
	// TODO:  �ڴ���������������

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
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	OnDraw(NULL);

	CView::OnTimer(nIDEvent);
}


int CFileUtilityView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	SetTimer(0, 30, NULL);	//��ʱ��ʾ��һ��30���봥��һ�εĶ�ʱ����30֡/�� 

	return 0;
}


void CFileUtilityView::OnGetFileList()
{
	// TODO:  �ڴ���������������
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
	// TODO:  �ڴ���������������
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
		outputInfo(_T("�ļ�������ǿյ�"));
		return;
	}

	StringVec	valFulList;
	CFileUtilitySTL::readFilelist(filePath + _T("val-full.txt"), valFulList);

	if (classNoList.empty())
	{
		tstring pathTemp(filePath + _T("val-full.txt"));
		outputInfo(pathTemp.c_str());
		outputInfo(_T("�ļ�������ǿյ�"));
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
	// TODO:  �ڴ���������������
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
	outputInfo(_T("������ѡ��ɣ�Ŀ��Ŀ¼��"));
	outputInfo(toPath.c_str());
}


void CFileUtilityView::OnSubPathMix()
{
	// TODO:  �ڴ���������������
	kernelSelectSample(true);
	
}


void CFileUtilityView::OnFileRenameBat()
{
	// TODO:  �ڴ���������������
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
	outputInfo(_T("������ѡ��ɣ�Ŀ��Ŀ¼��"));
	outputInfo(toPath.c_str());
}

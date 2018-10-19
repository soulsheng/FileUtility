#include "stdafx.h"
#include "CFileUtilityMFC.h"

tstring CFileUtilityMFC::openFileDialog(tstring fmt, tstring tip, CWnd* pParentWnd)
{
	tstring filepath;

	tstring filter = tip + _T("|") + fmt;
	filter += _T("|All Files(*.*)|*.*||");

	CFileDialog dlg(TRUE,
		fmt.c_str(), NULL,
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		filter.c_str(), pParentWnd);

	INT_PTR result = dlg.DoModal();
	if (result == IDOK)
	{
		CString fileName = dlg.GetPathName();

		filepath = fileName.GetBuffer();		
	}

	return filepath;
}



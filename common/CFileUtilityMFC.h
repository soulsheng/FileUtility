
#pragma once
#include "commonDefinitionFile.h"

#include "stdafx.h"

class CFileUtilityMFC
{
public:
	CFileUtilityMFC(){}
	~CFileUtilityMFC(){}

public:
	// fmt: eg _T("*.jpg;*.jpeg")
	static tstring	openFileDialog(tstring fmt, tstring tip, CWnd* pParentWnd);

};
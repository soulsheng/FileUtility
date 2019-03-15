#include "stdafx.h"
#include "CFileUtilityXML.h"
#include "pugixml.hpp"

bool CFileUtilityXML::findObjectNames(tstring& file, StringVec& strVec)
{
	pugi::xml_document doc;

	doc.load_file( file.c_str() );

	pugi::xml_node node = doc.child(_T("annotation")).child(_T("object"));

	while (node)
	{
		tstring obj_name = tstring(node.child(_T("name")).first_child().value());
		strVec.push_back(obj_name);
		node = node.next_sibling();
	}

	return true;
}

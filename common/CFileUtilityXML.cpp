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

bool CFileUtilityXML::editObjectNames(tstring fileIn, tstring fileOut, tstring str)
{
	pugi::xml_document doc;

	doc.load_file(fileIn.c_str());

	pugi::xml_node node = doc.child(_T("annotation")).child(_T("object"));

	while (node)
	{
		tstring obj_name = tstring(node.child(_T("name")).first_child().value());
		if (str != obj_name)
			node.child(_T("name")).first_child().set_value(str.c_str());

		node = node.next_sibling();
	}

	doc.save_file(fileOut.c_str());
	
	return true;
}
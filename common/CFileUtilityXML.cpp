#include "stdafx.h"
#include "CFileUtilityXML.h"
#include "pugixml.hpp"
#include "CFileUtilitySTL.h"

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

tstring CFileUtilityXML::xy2wh(tstring& val)
{
	tstring val_wh;
	StringVec vals = CFileUtilitySTL::split(val, _T(" "));
	int nRect[4];
	for (int i = 0; i < 4; i++)
	{
		nRect[i] = _ttoi(vals[i].c_str());
	}

	TCHAR buffer[7];
	_itot(nRect[2] - nRect[0], buffer, 10);
	vals[2] = buffer;

	_itot(nRect[3] - nRect[1], buffer, 10);
	vals[3] = buffer;

	for (int i = 0; i < 4; i++)
	{
		val_wh += vals[i] + _T(" ");
	}

	return val_wh;
}

int CFileUtilityXML::getStringBBox(tstring str, tstring& line, tstring& line_gt)
{
	pugi::xml_node node = doc.child(_T("annotation")).child(_T("object"));

	int numBBox = 0;
	while (node)
	{
		tstring obj_name = tstring(node.child(_T("name")).first_child().value());
		if (str.empty() || str == obj_name)
		{
			//node.child(_T("name")).first_child().set_value(str.c_str());
			tstring val = getNodeValueAll( node.child(_T("bndbox") ));
			line += val;

			line_gt += _T("\n");;
			line_gt += xy2wh(val);
			line_gt += _T("0 0 0 0 0 0");;

			numBBox++;
		}

		node = node.next_sibling();
	}

	if (line.empty())
		return false;

	node = doc.child(_T("annotation")).child(_T("filename"));
	tstring filename = node.first_child().value();

	line = CFileUtilitySTL::getOnlyFileName(filename) + _T(" ") + line;

	tsstream os;
	os << filename << std::endl
		<< numBBox << line_gt;

	line_gt = os.str();

	return numBBox;
}

tstring CFileUtilityXML::getNodeValueAll(pugi::xml_node node)
{
	tstring textBBox;

	node = node.first_child();
	while (node)
	{
		tstring val = tstring(node.first_child().value());
		
		textBBox += val + _T(" ");

		node = node.next_sibling();
	}

	return textBBox;
}

CFileUtilityXML::CFileUtilityXML(tstring& fileXML)
{
	doc.load_file(fileXML.c_str());
}
#ifndef REPOSITORY_H
#define REPOSITORY_H
//////////////////////////////////////////////////////////////////////////
// XmlParser.h -  Parses xml content in to AbstractXmlElement AST		//
//																		//
// ver 1.0																//
// ---------------------------------------------------------------------//
// copyright © Isira Samarasekera, 2015									//
// All rights granted provided that this notice is retained				//
// ---------------------------------------------------------------------//
// Language:    Visual C++, Visual Studio Ultimate 2013                 //
// Platform:    Mac Book Pro, Core i5, Windows 8.1						//
// Application: Project #2 – XmlDocument,2015						//
// Author:      Isira Samarasekera, Syracuse University					//
//              issamara@syr.edu										//
//////////////////////////////////////////////////////////////////////////
/*
* Module Operations:
* ==================
*
* Public Interface:
* =================

*
* Required Files:
* ===============
* Repository.h , Repository.cpp
* XmlElement.h,  XmlElement.cpp
*
* Build Process:
* ================
*  devenv XmlDocument.sln /debug rebuild
*
* Maintenance History:
* ====================
* ver 1.0 : 19 Mar 15
* - first release
*/

#include <stack>
#include <memory>
#include "../XmlElement/XmlElement.h"

class Repository
{
public:
	void pushToStack(std::shared_ptr<XmlProcessing::AbstractXmlElement> element);
	std::shared_ptr<XmlProcessing::AbstractXmlElement> pop();
	void addToTop(std::shared_ptr<XmlProcessing::AbstractXmlElement> element);


private:
	std::stack<std::shared_ptr<XmlProcessing::AbstractXmlElement>> _elementStack;
	std::shared_ptr<XmlProcessing::AbstractXmlElement> doc_element;
};
#endif
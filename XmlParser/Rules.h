#ifndef RULES_H
#define RULES_H
#include "../XmlElementParts/xmlElementParts.h"
#include "Actions.h"
#include <memory>

//////////////////////////////////////////////////////////////////////////
// Rules.h -  Contains rules for parsing XmlDocument					//
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
*
* Build Command:
* ==============
* cl /EHa /DTEST_RULES Rules.cpp
*
* Maintenance History:
* ====================
* ver 1.0 : 19 Mar 15
* - first release
*/

class ARule
{
	std::vector<std::shared_ptr<AAction> > actions;
public:

	virtual bool test(XmlParts xmlPart)=0;
	virtual void add(std::shared_ptr<AAction> action);
	virtual void doActions(XMLPartWrapper xmlPart);
};


class GeneralRule :public ARule
{
public:
	virtual bool test(XmlParts xmlPart);
};

class DetectDeclare :public ARule
{
public:
	virtual bool test(XmlParts xmlPart);
};

class DetectProcIns :public ARule
{
public:
	virtual bool test(XmlParts xmlPart);
};

class DetectComment :public ARule
{
public:
	virtual bool test(XmlParts xmlPart);
};

class DetectElement :public ARule
{
public:
	virtual bool test(XmlParts xmlPart);
};

class DetectEndElement :public ARule
{
public:
	virtual bool test(XmlParts xmlPart);
};

class DetectTextElement :public ARule
{
public:
	virtual bool test(XmlParts xmlPart);
};
#endif
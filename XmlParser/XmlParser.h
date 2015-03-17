#ifndef XMLPARSER_H
#define XMLPARSER_H

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
// Application: Project #2 – XmlDocument,2015							//
// Author:      Isira Samarasekera, Syracuse University					//
//              issamara@syr.edu										//
//////////////////////////////////////////////////////////////////////////
/*
* Module Operations:
* ==================
*
* Public Interface:
* =================
* XmlFileParser parser;
* Repository repo;
* std::shared_ptr<DocElement> docElement(new DocElement());
* repo.pushToStack(docElement);
* std::shared_ptr<ARule> rule0(new DetectTextElement());
* std::shared_ptr<AAction> action1(new PushStack(repo));
* rule0->add(action1);
* parser.parse("filePath");

* XmlStringParser stringParser;
* Repository repo;
* std::shared_ptr<DocElement> docElement(new DocElement());
* repo.pushToStack(docElement);
* std::shared_ptr<ARule> rule0(new DetectTextElement());
* std::shared_ptr<AAction> action1(new PushStack(repo));
* rule0->add(action1);
* parser.parse(xmlStringToBeParsed);
* 
* Required Files:
* ===============
* XmlParser.h , XmlParser.cpp
* XmlElement.h , XmlElement.cpp
*
* Build Process:
* ================
*  devenv XmlDocument.sln /debug rebuild
*
*
* Maintenance History:
* ====================
* ver 1.0 : 19 Mar 15
* - first release
*/

#include "Rules.h"
#include <stack>
#include "../XmlElement/XmlElement.h"
namespace XmlProcessing
{
class XmlParser
{
public:
	void parse(std::string content);
	void parse(XmlParts part);
	void add(std::shared_ptr<ARule> rule);
	virtual Toker* getToker(const std::string& content)=0;

	virtual ~XmlParser(){
		delete toker;
	}


private:
	std::vector<std::shared_ptr<ARule>> Rules;
	std::stack<std::shared_ptr<AbstractXmlElement>> _stack;
	Toker* toker;
};

class XmlStringParser:public XmlParser
{
public:
	Toker* getToker(const std::string& content);

};

class XmlFileParser:public XmlParser
{
public:
	Toker* getToker(const std::string& file);

};

}
#endif
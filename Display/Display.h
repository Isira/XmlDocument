#ifndef DISPLAY_H
#define DISPLAY_H

//////////////////////////////////////////////////////////////////////////
// Display.h -  display results on the command line					//
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
*  Display module displays messages in the standard output to demonstratre project #2 requirements
*
* Public Interface:
* =================
* Display display;
* display.RequirementHeader(3);
* display.showInternalParseTree(doc);
* display.showResults(doc);
* display.showFileContent(filePath);
* display.showBreakerDottedLine();
* display.showString(str);
* display.doOperationOnDoc(operation,success,doc);
*
* Required Files:
* ===============
* Display.h, Display.cpp
* XmlDocument.h , XmlDocument.cpp
*
* Build Command:
* ==============
* cl /EHa /DTEST_DISPLAY Display.cpp
*
* Maintenance History:
* ====================
* ver 1.0 : 20 Mar 15
* - first release
*/

#include <string>
#include "../XmlDocument/XmlDocument.h"
class Display
{
private:
	void SuccessfulAddingChild();
	void SuccessfulRemovingChild();
	void UnuccessfulAddingChild();
	void UnuccessfulRemovingChild();

	void progammaticallyBuildXmlDocument();
	void readingFromString();
	void readingFromFile();
	void writeToString();
	void writeToFile();
public:
	void RequirementHeader(int num);
	void showInternalParseTree(const XmlProcessing::XmlDocument& doc);
	void showResults(XmlProcessing::XmlDocument& doc);
	void showFileContent(const std::string& filePath);
	void showBreakerDottedLine();
	void showString(const std::string& str);
	void doOperationOnDoc(const std::string& operation, bool success, const XmlProcessing::XmlDocument& doc);

};
#endif
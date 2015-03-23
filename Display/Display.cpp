//////////////////////////////////////////////////////////////////////////
// Display.cpp -  display results on the command line					//
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

#include "Display.h"
#include "../XmlDocument/XmlDocument.h"

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace XmlProcessing;

//---< Show internal parse tree  >---------------------------

void Display::showInternalParseTree(const XmlDocument& doc)
{
	std::cout << "\nInternal Parse Tree String Representation:";
	std::cout << "\n--------------------------------------------\n\n";
	std::cout << doc;
	std::cout << "\n";
}

//---< show Contents of the file  >---------------------------

void Display::showFileContent(const std::string& filePath)
{
	std::string line;
	std::ifstream in(filePath);
	while (std::getline(in, line))
	{
		std::istringstream iss(line);
		std::cout << line << "\n";
	}
}

//---< show results in the doc  >---------------------------

void Display::showResults(XmlDocument& doc)
{
	std::vector<sPtr> results = doc.select();
	if (results.empty())
	{
		std::cout << "\nempty vector returned, ie: no results found\n";
		return;
	}

	for (auto it : results)
	{
		if (it == nullptr)
		{
			std::cout << "\nnullpointer returned, ie: no results found\n";
		}
		else
		{
			std::string xmlString = it->toString();
			std::cout << xmlString;
			std::cout << "\n";
		}
	}
}


//---< display the requirement header  >---------------------------

void Display::RequirementHeader(int num)
{
	std::cout << "\nDemonstrating Requirement " << num <<": \n";
	std::cout << "============================ \n\n";
}


//---< show a breaker dotted line  >---------------------------

void Display::showBreakerDottedLine()
{
	std::cout << "---------------------------------------------------------\n\n";
}

//---< show string in the standard output  >---------------------------

void Display::showString(const std::string& str)
{
	std::cout << str << std::endl;
}

//---< show results of a operation on a document  >---------------------------

void Display::doOperationOnDoc(const std::string& operation, bool success, const XmlDocument& doc)
{
	std::cout << "\n";
	std::cout << operation;
	std::cout << "------------------------------------------------------------------------\n";
	std::cout << "\n\nSuccessful: " << (success ? "True" : "False") << " \n";
	std::cout << "Resulting Xml Tree: " << " \n";
	std::cout << doc;
	std::cout << "\n \n";
}



#ifdef TEST_DISPLAY
void main()
{
	Display display;
	display.showString("Hello World");
	display.RequirementHeader(5);
	display.showBreakerDottedLine();
	display.showFileContent("LectureNote.xml");
	XmlDocument doc;
	display.showInternalParseTree(doc);
}
#endif
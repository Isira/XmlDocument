#ifndef TESTEXECUTIVE_H
#define TESTEXECUTIVE_H
//////////////////////////////////////////////////////////////////////////////////////
// TestExecutive.h -  Demonstrates the requirements of the XmlDocument project		//
//																					//
// ver 1.0																			//
// ---------------------------------------------------------------------------------//
// copyright © Isira Samarasekera, 2015												//
// All rights granted provided that this notice is retained							//
// ---------------------------------------------------------------------------------//
// Language:    Visual C++, Visual Studio Ultimate 2013								//
// Platform:    Mac Book Pro, Core i5, Windows 8.1									//
// Application: Project #2 – XmlDocument,2015										//
// Author:      Isira Samarasekera, Syracuse University								//
//              issamara@syr.edu													//
//////////////////////////////////////////////////////////////////////////////////////
/*
* Module Operations:
* ==================
* TestExecutive is responsible for driving the requirement demonstration for project #2
* 
* Public Interface:
* =================
* 	TestExecutive executive = TestExecutive("path/to/xmlFile");
*	executive.Requirement3();
*	executive.Requirement4();
*	executive.Requirement5();
*	executive.Requirement6();
*	executive.Requirement7();
*	executive.Requirement8();
*	executive.Requirement9();
*	executive.Requirement10();
*
* Required Files:
* ===============
* TestExecutive.h, TestExecutive.cpp
* XmlDocument.h , XmlDocument.cpp
*
* Build Command:
* ==============
* cl /EHa /DTEST_TESTEXECUTIVE TestExecutive.cpp
*
* Maintenance History:
* ====================
* ver 1.0 : 20 Mar 15
* - first release
*/

#include <string>
#include "../DocumentBuilder/DocumentBuilder.h"
#include "../Display/Display.h"

namespace XmlProcessing
{
	class TestExecutive
	{
	private:
		std::string _filePath;
		DocumentBuilder builder;
		Display display;
		void SuccessfulAddingChild();
		void SuccessfulRemovingChild();
		void UnuccessfulAddingChild();
		void UnuccessfulRemovingChild();
		void progammaticallyBuildXmlDocument();
		void addAttribute();
		void removeAttribute();
		void readingFromString();
		void readingFromFile();
		void writeToString();
		void writeToFile();
	
	public:
		TestExecutive(std::string filePath);
		void displayTreeStructure();
		void Requirement3();
		void Requirement4();
		void Requirement5();
		void Requirement6();
		void Requirement7();
		void Requirement8();
		void Requirement9();
		void Requirement10();
		void Requirement11();
	};
}

#endif
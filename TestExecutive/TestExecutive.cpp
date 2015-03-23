//////////////////////////////////////////////////////////////////////////
// TestExecutive.cpp -  Contains actions								//
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

#include "TestExecutive.h"
#include "../XmlDocument/XmlDocument.h"
#include "../XmlElement/XmlElementFactory.h"
#include "../Display/Display.h"

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace XmlProcessing;

TestExecutive::TestExecutive(std::string filePath) :_filePath(filePath)
{
}

void TestExecutive::displayTreeStructure()
{
	std::cout << "\nDisplaying Tree Structure\n";
	XmlDocument doc(_filePath, XmlDocument::sourceType::filename);
	builder.build(doc);
	std::cout << doc;
	std::cout << "\n";
}

//----< Demontrate a facility to read XML strings and files and build an internal parse tree representation wrapped in a
//Document object >---------------------------

void TestExecutive::Requirement3()
{
	display.RequirementHeader(3);

	{
		std::string xmlString = "< ? xml version = \"1.0\" encoding = \"utf - 8\" ? >< ? Take version = \"1.0\" encoding = \"utf - 8\" ? ><!--XML test---- - case --><LectureNote course = \"CSE681\">"
			"<title>XML Example #1 < / title ><reference><title>Programming Microsoft.Net< / title><author>Jeff Prosise <note Company = 'Wintellect'>< / note>< / author>"
			"<publisher>Microsoft Press< / publisher><date>2002 < / date ><page>608 < / page >< / reference>"
			"<comment>Description of PCDATA< / comment>< / LectureNote>";

		display.showString("Xml String Parsed:");
		display.showString(xmlString);

		XmlDocument doc(xmlString);
		builder.build(doc);
		display.showInternalParseTree(doc);
	}
	display.showBreakerDottedLine();
	{
		display.showString("\n");
		display.showString("Xml File Parsed: ");
		display.showString(_filePath);

		XmlDocument doc(_filePath, XmlDocument::sourceType::filename);
		builder.build(doc);
		display.showInternalParseTree(doc);
	}
}

//----<Demonstrating XmlDocument move construction and move assignment operations and  read and write operations to and from
// both strings and files.  >---------------------------

void TestExecutive::Requirement4()
{
	display.RequirementHeader(4);

	XmlDocument doc(_filePath, XmlDocument::sourceType::filename);
	builder.build(doc);

	display.showString("\n");
	std::cout << "Original Document:\n";
	display.showInternalParseTree(doc);

	XmlDocument movedDoc(std::move(doc));

	display.showString("\nMove constructing XmlDocument");
	display.showString("--------------------------------");
	display.showInternalParseTree(movedDoc);

	display.showString("\nMove assigning xmlDocument");
	display.showString("-----------------------------");

	XmlDocument emptyDoc;
	display.showString("\nXmlDocument before assigning");
	display.showInternalParseTree(emptyDoc);
	
	emptyDoc = std::move(movedDoc);

	display.showString("\nXmlDocument after assigning");
	display.showInternalParseTree(emptyDoc);
	
	display.showString("\nSaving to a File");
	emptyDoc.save("EmptyXml.xml");

	display.showString("\n");
	display.showString("Reading from the saved File\n");

	display.showFileContent("EmptyXml.xml");
	display.showString("\n");

}

//----< Demonstrating finding any element based on a unique id attribute  >---------------------------

void TestExecutive::Requirement5()
{
	display.RequirementHeader(5);
	
	XmlDocument doc(_filePath, XmlDocument::sourceType::filename);
	builder.build(doc);

	std::cout << "\nFind Element with Attribute \"Company\" and value \"Wintellect\"";
	doc.elementsWithAttribute("Company","Wintellect");
	display.showResults(doc);

	display.showString("\nFind Element with Attribute \"Company\" and value \"Microsoft\"");
	doc.elementsWithAttribute("Company", "Microsoft");
	display.showResults(doc);
}


//----< Demonstrating finding collection if elements with specific tag   >---------------------------

void TestExecutive::Requirement6()
{
	display.RequirementHeader(6);

	XmlDocument doc(_filePath, XmlDocument::sourceType::filename);
	builder.build(doc);
	display.showString("\nFind Elements with Tag \"title\"");
	doc.elements("title");

	display.showResults(doc);

	display.showString("\nFind Elements with Tag \"Isira\"");
	doc.elements("Isira");

	display.showResults(doc);
}

//----< Demonstrating successful add child  >---------------------------

void TestExecutive::SuccessfulAddingChild()
{
	XmlDocument doc(_filePath, XmlDocument::sourceType::filename);
	builder.build(doc);

	std::vector<sPtr> results = doc.element("LectureNote").select();
	if (!results.empty())
	{
		sPtr result = results[0];
		std::shared_ptr<AbstractXmlElement> taggedElement = XmlElementFactory::makeTaggedElement("TaggedElement");
		taggedElement->addAttrib("NewAttribute", "NewValue");
		bool success = result->addChild(taggedElement);

		std::string operation = "\nAdding a tagged element with the Tag \"TaggedElement\" as a child to Lecture Note element\n";

		display.doOperationOnDoc(operation, success, doc);
	}
	
}

//----< Demonstrating successful remove child  >---------------------------

void TestExecutive::SuccessfulRemovingChild()
{
	XmlDocument doc(_filePath, XmlDocument::sourceType::filename);
	builder.build(doc);

	std::vector<sPtr> results = doc.element("LectureNote").select();
	if (!results.empty())
	{
		sPtr rootElement = results[0];
		std::vector<sPtr> children = rootElement->children();
		if (!children.empty())
		{
			sPtr firstChild = children[0];
			bool success = rootElement->removeChild(firstChild);
			std::string operation = "\nRemoving first Child of the Lecture note element \n";
			display.doOperationOnDoc(operation, success, doc);
		}

	}
}

//----< Demonstrating unsuccessful add child  >---------------------------

void TestExecutive::UnuccessfulAddingChild()
{
	XmlDocument doc(_filePath, XmlDocument::sourceType::filename);
	builder.build(doc);

	sPtr docElement = doc.docElement();
	sPtr anotherTagged = XmlElementFactory::makeTaggedElement("anotherTagged");
	bool success = docElement->addChild(anotherTagged);

	std::string operation = "\nTrying to add a tagged element to the root element\n";
	display.doOperationOnDoc(operation, success, doc);

}

//----< Demonstrating unsuccessful remove child  >---------------------------

void TestExecutive::UnuccessfulRemovingChild()
{
		XmlDocument doc(_filePath, XmlDocument::sourceType::filename);
		builder.build(doc);
		std::vector<sPtr> results1 = doc.element("LectureNote").select();
		std::vector<sPtr> results2 = doc.element("publisher").select();
		if (!results1.empty() && !results2.empty())
		{
			sPtr rootElement = results1[0];
			sPtr firstChild = results2[0];

			bool success = rootElement->removeChild(firstChild);

			std::string operation = "\nTrying to removing a child with tag name publisher of the LectureNote element \n";
			display.doOperationOnDoc(operation, success, doc);
		}

}

//----< Demonstrating programmatically building document tree  >---------------------------

void TestExecutive::progammaticallyBuildXmlDocument()
{
	display.showString("\nProgrammatically Building an Xml Document ");
	display.showString("-------------------------------------------\n");
	sPtr pRoot =  XmlElementFactory::makeTaggedElement("root");
	sPtr pChild1 = XmlElementFactory::makeTaggedElement("child1");
	pRoot->addChild(pChild1);
	sPtr pChild2 = XmlElementFactory::makeCommentElement("this is a comment");
	pRoot->addChild(pChild2);
	sPtr pGrandChild11 = XmlElementFactory::makeTextElement("grandChild11 text element");
	pChild1->addChild(pGrandChild11);
	sPtr pGrandChild12 = XmlElementFactory::makeTaggedElement("greatGrandChild11");
	pGrandChild12->addAttrib("Value", "Name");
	pChild1->addChild(pGrandChild12);
	
	sPtr xDocumentElement = XmlElementFactory::makeDocElement(pRoot);
	xDocumentElement->addChild(XmlElementFactory::makeXmlDeclarElement());
	XmlDocument _doc("");
	_doc.setDocElement(xDocumentElement);
	
	display.showInternalParseTree(_doc);
}

//----< Demonstrate  Requirement 7 >---------------------------

void TestExecutive::Requirement7()
{

	display.RequirementHeader(7);
	SuccessfulAddingChild();
	SuccessfulRemovingChild();
	UnuccessfulAddingChild();
	UnuccessfulRemovingChild();
	progammaticallyBuildXmlDocument();
}

//----< Demonstrate  given a pointer to any element, returning attribute name pairs and children >---------------------------

void TestExecutive::Requirement8()
{
	display.RequirementHeader(8);

	XmlDocument doc(_filePath, XmlDocument::sourceType::filename);
	builder.build(doc);
	std::vector<sPtr> results = doc.element("LectureNote").select();

	if (!results.empty() && results[0] != nullptr)
	{
		sPtr element = results[0];
		display.showString("\nShow name,values for attributes for element with tag \"LectureNote\": \n");
		if (element->attribs().empty())
		{
			display.showString("\nEmpty Vector returned, ie: No attributes exists for the element\n");
		}
		else
		{
			for (auto it : element->attribs())
			{
				display.showString( "Name: " + it.first + " Value: " + it.second);
			}
		}
		display.showString("\n\nShow children  for element with tag \"LectureNote\":" );
		if (element->attribs().empty())
		{
			display.showString("\nEmpty Vector returned, ie: No child exists for the element");
		}
		else
		{
			for (auto it : element->children())
			{
				display.showString(it->toString());
				display.showString("\n-------------------------------");
			}
		}
		
	}
	display.showString("");
}

//----< add  an attribute name - value pair from any element node >---------------------------

void TestExecutive::addAttribute()
{
	display.showString("\nAdd Attribute \"type\" with value \"book\"to element with tag \"reference\": ");
	XmlDocument doc(_filePath, XmlDocument::sourceType::filename);
	builder.build(doc);

	std::vector<sPtr> results = doc.element("reference").select();
	if (!results.empty() && results[0] != nullptr)
	{
		sPtr element = results[0];
		if (element->addAttrib("type", "book"))
		{
			display.showString("Operation successful");
		}
		else
		{
			display.showString("Operation Unsuccesfull");
		}
		std::cout << doc;
	}
}

//----< remove an attribute name - value pair from any element node >---------------------------

void TestExecutive::removeAttribute()
{
	display.showString("\nRemove Attribute \"type\" from element with tag \"reference\": \n");
	XmlDocument doc(_filePath, XmlDocument::sourceType::filename);
	builder.build(doc);
	std::vector<sPtr> results = doc.element("reference").select();
	if (!results.empty() && results[0] != nullptr)
	{
		sPtr element = results[0];
		if (element->removeAttrib("type"))
		{
			display.showString("removing Attribute successful");
		}
		else
		{
			display.showString("Operation Unsuccesfull");
		}
		display.showInternalParseTree(doc);
	}

	display.showString("\n\nRemove Attribute \"type\" from element with tag \"reference\": \n");
	results = doc.element("reference").select();
	if (!results.empty() && results[0] != nullptr)
	{
		sPtr element = results[0];
		if (element->removeAttrib("type"))
		{
			display.showString("removing Attribute successful");
		}
		else
		{
			display.showString("Operation Unsuccesfull");
		}
		display.showInternalParseTree(doc);
	}
	display.showString("\n\n");
}

//----< Demonstrating Requirement 9 >---------------------------

void TestExecutive::Requirement9()
{
	display.RequirementHeader(9);
	addAttribute();
	removeAttribute();
}

//----< Demonstrating making internal parse tree from a string >---------------------------

void TestExecutive::readingFromString()
{
	std::string xmlString = "< ? xml version = \"1.0\" encoding = \"utf - 8\" ? >< ? Take version = \"1.0\" encoding = \"utf - 8\" ? ><!--XML test---- - case --><LectureNote course = \"CSE681\">"
		"<title>XML Example #1 < / title ><reference><title>Programming Microsoft.Net< / title><author>Jeff Prosise <note Company = 'Wintellect'>< / note>< / author>"
		"<publisher>Microsoft Press< / publisher><date>2002 < / date ><page>608 < / page >< / reference>"
		"<comment>Description of PCDATA< / comment>< / LectureNote>";

	display.showString("\nXml String Parsed:\n" + xmlString);

	XmlDocument doc(xmlString);
	builder.build(doc);
	display.showInternalParseTree(doc);
}

//----< Demonstrating making internal parse tree from a file >---------------------------

void TestExecutive::readingFromFile()
{
	display.showString( "\nXml File Parsed: " + _filePath);

	XmlDocument doc(_filePath, XmlDocument::sourceType::filename);
	builder.build(doc);
	display.showInternalParseTree(doc);
}

//----< Demonstrating  internal parse tree to a string >---------------------------

void TestExecutive::writeToString()
{
	XmlDocument doc(_filePath, XmlDocument::sourceType::filename);
	builder.build(doc);
	display.showString("\nWritting to a string");
	std::ostringstream oss;
	oss << doc;
	std::string xml = oss.str();

	display.showString("\nReading the xml Content from string:\n");
	std::cout << xml;
	std::cout << "\n\n";
}

//----< Demonstrating internal parse tree to a file >---------------------------

void TestExecutive::writeToFile()
{
	XmlDocument doc(_filePath, XmlDocument::sourceType::filename);
	builder.build(doc);
	display.showString( "\nSaving to a File");
	doc.save("duplicate.xml");

	display.showString("\nReading from the saved File\n");
	display.showFileContent("duplicate.xml");
	display.showString("\n");

}

//----< Demonstrating requirement 10 >---------------------------

void TestExecutive::Requirement10()
{
	display.RequirementHeader(10);
	
	readingFromString();
	readingFromFile();
	writeToString();
	writeToFile();
	
}

#ifdef TEST_TESTEXECUTIVE
int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		std::cout
			<< "\n  please enter name of file to process on command line\n\n";
		return 1;
	}

	TestExecutive executive(argv[1]);
	executive.Requirement3();
	executive.Requirement4();
	executive.Requirement5();
	executive.Requirement6();
	executive.Requirement7();
	executive.Requirement8();
	executive.Requirement9();
	executive.Requirement10();
}
#endif
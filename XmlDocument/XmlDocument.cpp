///////////////////////////////////////////////////////////////////
// XmlDocument.cpp - a container of XmlElement nodes             //
// Ver 1.2                                                       //
// Application: Help for CSE687 Pr#2, Spring 2015                //
// Platform:    Dell XPS 2720, Win 8.1 Pro, Visual Studio 2013   //
// Author:      Jim Fawcett, CST 4-187, 443-3948                 //
//              jfawcett@twcny.rr.com                            //
///////////////////////////////////////////////////////////////////

#include <iostream>
#include "XmlDocument.h"
#include "../XmlParser/XmlParser.h"
#include "../AbstractXmlElementVisitor/Visitors.h"
using namespace XmlProcessing;

XmlProcessing::XmlDocument::XmlDocument(const std::string& src, sourceType srcType)
{
	XmlParser *parser= nullptr;
	if (srcType == filename)
	{
		parser = new XmlFileParser();
	}
	else if (srcType == string)
	{
		parser = new XmlStringParser();
	}
	Repository repo;
	pDocElement_ = makeDocElement();
	repo.pushToStack(pDocElement_);

	std::shared_ptr<ARule> rule0(new DetectTextElement());
	std::shared_ptr<ARule> rule1(new DetectProcIns());
	std::shared_ptr<ARule> rule2(new DetectComment());
	std::shared_ptr<ARule> rule3(new DetectElement());
	std::shared_ptr<ARule> rule4(new DetectEndElement());
	std::shared_ptr<ARule> rule5(new DetectDeclare());

	std::shared_ptr<AAction> action1(new PushStack(repo));
	std::shared_ptr<AAction> action2(new PopStack(repo));

	rule0->add(action1);
	rule0->add(action2);

	rule1->add(action1);
	rule1->add(action2);

	rule2->add(action1);
	rule2->add(action2);

	rule3->add(action1);

	rule4->add(action2);

	rule5->add(action1);
	rule5->add(action2);

	parser->add(rule0);
	parser->add(rule1);
	parser->add(rule2);
	parser->add(rule3);
	parser->add(rule4);
	parser->add(rule5);

	parser->parseFile(src);

	delete parser;
}

std::string XmlDocument::toString()
{
	return pDocElement_->toString();
}

XmlDocument& XmlDocument::element(const std::string& tag)
{
	ElementFinderVisitor visitor(tag);
	pDocElement_->accept(visitor);
	std::vector<AbstractXmlElement*> elems = visitor.select();
	found_.push_back((elems[0]));
	return *this;
}

XmlDocument& XmlDocument::elements(const std::string& tag)
{
	ElementFinderVisitor visitor(tag);
	pDocElement_->accept(visitor);
	std::vector <AbstractXmlElement*> elems = visitor.select();
	found_.insert(found_.end(), elems.begin(), elems.end());
	return *this;
}

XmlDocument& XmlDocument::children(const std::string& tag)
{
	std::vector <AbstractXmlElement*> elems;
	for (auto it : found_)
	{
		ChildrenFinderVisitor visitor(*it,tag);
		it->accept(visitor);
		std::vector<AbstractXmlElement*> results = visitor.select();
		elems.insert(elems.end(), results.begin(),results.end());
	}
	found_ = std::move(elems);
	return *this;
}

XmlDocument& XmlDocument::descendents(const std::string& tag)
{
	std::vector <AbstractXmlElement*> elems;
	for (auto it : found_)
	{
		DependentsFinderVisitor visitor(*it, tag);
		it->accept(visitor);
		std::vector<AbstractXmlElement*> results = visitor.select();
		elems.insert(elems.end(), results.begin(), results.end());
	}
	found_ = std::move(elems);
	return *this;
}


XmlDocument& XmlDocument::elementsWithAttribute(const std::string& attribute, const std::string& value)
{
	AttributeIDFinderVisitor visitor(attribute, value);
	pDocElement_->accept(visitor);
	std::vector <AbstractXmlElement*> elems = visitor.select();
	found_.insert(found_.end(), elems.begin(), elems.end());
	return *this;
}

std::vector<AbstractXmlElement*> XmlDocument::select()
{
	return std::move(found_);
}


int main(int argc, char* argv[])
{
	std::cout << "\n  Testing XmlDocument class\n "
		<< std::string(23, '=') << std::endl;
	std::cout
		<< "\n  Note that quotes are returned as single tokens\n\n";

	if (argc < 2)
	{
		std::cout
			<< "\n  please enter name of file to process on command line\n\n";
		return 1;
	}

	std::cout << "\n  Processing file " << argv[1];
	std::cout << "\n  " << std::string(16 + strlen(argv[1]), '-') ;

	std::string xmlString = "< ? xml version = \"1.0\" encoding = \"utf - 8\" ? >"
		"<!--XML test---- - case -->"
		"<LectureNote course = \"CSE681\">"
		"<title>XML Example #1 < / title >"
		"<reference>"
		"<title>Programming Microsoft.Net< / title>"
		"<author>Jeff Prosise <note Company = 'Wintellect'>< / note>< / author>"
		"<publisher>Microsoft Press< / publisher>"
		"<date>2002 < / date >"
		"<page>608 < / page >"
		"< / reference>"
		"<comment>Description of PCDATA< / comment>"
		"< / LectureNote>";
	{
		XmlDocument document(argv[1]);
		//std::cout << document.toString();
		// <title>Programming Microsoft .Net</title>
		//document.elements("LectureNote").descendents("author");
		//std::vector<AbstractXmlElement*> results = document.select(); // size needs to be one and the 
		//if(!results.empty() )
		//{
		//	for (auto i : results)
		//	{
		//		std::cout<< i->toString();
		//	}
		//	std::cout<<"\n";
		//}

		//document.elements("LectureNote").descendents("note");
		//std::vector<AbstractXmlElement*> results = document.select(); // size needs to be one and the 
		//if(!results.empty() )
		//{
		//	for (auto i : results)
		//	{
		//		 i->addAttrib("Company","myVal");
		//		 i->addChild(makeTaggedElement("This is the comment"));
		//		 std::cout << i->toString();
		//	}
		//	std::cout<<"\n";
		//}


		document.elements("LectureNote").descendents("note");
		std::vector<AbstractXmlElement*> results = document.select(); // size needs to be one and the 
		if (!results.empty())
		{
			for (auto i : results)
			{
				i->addAttrib("Company", "myVal");
				i->addChild(makeTaggedElement("This is the comment"));
				std::cout << document.toString();
			}
			std::cout << "\n";
		}
	}

	/*{
		XmlDocument document(xmlString,XmlProcessing::XmlDocument::sourceType::string);
		std::cout << document.toString();
	}*/

	{
		XmlDocument document(xmlString, XmlProcessing::XmlDocument::sourceType::string);
		document.elementsWithAttribute("Company","Wintellect");

		std::vector<AbstractXmlElement*> results = document.select(); // size needs to be one and the 
		if (!results.empty())
		{
			for (auto i : results)
			{
				std::cout << i->toString();
			}
			std::cout << "\n";
		}
	}

}


//////////////////////////////////////////////////////////////////////////
// Visitors.cpp -  Contains actions										//
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

#include "Visitors.h"
#include "../XmlElement/XmlElement.h"
#include <iostream>
#include <memory>
using namespace XmlProcessing;

size_t PrintVisitor::count = 0;
size_t PrintVisitor::tabSize = 2;

void PrintVisitor::visit(TextElement& element)
{
	std::string spacer(tabSize * ++count, ' ');
	std::string xml = "\n" + spacer + element.value();
	--count;
	std::cout << xml;
}

void PrintVisitor::visit(TaggedElement& element)
{
	std::string spacer(tabSize*++count, ' ');
	std::string xml = "\n" + spacer + "<" + element.value();
	for (auto at : element.attribs())
	{
		xml += " ";
		xml += at.first;
		xml += "=\"";
		xml += at.second;
		xml += "\"";
	}
	xml += ">";
	std::cout << xml;

}

void PrintVisitor::postVisit(TaggedElement& element)
{
	std::string xml;
	std::string spacer(tabSize*count, ' ');
	xml += "\n" + spacer + "</" + element.value() + ">";
	--count;
	std::cout << xml;
}
void PrintVisitor::visit(CommentElement& element)
{
	std::string spacer(tabSize * ++count, ' ');
	std::string xml = "\n" + spacer + "<!--" + element.value() + "-->";
	--count;
	std::cout << xml;
}


void PrintVisitor::visit(ProcInstrElement& element)
{
	std::string spacer(tabSize * ++count, ' ');
	std::string xml = "\n" + spacer + "<?xml";
	for (auto at : element.attribs())
	{
		xml += " ";
		xml += at.first;
		xml += "=\"";
		xml += at.second;
		xml += "\"";
	}
	xml += "?>";
	--count;
	std::cout << xml;
}

void PrintVisitor::visit(XmlDeclarElement& element)
{
	std::string spacer(tabSize * ++count, ' ');
	std::string xml = "\n" + spacer + "<?xml";
	for (auto at : element.attribs())
	{
		xml += " ";
		xml += at.first;
		xml += "=\"";
		xml += at.second;
		xml += "\"";
	}
	xml += "?>";
	--count;
	std::cout << xml;
}

ElementFinderVisitor::ElementFinderVisitor(const std::string& tag):_tag(tag)
{
}

void ElementFinderVisitor::visit(TaggedElement& element)
{
	if (element.value() == _tag)
		found.push_back(&element);

}

std::vector<AbstractXmlElement*> &ElementFinderVisitor::select()
{
	return std::move(found);
}

ElementFinderVisitor::~ElementFinderVisitor()
{
}


AttributeIDFinderVisitor::AttributeIDFinderVisitor(const std::string& idAttribute, const std::string& value):
							idAttribute_(idAttribute), value_( value)
{
}

void AttributeIDFinderVisitor::visit(TaggedElement& element)
{
	std::vector<std::pair<std::string, std::string>> atts = element.attribs();
	for (auto it:atts)
	{
		std::string attrib = it.first;
		std::string val = it.second;

		if (attrib == idAttribute_ && val == value_)
		{
			found.push_back(&element);
		}
	}
}
void AttributeIDFinderVisitor::visit(XmlDeclarElement& element)
{
	std::vector<std::pair<std::string, std::string>> atts = element.attribs();
	for (auto it : atts)
	{
		std::string attrib = it.first;
		std::string val = it.second;

		if (attrib == idAttribute_ && val == value_)
		{
			found.push_back(&element);
		}
	}
}
void AttributeIDFinderVisitor::visit(ProcInstrElement& element)
{
	std::vector<std::pair<std::string, std::string>> atts = element.attribs();
	for (auto it : atts)
	{
		std::string attrib = it.first;
		std::string val = it.second;

		if (attrib == idAttribute_ && val == value_)
		{
			found.push_back(&element);
		}
	}
}


std::vector<AbstractXmlElement*>& AttributeIDFinderVisitor::select()
{
	return std::move(found);
}
AttributeIDFinderVisitor::~AttributeIDFinderVisitor(){}

DependentsFinderVisitor::DependentsFinderVisitor(AbstractXmlElement& element, const std::string& tag) :_element(element), _tag(tag){}

void DependentsFinderVisitor::visit(TaggedElement& element)
{
	if (inside)
	{
		if (_tag.empty() || _tag == element.value())
				found.push_back(&element);
	}

	if (&element == &_element)
	{
		inside = true;
	}
}




void DependentsFinderVisitor::postVisit(TaggedElement& element)
{
	if (&element == &_element)
	{
		inside = false;
	}
}

std::vector<AbstractXmlElement*>& DependentsFinderVisitor::select()
{
	return std::move(found);
}
DependentsFinderVisitor::~DependentsFinderVisitor(){}

ChildrenFinderVisitor::ChildrenFinderVisitor(AbstractXmlElement& element, const std::string& tag) :_element(element),_tag(tag){}

void ChildrenFinderVisitor::visit(TaggedElement& element)
{

	if (&element == &_element)
	{
		for (auto child : element.children())
		{
			if (_tag.empty() || _tag == child->value())
			found.push_back(child.get());
		}	

	}
}

std::vector<AbstractXmlElement*>& ChildrenFinderVisitor::select()
{
	return std::move(found);
}
ChildrenFinderVisitor::~ChildrenFinderVisitor(){}

#ifdef TEST_VISITORS

#include "../XmlDocument/XmlDocument.h"

void main(int argc, char* argv[])
{
	// Load the document
	XmlDocument doc(argv[1],XmlDocument::filename);

	// create the visitor
	PrintVisitor visitor;

	// visitor visits the document
	doc.accept(visitor);

	// Get the required details from the document
	//std::cout << doc.toString();
	

}
#endif
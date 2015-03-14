#include "Visitors.h"
#include "../XmlElement/XmlElement.h"
#include <iostream>
#include <memory>
using namespace XmlProcessing;

size_t PrintVisitor::count = 0;
size_t PrintVisitor::tabSize = 2;



bool PrintVisitor::visit(TextElement& element)
{
	std::string spacer(tabSize * ++count, ' ');
	std::string xml = "\n" + spacer + element.value();
	--count;
	std::cout << xml;
	return false;
}

bool PrintVisitor::visit(TaggedElement& element)
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
	return false;

}

bool PrintVisitor::postVisit(TaggedElement& element)
{
	std::string xml;
	std::string spacer(tabSize*count, ' ');
	xml += "\n" + spacer + "</" + element.value() + ">";
	--count;
	std::cout << xml;
	return false;
}
bool PrintVisitor::visit(CommentElement& element)
{
	std::string spacer(tabSize * ++count, ' ');
	std::string xml = "\n" + spacer + "<!--" + element.value() + "-->";
	--count;
	std::cout << xml;
	return false;
}


bool PrintVisitor::visit(ProcInstrElement& element)
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
	return false;
}

bool PrintVisitor::visit(XmlDeclarElement& element)
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
	return false;
}

ElementFinderVisitor::ElementFinderVisitor(const std::string& tag):_tag(tag)
{
}

bool ElementFinderVisitor::visit(TaggedElement& element)
{
	if (element.value() == _tag)
		found.push_back(&element);

	return false;
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

bool AttributeIDFinderVisitor::visit(TaggedElement& element)
{
	std::vector<std::pair<std::string, std::string>> atts = element.attribs();
	for (auto it:atts)
	{
		std::string attrib = it.first;
		std::string val = it.second;

		if (attrib == idAttribute_ && val == value_)
		{
			found.push_back(&element);
			return true;
		}
	}
	return false;
}
bool AttributeIDFinderVisitor::visit(XmlDeclarElement& element)
{
	std::vector<std::pair<std::string, std::string>> atts = element.attribs();
	for (auto it : atts)
	{
		std::string attrib = it.first;
		std::string val = it.second;

		if (attrib == idAttribute_ && val == value_)
		{
			found.push_back(&element);
			return true;
		}
	}
	return false;
}
bool AttributeIDFinderVisitor::visit(ProcInstrElement& element)
{
	std::vector<std::pair<std::string, std::string>> atts = element.attribs();
	for (auto it : atts)
	{
		std::string attrib = it.first;
		std::string val = it.second;

		if (attrib == idAttribute_ && val == value_)
		{
			found.push_back(&element);
			return true;
		}
	}
	return false;
}


std::vector<AbstractXmlElement*>& AttributeIDFinderVisitor::select()
{
	return std::move(found);
}
AttributeIDFinderVisitor::~AttributeIDFinderVisitor(){}

DependentsFinderVisitor::DependentsFinderVisitor(AbstractXmlElement& element, const std::string& tag) :_element(element), _tag(tag){}

bool DependentsFinderVisitor::visit(TaggedElement& element)
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
	return false;
}




bool DependentsFinderVisitor::postVisit(TaggedElement& element)
{
	if (&element == &_element)
	{
		inside = false;
	}
	return false;
}

std::vector<AbstractXmlElement*>& DependentsFinderVisitor::select()
{
	return std::move(found);
}
DependentsFinderVisitor::~DependentsFinderVisitor(){}

ChildrenFinderVisitor::ChildrenFinderVisitor(AbstractXmlElement& element, const std::string& tag) :_element(element),_tag(tag){}

bool ChildrenFinderVisitor::visit(TaggedElement& element)
{

	if (&element == &_element)
	{
		for (auto child : element.children())
		{
			if (_tag.empty() || _tag == child->value())
			found.push_back(child.get());
		}	
		return true;
	}
	return false;
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
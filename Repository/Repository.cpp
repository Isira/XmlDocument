#include "Repository.h"
#include <stack>

void Repository::pushToStack(std::shared_ptr<XmlProcessing::AbstractXmlElement> element)
{
	_elementStack.push(element);
}
std::shared_ptr<XmlProcessing::AbstractXmlElement> Repository::pop()
{
	std::shared_ptr<XmlProcessing::AbstractXmlElement> elem = _elementStack.top();
	_elementStack.pop();
	return elem;
}

void Repository::addToTop(std::shared_ptr<XmlProcessing::AbstractXmlElement> element)
{
	std::shared_ptr<XmlProcessing::AbstractXmlElement> elem = _elementStack.top();
	if (elem != nullptr)
	{
		elem->addChild(element);
	}
	else
		doc_element = element;

}

#ifdef TEST_REPOSITORY
#include <iostream>



void main()
{
	std::cout << "Compiling;" << std::endl;
}
#endif
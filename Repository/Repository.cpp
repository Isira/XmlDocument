//////////////////////////////////////////////////////////////////////////
// Repository.cpp -  Contains actions										//
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
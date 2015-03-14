#ifndef REPOSITORY_H
#define REPOSITORY_H
#include <stack>
#include <memory>
#include "../XmlElement/XmlElement.h"

class Repository
{
public:
	void pushToStack(std::shared_ptr<XmlProcessing::AbstractXmlElement> element);
	std::shared_ptr<XmlProcessing::AbstractXmlElement> pop();
	void addToTop(std::shared_ptr<XmlProcessing::AbstractXmlElement> element);


private:
	std::stack<std::shared_ptr<XmlProcessing::AbstractXmlElement>> _elementStack;
	std::shared_ptr<XmlProcessing::AbstractXmlElement> doc_element;
};
#endif
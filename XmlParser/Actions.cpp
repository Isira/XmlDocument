#include "Actions.h"

void PrintAction::doAction(XMLPartWrapper xmlPart)
{
	std::cout << xmlPart.part().show().c_str() << std::endl;
}

void PushStack::doAction(XMLPartWrapper xmlPart)
{
	std::shared_ptr<XmlProcessing::AbstractXmlElement> ptr = XMLElementFactory::createElement(xmlPart);
	_repo.pushToStack(ptr);
}

void PopStack::doAction(XMLPartWrapper xmlPart)
{
	std::shared_ptr<XmlProcessing::AbstractXmlElement> ptr = _repo.pop();
	_repo.addToTop(ptr);
}

std::shared_ptr<XmlProcessing::AbstractXmlElement> XMLElementFactory::createTaggedElement(XmlParts xmlPart)
{
	std::shared_ptr<XmlProcessing::AbstractXmlElement> ptr = nullptr;
	ptr = XmlProcessing::makeTaggedElement(xmlPart[1]);
	for (int i = 2; i < xmlPart.length() - 1; i += 3)
	{
		std::string attribute = xmlPart[i];
		std::string tValue = xmlPart[i+2];
		std::string value = tValue.substr(1, tValue.length()-2);
		ptr->addAttrib(attribute,value);
	}
	return ptr;
}

std::shared_ptr<XmlProcessing::AbstractXmlElement> XMLElementFactory::createXMLDeclaration(XmlParts xmlPart)
{
	std::shared_ptr<XmlProcessing::AbstractXmlElement> ptr = nullptr;
	ptr = XmlProcessing::makeXmlDeclarElement();
	for (int i = 3; i < xmlPart.length() - 2; i += 3)
	{
		std::string attribute = xmlPart[i];
		std::string tValue = xmlPart[i + 2];
		std::string value = tValue.substr(1, tValue.length() - 2);
		ptr->addAttrib(attribute, value);
	}
	return ptr;
}

std::shared_ptr<XmlProcessing::AbstractXmlElement> XMLElementFactory::createComment(XmlParts xmlPart)
{
	std::shared_ptr<XmlProcessing::AbstractXmlElement> ptr = nullptr;
	
	std::string comment = "";
	for (int i = 3; i < xmlPart.length() - 3; i++)
	{
		comment += xmlPart[i]+" ";
	}
	comment += xmlPart[xmlPart.length() - 3];

	ptr = XmlProcessing::makeCommentElement(comment);
	return ptr;
}

std::shared_ptr<XmlProcessing::AbstractXmlElement> XMLElementFactory::createElement(XMLPartWrapper xmlPart)
{
	
	std::shared_ptr<XmlProcessing::AbstractXmlElement> ptr = nullptr;

	switch (xmlPart.type())
	{
	case PROC_INSTRUCTION:
		ptr = XmlProcessing::makeProcInstrElement(xmlPart.part().show());
		break;
	case DECLARATION:
		ptr = createXMLDeclaration(xmlPart.part());
		break;
	case COMMENT:
		ptr = createComment(xmlPart.part());
		break;
	case TAGGED_ELEMENT:
		ptr = createTaggedElement(xmlPart.part());
		break;
	case TEXT_ELEMENT:
		ptr = XmlProcessing::makeTextElement(xmlPart.part().show());
		break;
	default:
		break;
	}
	return ptr;
}
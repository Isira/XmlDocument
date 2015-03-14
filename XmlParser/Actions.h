#ifndef ACTIONS_H
#define ACTIONS_H

#include "../XmlElementParts/xmlElementParts.h"
#include "../XmlElement/XmlElement.h"
#include "../Repository/Repository.h"
enum NodeType
{
	DECLARATION,
	PROC_INSTRUCTION,
	COMMENT,
	TAGGED_ELEMENT,
	TEXT_ELEMENT,
	UNDEFINED
};

class XMLPartWrapper
{
	XmlParts& _part;
	NodeType _type;
public:
	XMLPartWrapper(XmlParts& part, NodeType type=UNDEFINED) :_part(part), _type(type)
	{
	};

	inline XmlParts part()
	{
		return _part;
	}
	inline NodeType type()
	{
		return _type;
	}
};

class XMLElementFactory
{
	static std::shared_ptr<XmlProcessing::AbstractXmlElement> createTaggedElement(XmlParts xmlPart);
	static std::shared_ptr<XmlProcessing::AbstractXmlElement> createXMLDeclaration(XmlParts xmlPart);
	static std::shared_ptr<XmlProcessing::AbstractXmlElement> createComment(XmlParts xmlPart);
public:
	static std::shared_ptr<XmlProcessing::AbstractXmlElement> createElement(XMLPartWrapper xmlPart);
	
};

class AAction
{
public:
	virtual void doAction(XMLPartWrapper xmlPart) = 0;
};

class PrintAction :public AAction
{
	virtual void doAction(XMLPartWrapper xmlPart);
};

class PushStack :public AAction
{
public:
	Repository& _repo;
	PushStack(Repository& repo):_repo(repo){}
	virtual void doAction(XMLPartWrapper xmlPart);
};

class PopStack :public AAction
{
public:
	Repository& _repo;
	PopStack(Repository& repo) :_repo(repo){}
	virtual void doAction(XMLPartWrapper xmlPart);
};
#endif
#ifndef RULES_H
#define RULES_H
#include "../XmlElementParts/xmlElementParts.h"
#include "Actions.h"
#include <memory>

class ARule
{
	std::vector<std::shared_ptr<AAction> > actions;
public:

	virtual bool test(XmlParts xmlPart)=0;
	virtual void add(std::shared_ptr<AAction> action);
	virtual void doActions(XMLPartWrapper xmlPart);
};


class GeneralRule :public ARule
{
public:
	virtual bool test(XmlParts xmlPart);
};

class DetectDeclare :public ARule
{
public:
	virtual bool test(XmlParts xmlPart);
};

class DetectProcIns :public ARule
{
public:
	virtual bool test(XmlParts xmlPart);
};

class DetectComment :public ARule
{
public:
	virtual bool test(XmlParts xmlPart);
};

class DetectElement :public ARule
{
public:
	virtual bool test(XmlParts xmlPart);
};

class DetectEndElement :public ARule
{
public:
	virtual bool test(XmlParts xmlPart);
};

class DetectTextElement :public ARule
{
public:
	virtual bool test(XmlParts xmlPart);
};
#endif
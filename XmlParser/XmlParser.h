#ifndef XMLPARSER_H
#define XMLPARSER_H

#include "Rules.h"
#include <stack>
#include "../XmlElement/XmlElement.h"
namespace XmlProcessing
{
class XmlParser
{
public:
	void parseFile(std::string file);
	void parse(XmlParts part);
	void add(std::shared_ptr<ARule> rule);
	virtual Toker* getToker(const std::string& content)=0;

	virtual ~XmlParser(){
		delete toker;
	}


private:
	std::vector<std::shared_ptr<ARule>> Rules;
	std::stack<std::shared_ptr<AbstractXmlElement>> _stack;
	Toker* toker;

	
};

class XmlStringParser:public XmlParser
{
public:
	Toker* getToker(const std::string& content);

};

class XmlFileParser:public XmlParser
{
public:
	Toker* getToker(const std::string& file);

};

}
#endif
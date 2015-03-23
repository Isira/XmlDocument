#ifndef ABSTRACTXMLELEMENT_H
#define ABSTRACTXMLELEMENT_H

//////////////////////////////////////////////////////////////////////////
// AbstractXmlElement.h -  base class for all concrete element types  	//
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
// Source:      Jim Fawcett, CST 4-187, 443-3948						//
//              jfawcett@twcny.rr.com									//
//////////////////////////////////////////////////////////////////////////

/* Module Operations :
*=====================
* This is the base class for all concrete element types
* 
* Public Interface :
*=================
* sPtr abstractXmlELement;
* abstractXmlELement->addChild(pChild);
* abstractXmlELement-> removeChild(pChild);
* abstractXmlELement->addAttrib(name,value);
* abstractXmlELement->removeAttrib(name);
* abstractXmlELement->value();
* abstractXmlELement->toString();
* std::vector<std::pair<std::string, std::string>> attbs = abstractXmlELement->attribs();
* abstractXmlELement->children();
* abstractXmlELement->tag();
*
* Required Files :
* ===============
* AbstractXmlElement.h, AbstractXmlElement.cpp
*
* Build Process:
* --------------
*   devenv XmlDocument.sln /debug rebuild
*
* Maintenance History :
*+====================
*ver 1.0 : 20 Mar 15
* -first release
*/

#include <string>
#include <vector>
#include <memory>

namespace XmlProcessing
{

	class AbstractXmlElement
	{
	public:
		virtual bool addChild(std::shared_ptr<AbstractXmlElement> pChild);
		virtual bool removeChild(std::shared_ptr<AbstractXmlElement> pChild);
		virtual bool addAttrib(const std::string& name, const std::string& value);
		virtual bool removeAttrib(const std::string& name);
		virtual std::string value() = 0;
		virtual std::string toString() = 0;
		virtual ~AbstractXmlElement();
		virtual std::vector<std::pair<std::string, std::string>> attribs();
		virtual std::vector<std::shared_ptr<AbstractXmlElement>> children();
		virtual std::string tag();

	protected:
		static size_t count;
		static size_t tabSize;
	};
}
#endif
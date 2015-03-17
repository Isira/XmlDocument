#ifndef VISITORS_H
#define VISITORS_H
//////////////////////////////////////////////////////////////////////////
// Visitors.h - Visitors of the AbstractXmlElement ASTs					//
//																		//
// ver 1.0																//
// ---------------------------------------------------------------------//
// copyright © Isira Samarasekera, 2015									//
// All rights granted provided that this notice is retained				//
// ---------------------------------------------------------------------//
// Language:    Visual C++, Visual Studio Ultimate 2013                 //
// Platform:    Mac Book Pro, Core i5, Windows 8.1						//
// Application: Project #2 – XmlDocument,2015						//
// Author:      Isira Samarasekera, Syracuse University					//
//              issamara@syr.edu										//
//////////////////////////////////////////////////////////////////////////
/*
* Module Operations:
* ==================
*
* Public Interface:
* =================

*
* Required Files:
* ===============
* AbstractXmlElementVisitor.h
* Visitors.h , Visitors.cpp
* XmlElement.h , XmlElement.cpp
*
* Build Process:
* ================
*  devenv XmlDocument.sln /debug rebuild
*
* Maintenance History:
* ====================
* ver 1.0 : 19 Mar 15
* - first release
*/

#include "AbstractXmlElementVisitor.h"
#include <vector>
#include <memory>
#include "../XmlElement/XmlElement.h"
namespace XmlProcessing
{
	class PrintVisitor :public AbstractXmlElementVisitor
	{
	private:
		static size_t count;
		static size_t tabSize;
	public:
		
		virtual void visit(TextElement& element);
		virtual void visit(TaggedElement& element);
		virtual void visit(CommentElement& element);
		virtual void visit(ProcInstrElement& element);
		virtual void visit(XmlDeclarElement& element);

		virtual void postVisit(TaggedElement& element);
		virtual ~PrintVisitor(){}
	};

	class ElementFinderVisitor :public AbstractXmlElementVisitor
	{
		std::vector<AbstractXmlElement*> found;  // query results
		std::string _tag;
	public:
		ElementFinderVisitor(const std::string& tag);
		virtual void visit(TaggedElement& element);
		std::vector<AbstractXmlElement*>& select();
		virtual ~ElementFinderVisitor();
	};

	class DependentsFinderVisitor :public AbstractXmlElementVisitor
	{
		std::vector<AbstractXmlElement*> found;  // query results
		std::string _tag;
		AbstractXmlElement& _element;
		bool inside = false;
	public:
		DependentsFinderVisitor(AbstractXmlElement& element, const std::string& tag);
		virtual void visit(TaggedElement& element);
		virtual void postVisit(TaggedElement& element);
		std::vector<AbstractXmlElement*>& select();
		virtual ~DependentsFinderVisitor();
	};

	class ChildrenFinderVisitor :public AbstractXmlElementVisitor
	{
		std::vector<AbstractXmlElement*> found;  // query results
		std::string _tag;
		AbstractXmlElement& _element;
		bool inside = false;
	public:
		ChildrenFinderVisitor(AbstractXmlElement& element,const std::string& tag);
		virtual void visit(TaggedElement& element);
		std::vector<AbstractXmlElement*>& select();
		virtual ~ChildrenFinderVisitor();
	};

	class AttributeIDFinderVisitor :public AbstractXmlElementVisitor
	{
		std::vector<AbstractXmlElement*> found;  // query results
		std::string idAttribute_;
		std::string value_;
	public:
		AttributeIDFinderVisitor(const std::string& idAttribute, const std::string& value);
		virtual void visit(TaggedElement& element);
		virtual void visit(XmlDeclarElement& element);
		virtual void visit(ProcInstrElement& element);
		std::vector<AbstractXmlElement*>& select();
		virtual ~AttributeIDFinderVisitor();
	};
}

#endif
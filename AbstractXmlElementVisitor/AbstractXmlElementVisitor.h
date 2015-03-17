#ifndef ABSTRACTXMLELEMENTVISITOR_H
#define ABSTRACTXMLELEMENTVISITOR_H
//////////////////////////////////////////////////////////////////////////
// XmlParser.h -  Parses xml content in to AbstractXmlElement AST		//
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
*
* Build Command:
* ==============
* cl /EHa /DTEST_XMLPARSER XmlParser.cpp
*
* Maintenance History:
* ====================
* ver 1.0 : 19 Mar 15
* - first release
*/

#include <memory>
namespace XmlProcessing
{

	class DocElement;
	class TextElement;
	class TaggedElement;
	class CommentElement;
	class ProcInstrElement;
	class XmlDeclarElement;
	class AbstractXmlElement;

	class AbstractXmlElementVisitor
	{
	public:
		virtual void preVisit(TaggedElement& element){ }

		virtual void visit(DocElement& element){  }
		virtual void visit(TextElement& element){  }
		virtual void visit(TaggedElement& element){  }
		virtual void visit(CommentElement& element){  }
		virtual void visit(ProcInstrElement& element){ }
		virtual void visit(XmlDeclarElement& element){}

		virtual void postVisit(TaggedElement& element){}
		virtual ~AbstractXmlElementVisitor(){}
	};
}

#endif
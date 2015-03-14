#ifndef VISITORS_H
#define VISITORS_H
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
		virtual bool visit(DocElement& element);
		virtual bool visit(TextElement& element);
		virtual bool visit(TaggedElement& element);
		virtual bool visit(CommentElement& element);
		virtual bool visit(ProcInstrElement& element);
		virtual bool visit(XmlDeclarElement& element);

		virtual bool postVisit(TaggedElement& element);
		virtual ~PrintVisitor(){}
	};

	class ElementFinderVisitor :public AbstractXmlElementVisitor
	{
		std::vector<AbstractXmlElement*> found;  // query results
		std::string _tag;
	public:
		ElementFinderVisitor(const std::string& tag);
		virtual bool visit(TaggedElement& element);
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
		virtual bool visit(TaggedElement& element);
		virtual bool postVisit(TaggedElement& element);
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
		virtual bool visit(TaggedElement& element);
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
		virtual bool visit(TaggedElement& element);
		virtual bool visit(XmlDeclarElement& element);
		virtual bool visit(ProcInstrElement& element);
		std::vector<AbstractXmlElement*>& select();
		virtual ~AttributeIDFinderVisitor();
	};
}

#endif
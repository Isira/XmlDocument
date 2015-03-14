#ifndef ABSTRACTXMLELEMENTVISITOR_H
#define ABSTRACTXMLELEMENTVISITOR_H
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
		virtual bool preVisit(TaggedElement& element){ return false; }

		virtual bool visit(DocElement& element){ return false; }
		virtual bool visit(TextElement& element){ return false; }
		virtual bool visit(TaggedElement& element){ return false; }
		virtual bool visit(CommentElement& element){ return false; }
		virtual bool visit(ProcInstrElement& element){ return false; }
		virtual bool visit(XmlDeclarElement& element){ return false; }

		virtual bool postVisit(TaggedElement& element){ return false; }
		virtual ~AbstractXmlElementVisitor(){}
	};
}

#endif
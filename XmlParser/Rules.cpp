#include "Rules.h"
#include <regex>

void ARule::add(std::shared_ptr<AAction> action)
{
	actions.push_back(action);
}

void ARule::doActions(XMLPartWrapper xmlPart)
{
	for (std::shared_ptr<AAction> action : actions)
		action->doAction(xmlPart);
}

bool GeneralRule::test(XmlParts xmlPart)
{
	XMLPartWrapper wrapper(xmlPart);
	doActions(xmlPart);
	return true;
}

bool DetectProcIns::test(XmlParts xmlPart) 
{
	if (xmlPart[0] == "<" &&xmlPart[1] == "?" && xmlPart[2] != "xml" &&xmlPart[xmlPart.length() - 2] == "?"
		&&xmlPart[xmlPart.length() - 1] == ">"){
		// Create the element
		XMLPartWrapper wrapper(xmlPart,PROC_INSTRUCTION);
		doActions(wrapper);
	}
	return false;
}


bool DetectDeclare::test(XmlParts xmlPart)
{
	if (xmlPart[0] == "<" &&xmlPart[1] == "?" && xmlPart[2] == "xml" &&xmlPart[xmlPart.length() - 2] == "?"
		&&xmlPart[xmlPart.length() - 1] == ">"){
		// Create the element
		XMLPartWrapper wrapper(xmlPart, DECLARATION);
		doActions(wrapper);
	}
	return false;
}

bool DetectComment::test(XmlParts xmlPart)
{
	if (xmlPart[0] == "<" &&xmlPart[1] == "!" &&xmlPart[2] == "--" &&xmlPart[xmlPart.length() - 2] == "--"
		&& xmlPart[xmlPart.length() - 1] == ">"){
		XMLPartWrapper wrapper(xmlPart, COMMENT);
		doActions(wrapper);
	}
	return false;
}

bool DetectElement::test(XmlParts xmlPart)
{
	if (xmlPart[0] == "<" &&xmlPart[1] != "!" &&xmlPart[1] != "?"&& xmlPart[1] != "/"&& xmlPart[xmlPart.length() - 1] == ">"){
		XMLPartWrapper wrapper(xmlPart, TAGGED_ELEMENT);
		doActions(wrapper);
	}
	return false;
}

bool DetectEndElement::test(XmlParts xmlPart)
{
	if (xmlPart[0] == "<"  && xmlPart[1] == "/"&& xmlPart[xmlPart.length() - 1] == ">"){
		doActions(xmlPart);
	}
	return false;
}

bool DetectTextElement::test(XmlParts xmlPart)
{
	if (xmlPart[0] != "<" && xmlPart[xmlPart.length() - 1] != ">"){
		XMLPartWrapper wrapper(xmlPart, TEXT_ELEMENT);
		doActions(wrapper);
	}
	return false;
}
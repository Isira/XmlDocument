#include "XmlParser.h"
#include "../Repository/Repository.h"

using namespace XmlProcessing;

void XmlParser::add(std::shared_ptr<ARule> rule)
{
	Rules.push_back(rule);
}

void XmlParser::parse(XmlParts part)
{
	for (std::shared_ptr<ARule> rule : Rules)
	{
		if (rule->test(part))
			break;	
	}
}


void XmlParser::parseFile(std::string file)
{
	try
	{
		Toker* toker = getToker(file);
		toker->setMode(Toker::xml);
		XmlParts parts(toker);
		//parts.verbose();                 // uncomment to show token details
		while (parts.get())
			parse(parts);
		std::cout << "\n\n";
	}
	catch (std::exception ex)
	{
		std::cout << "\n  " << ex.what() << "\n\n";
	}
}

Toker* XmlStringParser::getToker(const std::string& content)
{
	return new Toker(content,false);
}

Toker* XmlFileParser::getToker(const std::string& file)
{
	return new Toker(file);
}



//
//----< test stub >--------------------------------------------

#ifdef TEST_XMLPARSER

#include <iostream>
#include <string>

int main(int argc, char* argv[])
{
	std::cout << "\n  Testing XmlParts class\n "
		<< std::string(23, '=') << std::endl;
	std::cout
		<< "\n  Note that quotes are returned as single tokens\n\n";

	if (argc < 2)
	{
		std::cout
			<< "\n  please enter name of file to process on command line\n\n";
		return 1;
	}

	std::cout << "\n  Processing file " << argv[1];
	std::cout << "\n  " << std::string(16 + strlen(argv[1]), '-') << "\n\n";
	 
	XmlParser parser;
	Repository repo;
	std::shared_ptr<DocElement> docElement(new DocElement());
	repo.pushToStack(docElement);


	std::shared_ptr<ARule> rule0(new DetectTextElement());
	std::shared_ptr<ARule> rule1(new DetectProcIns());
	std::shared_ptr<ARule> rule2(new DetectComment());
	std::shared_ptr<ARule> rule3(new DetectElement());
	std::shared_ptr<ARule> rule4(new DetectEndElement());

	std::shared_ptr<AAction> action1(new PushStack(repo));
	std::shared_ptr<AAction> action2(new PopStack(repo));

	rule0->add(action1);
	rule1->add(action1);
	rule1->add(action2);

	rule2->add(action1);
	rule2->add(action2);

	rule3->add(action1);

	rule0->add(action2);
	rule4->add(action2);

	parser.add(rule0);
	parser.add(rule1);
	parser.add(rule2);
	parser.add(rule3);
	parser.add(rule4);
	
	parser.parseFile(argv[1]);
	std::cout << docElement->toString();

}

#endif
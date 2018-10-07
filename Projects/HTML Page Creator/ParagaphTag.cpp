#include "ParagaphTag.h"

ParagraphTag::ParagraphTag(const MyString & new_content, const MyString & new_descr)
{
	content = new_content;
	descr = new_descr;
}

ParagraphTag::ParagraphTag(const ParagraphTag & obj)
{
	content = obj.content;
	descr = obj.descr;
}

ParagraphTag & ParagraphTag::operator=(const ParagraphTag & obj)
{
	if (this != &obj)
	{
		content = obj.content;
		descr = obj.descr;
	}
	return*this;
}

void ParagraphTag::PrintOnConsole() const
{
	std::cout << "Tag: Text | Description: " << descr << " | "
		<< "Text: " << content;
}

void ParagraphTag::PrintInFile(std::ostream & file) const
{
	file << "<p descr=\"" << descr 
		<< "\">"<< content << "</p>";
}

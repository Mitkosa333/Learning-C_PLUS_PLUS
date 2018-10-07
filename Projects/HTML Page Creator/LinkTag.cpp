#include "LinkTag.h"

LinkTag::LinkTag(const MyString& new_content, const MyString& new_descr, const MyString & new_link)
{
	content = new_content;
	descr = new_descr;
	link = new_link;
}

LinkTag::LinkTag(const LinkTag & obj)
{
	content = obj.content;
	descr = obj.descr;
	link = obj.link;
}

LinkTag & LinkTag::operator=(const LinkTag & obj)
{
	if(this != &obj)
	{
		content = obj.content;
		descr = obj.descr;
		link = obj.link;
	}
	return *this;
}

void LinkTag::PrintOnConsole() const
{
	std::cout << "Tag: Link | Description: " << descr << " | " 
		<< "Information: " << content << " | " 
		<< "Link: " << link;
}

void LinkTag::PrintInFile(std::ostream & file) const
{
	file << "<a href=\"" << link
		<< "\" descr=\"" << descr
		<< "\">" << content << "</a>";
}

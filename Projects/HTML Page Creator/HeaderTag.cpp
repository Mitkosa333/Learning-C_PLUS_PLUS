#include "HeaderTag.h"

HeaderTag::HeaderTag()
{
	header_size = 0;
}

HeaderTag::HeaderTag(const MyString& new_content, const MyString& new_descr, const unsigned new_size)
{
	content = new_content;
	descr = new_descr;
	header_size = new_size;
}

HeaderTag::HeaderTag(const HeaderTag & obj)
{
	content = obj.content;
	descr = obj.descr;
	header_size = obj.header_size;
}

HeaderTag & HeaderTag::operator=(const HeaderTag & obj)
{
	if (this != &obj)
	{
		header_size = obj.header_size;
		content = obj.content;
		descr = obj.descr;
	}

	return *this;
}

void HeaderTag::PrintOnConsole() const
{
	std::cout << "Tag: Header | Description: " << descr << " | " 
		<< "Header: " << content << " | " 
		<< "Size of header: " << header_size;
}

void HeaderTag::PrintInFile(std::ostream & file) const
{
	file << "<h" << header_size 
		<< " descr=\"" << descr << "\">" 
		<< content << "</h" << header_size << ">";
}

#include "ImageTag.h"

ImageTag::ImageTag(const MyString & new_content, const MyString & new_descr)
{
	content = new_content;
	descr = new_descr;
}

ImageTag::ImageTag(const ImageTag & obj)
{
	content = obj.content;
	descr = obj.descr;
}

ImageTag & ImageTag::operator=(const ImageTag & obj)
{
	if (this != &obj)
	{
		content = obj.content;
		descr = obj.descr;
	}
	return *this;
}

void ImageTag::PrintOnConsole() const
{
	std::cout << "Tag: Image | Description: " << descr << " | " 
		<< "Link: " << content;
}

void ImageTag::PrintInFile(std::ostream & file) const
{
	file << "<img src=\"" << content 
		<< "\" descr=\"" << descr << "\">";
}

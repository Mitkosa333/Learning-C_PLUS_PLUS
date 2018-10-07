#include "VideoTag.h"

VideoTag::VideoTag(const MyString & new_content, const MyString & new_descr, const MyString & new_link)
{
	content = new_content;
	descr = new_descr;
	link = new_link;
}

VideoTag::VideoTag(const VideoTag & obj)
{
	content = obj.content;
	descr = obj.descr;
	link = obj.link;
}

VideoTag & VideoTag::operator=(const VideoTag & obj)
{
	if (this != &obj)
	{
		content = obj.content;
		descr = obj.descr;
		link = obj.link;
	}

	return *this;
}

void VideoTag::PrintOnConsole() const
{
	std::cout << "Tag: Video | Description: " << descr << " | "
		<< "Information: " << content << " | "
		<< "Link: " << link;
}

void VideoTag::PrintInFile(std::ostream & file) const
{
	file << "<iframe src=\"" << link
		<< "\" descr=\"" << descr
		<< "\">" << content << "</iframe>";
}

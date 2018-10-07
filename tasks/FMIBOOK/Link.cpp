#include "Link.h"

Link::Link(const char * username, const char * text, const char * link, const unsigned randomNum)
{
	setAttributes(username, text, randomNum);

	this->link = new char[strlen(link) + 1];
}

Link::~Link()
{
	delete[] link;
}

void Link::WriteInHTML(const char* username) const
{
	char filename[_MAX_PATH] = { 0 };
	CreateFileNameById(username, filename);
	std::ofstream myFile(filename);

	myFile << "<html>" << std::endl;
	myFile << "<body>" << std::endl;
	myFile << "Posted by: " << creator << "</br>" << std::endl;
	WriteHTMLSpecifics(myFile);
	myFile << "</body>" << std::endl;
	myFile << "</html>" << std::endl;

	myFile.close();
}

void Link::WriteHTMLSpecifics(std::ofstream & file) const
{
	file << "<a href=\"" << link << "\">" << text << "</a>" << std::endl;
}

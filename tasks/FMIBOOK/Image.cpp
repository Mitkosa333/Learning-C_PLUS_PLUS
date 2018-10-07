#include "Image.h"

Image::Image(const char* username, const char* text, const char* path, const unsigned randomNum)
{
	setAttributes(username, text, randomNum);

	this->path = new char[strlen(path) + 1];
}

Image::~Image()
{
	delete[] path;
}

void Image::WriteInHTML(const char* username) const
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

void Image::WriteHTMLSpecifics(std::ofstream & file) const
{
	file << "<img src=\"" << path << "\" " << "alt=\"" << text << "\">" << std::endl;
}

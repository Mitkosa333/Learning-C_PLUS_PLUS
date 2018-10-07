#include "Text.h"

Text::Text(const char* username, const char* text, const unsigned randomNum)
{
	setAttributes(username, text, randomNum);
}

void Text::WriteInHTML(const char* username) const
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

void Text::WriteHTMLSpecifics(std::ofstream& file) const
{
	file << text << std::endl;
}

#include "Post.h"

Post::Post()
{
	creator = nullptr;
	text = nullptr;
	id = 0;
}

Post::~Post()
{
	delete[] creator;
	delete[] text;
}

void Post::changeCreatorName(const char *newUsername)
{
	char* buffer = new char[strlen(newUsername) + 1];
	strncpy(buffer, newUsername, strlen(newUsername) + 1);
	delete[] creator;
	creator = buffer;
}

void Post::setAttributes(const char* username, const char* text, const unsigned randomNum)
{
	char* textBuffer = new char[strlen(text) + 1];
	char* usernameBuffer = new char[strlen(username) + 1];

	strncpy(textBuffer, text, strlen(text) + 1);
	strncpy(usernameBuffer, username, strlen(username) + 1);

	id = randomNum;
	this->text = textBuffer;
	this->creator = usernameBuffer;
}

void Post::CreateFileNameById(const char* username, char* filename) const
{
	unsigned i = 0;
	for (unsigned j = 0; username[j] != '\0'; j++)
	{
		filename[i] = username[j];
		i++;
	}

	filename[i] = ' ';
	i++;

	char numberBuffer[64] = { 0 };
	unsigned idTemp = id;
	unsigned num = 0;

	unsigned sizeId = 0;
	while (idTemp != 0)
	{
		num = idTemp % 10;
		idTemp /= 10;
		numberBuffer[sizeId] = num + '0';
		sizeId++;
	}

	numberBuffer[sizeId] = '\0';

	unsigned sizeIdTEMP = sizeId;

	while (sizeIdTEMP > 0)
	{
		filename[i] = numberBuffer[sizeIdTEMP - 1];
		sizeIdTEMP--;
		i++;
	}
	
	filename[i] = '.';
	i++;
	filename[i] = 'h';
	i++;
	filename[i] = 't';
	i++;
	filename[i] = 'm';
	i++;
	filename[i] = 'l';
	i++;
	filename[i] = '\0';
}


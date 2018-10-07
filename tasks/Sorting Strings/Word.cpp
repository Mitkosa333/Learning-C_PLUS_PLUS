#include "Word.h"

Word::Word()
{
	content = nullptr;
	type = NOT_DEFINED;
}

Word::Word(const Word & obj)
{
	setWord(obj);
}

Word & Word::operator=(const Word & obj)
{
	if (this != &obj)
	{
		delete[] content;
		setWord(obj);
	}

	return *this;
}

Word::~Word()
{
	delete[] content;
}

const char * Word::getType() const
{
	return types[type];
}

const char * Word::getContent() const
{
	return content;
}

void Word::setWord(const Word & obj)
{
	content = new char[strlen(obj.content) + 1];
	strncpy(content, obj.content, strlen(obj.content) + 1);
	type = obj.type;
}

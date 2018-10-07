#include "Hashtag.h"

Hashtag::Hashtag(const char * word)
{
	type = HASHTAG;
	content = new char[strlen(word) + 1];
	strncpy(content, word, strlen(word) + 1);
}

Hashtag & Hashtag::operator=(const Hashtag & obj)
{
	if (this != &obj)
	{
		Word::operator=(obj);
	}
	return*this;
}

unsigned Hashtag::compare(const Word & obj) const
{
	return ((stricmp(getType(), obj.getType()) == 0) && (stricmp(obj.getContent(), content) == 0)) 
		? 100 
		: 0;
} 

Word * Hashtag::clone() const
{
	return new Hashtag(*this);
}

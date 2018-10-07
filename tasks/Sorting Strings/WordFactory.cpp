#include "WordFactory.h"

Word * WordFactory::Create(const char * new_word)
{
	if (new_word[0] == '#' && new_word[1] != '\0')
	{
		char buffer[281];
		unsigned i = 1;
		while (new_word[i] != '\0')
		{
			buffer[i - 1] = new_word[i];
			i++;
		}
		buffer[i - 1] = '\0';

		return new Hashtag(buffer);
	}
	else if ((new_word[0] >= '0' && new_word[0] <= '9') &&
		(new_word[1] >= '0' && new_word[1] <= '9') &&
		(new_word[2] == '-') &&
		(new_word[3] >= '0' && new_word[3] <= '9') &&
		(new_word[4] >= '0' && new_word[4] <= '9') &&
		(new_word[5] == '-') &&
		(new_word[6] >= '0' && new_word[6] <= '9') &&
		(new_word[7] >= '0' && new_word[7] <= '9') &&
		(new_word[8] >= '0' && new_word[8] <= '9') &&
		(new_word[9] >= '0' && new_word[9] <= '9'))
	{
		return new Date(new_word);
	}
	else
	{
		return new Simple(new_word);
	}
}

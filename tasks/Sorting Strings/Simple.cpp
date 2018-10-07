#include "Simple.h"

Simple::Simple(const char * word)
{
	type = SIMPLE;
	content = new char[strlen(word) + 1];
	strncpy(content, word, strlen(word) + 1);
}

Simple & Simple::operator=(const Simple & obj)
{
	if (this != &obj)
	{
		Word::operator=(obj);
	}
	return*this;
}

unsigned Simple::compare(const Word & obj) const
{
	return (strcmp(getType(), obj.getType()) == 0)
		? convert_to_percent(obj.getContent())
		: 0;
}

Word * Simple::clone() const
{
	return new Simple(*this);
}

unsigned Simple::differences(const char * word) const
{
	unsigned size1 = strlen(content);
	unsigned size2 = strlen(word);

	char* buffer1 = new char[size1 + 1];
	strncpy(buffer1, content, size1 + 1);
	cap_into_lower(buffer1);

	char* buffer2 = new char[size2 + 1];
	strncpy(buffer2, word, size2 + 1);
	cap_into_lower(buffer2);

	int** distance = new int*[size1 + 1];
	for (unsigned i = 0; i < size1 + 1; i++)
	{
		distance[i] = new int[size2 + 1];
	}

	for (unsigned i = 0; i < size1 + 1; i++)
	{
		for (unsigned j = 0; j < size2 + 1; j++)
		{
			distance[i][j] = 0;
		}
	}

	for (unsigned i = 0; i < size1 + 1; i++)
	{
		distance[i][0] = i;
	}

	for (unsigned i = 0; i < size2 + 1; i++)
	{
		distance[0][i] = i;
	}

	for (unsigned i = 1; i < size1 + 1; i++)
	{
		for (unsigned j = 1; j < size2 + 1; j++)
		{
			bool cost = (buffer2[j - 1] != buffer1[i - 1]);
			distance[i][j] = Min(Min(distance[i - 1][j] + 1, distance[i][j - 1] + 1), distance[i - 1][j - 1] + cost);

		}
	}

	delete[] buffer1;
	delete[] buffer2;

	int dif = distance[size1][size2];
	for (unsigned i = 0; i < size1 + 1;i++)
	{
		delete[] distance[i];
	}
	delete[] distance;

	return dif;
}

void Simple::cap_into_lower(char * word) const
{
	for (unsigned i = 0; word[i] != '\0'; i++)
	{
		if (word[i] >= 'A' && word[i] <= 'Z')
		{
			word[i] += 'a' - 'A';
		}
	}
}

unsigned Simple::convert_to_percent(const char * word) const
{
	int convert = differences(word);
	return (1 - (convert / Max(strlen(word), strlen(content))));
}

int Min(const unsigned n1, const unsigned n2)
{
	if (n1 < n2)
	{
		return n1;
	}
	else
	{
		return n2;
	}
}

int Max(const unsigned n1, const unsigned n2)
{
	if (n1 > n2)
	{
		return n1;
	}
	else
	{
		return n2;
	}
}

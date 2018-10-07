#include "Text.h"

Text::Text()
{
	lines = nullptr;
	num_lines = 0;
}

Text::Text(std::ifstream & file)
{
	const int max_size = 281;
	char buffer[max_size];
	num_lines = 0;

	if (!file.good())
	{
		lines = nullptr;
	}

	while (file.good())
	{
		file.getline(buffer, max_size);
		if (buffer[0] != '\0')
		{
 			addSentence(buffer);
		}
	}
}

Text::Text(const Text & obj)
{
	setNewText(obj);
}

Text& Text::operator=(const Text & obj)
{
	if (this != &obj)
	{
		clear();
		setNewText(obj);
	}
	return *this;
}

Text::~Text()
{
	clear();
}

void Text::WordCompareData(const char * word)
{
	WordFactory factory;
	Word* new_word = factory.Create(word);
	
	printHashtags();
	sortANDprintMostSimilar(*new_word);
	printMesseges(*new_word);

	delete new_word;
}

Sentence & Text::operator[](const char * new_word)
{
	sortANDprintMostSimilar(new_word);
	return lines[0];
}

Text & Text::operator+=(const Text & obj)
{
	for (unsigned i = 0; i < obj.num_lines; i++)
	{
		addSentence(obj.lines[i]);
	}

	return *this;
}

Text & Text::operator+=(const Sentence & obj)
{
	addSentence(obj);

	return *this;
}

bool Text::extentionCheck() const
{
	return !((num_lines)&(num_lines - 1));
}

void Text::extend()
{
	if (num_lines == 0)
	{
		lines = new Sentence[1];
	}
	else if (extentionCheck())
	{
		Sentence * buffer = new Sentence[num_lines * 2];
		for (unsigned i = 0; i < num_lines; i++)
		{
			buffer[i] = lines[i];
		}
		delete[] lines;
		lines = buffer;
	}
}

void Text::sort(const Word& word)
{
	unsigned max_idx = 0;
	for (unsigned i = 0; i < num_lines - 1; i++)
	{
		max_idx = i;
		for (unsigned j = i + 1; j < num_lines; j++)
		{
			if (lines[j].similarities(word) > lines[max_idx].similarities(word))
			{
				max_idx = j;
			}
		}
		swap(lines[max_idx], lines[i]);
	}
}

void Text::printHashtags() const
{
	std::cout << "-- Hashtags:" << std::endl;
	for (unsigned i = 0; i < num_lines; i++)
	{
		lines[i].printHashtagWords();
	}
	std::cout << std::endl;
}

void Text::addSentence(const char * new_sentence)
{
	extend();
	lines[num_lines] = new_sentence;
	num_lines++;
}

void Text::addSentence(const Sentence & new_sentence)
{
	extend();
	lines[num_lines] = new_sentence;
	num_lines++;
}

void Text::setNewText(const Text & obj)
{
	num_lines = 0;
	for (unsigned i = 0; i < obj.num_lines; i++)
	{
		extend();
		lines[i] = obj.lines[i];
		num_lines++;
	}
}

void Text::sortANDprintMostSimilar(const Word& new_word)
{
	std::cout << "-- The message closest to \"" << new_word.getContent() << " \"is:" << std::endl;
	
	if (lines != nullptr)
	{
		sort(new_word);
		std::cout << lines[0].getSentence()<<std::endl;
	}
	std::cout << std::endl;
}

void Text::sortANDprintMostSimilar(const char * new_word)
{
	std::cout << "-- The message closest to \"" << new_word << " \"is:" << std::endl;

	if (lines != nullptr)
	{
		WordFactory factory;
		Word* word = factory.Create(new_word);
		sort(*word);
		std::cout << lines[0].getSentence() << std::endl;
		
		delete word;
	}
}

void Text::printMesseges(const Word& word)
{
	std::cout << "--Messages arranged by proximity to \"" << word.getContent() << "\":" << std::endl;
	for (unsigned i = 0; i < num_lines; i++)
	{
		std::cout << lines[i].getSentence() << std::endl;
	}
}

void Text::clear()
{
	delete[] lines;
	lines = nullptr;
	num_lines = 0;
}

Text operator+(const Text & first, const Text & second)
{
	Text buffer = first;
	buffer += second;
	return buffer;
}

Text operator+(const Text & first, const Sentence & second)
{
	Text buffer = first;
	buffer += second;
	return buffer;
}

Text operator+(const Sentence & first, const Text & second)
{
	Text buffer = second;
	buffer += first;
	return buffer;
}

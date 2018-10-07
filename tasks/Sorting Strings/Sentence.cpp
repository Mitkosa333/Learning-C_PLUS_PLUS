#include "Sentence.h"

Sentence::Sentence()
{
	content = nullptr;
	num_words = 0;
	words = nullptr;
}

Sentence::Sentence(const char * main_sentence)
{
	setSentenceFromChar(main_sentence);
}

Sentence::Sentence(const Sentence & obj)
{
	setNewSentence(obj);
}

Sentence & Sentence::operator=(const Sentence & obj)
{
	if (this != &obj)
	{
		clear();
		setNewSentence(obj);
	}

	return *this;
}

Sentence & Sentence::operator=(const char * main_sentence)
{
	clear();
	setSentenceFromChar(main_sentence);
	
	return *this;
}

Sentence::~Sentence()
{
	clear();
}

unsigned Sentence::similarities(const Word & obj) const
{
	if (num_words == 0)
	{
		return 0;
	}
	else
	{
		unsigned counter = 0;
		for (unsigned i = 0; i < num_words; i++)
		{
			counter += words[i]->compare(obj);
		}

		return counter /= num_words;
	}
}

void Sentence::printHashtagWords() const
{
	for (unsigned i = 0; i < num_words; i++)
	{
		if (strcmp(words[i]->getType(), "HASHTAG") == 0)
		{
			std::cout << "#" << words[i]->getContent()<<std::endl;
		}
	}
}

const char * Sentence::getSentence() const
{
	return content;
}

bool Sentence::extentionCheck() const
{
	return !((num_words)&(num_words - 1));
}

void Sentence::extend()
{
	if (num_words == 0)
	{
		words = new Word*[1];
	}
	else if (extentionCheck())
	{
		Word ** buffer = new Word*[num_words * 2];
		for (unsigned i = 0; i < num_words; i++)
		{
			buffer[i] = words[i];
		}
		delete[] words;
		words = buffer;
	}
}

void Sentence::setNewSentence(const Sentence & obj)
{
	num_words = 0;
	for (unsigned i = 0; i < obj.num_words; i++)
	{
		extend();

		words[i] = obj.words[i]->clone();
		num_words++;
	}

	content = new char[strlen(obj.content) + 1];
	strncpy(content, obj.content, strlen(obj.content) + 1);
}

void Sentence::addWord(const char * new_word)
{
	extend();
	WordFactory factory;
	words[num_words] = factory.Create(new_word);
	num_words++;
}

void Sentence::clear()
{
	for (unsigned i = 0; i < num_words; i++)
	{
		delete words[i];
	}
	delete[] words;
	words = nullptr;
	num_words = 0;
	delete[] content;
	content = nullptr;
}

void Sentence::setSentenceFromChar(const char * main_sentence)
{
	char buffer[281];
	for (unsigned i = 0; main_sentence[i] != '\0'; i++)
	{
		unsigned j = 0;
		bool flag = false;
		while ((main_sentence[i] >= '0' && main_sentence[i] <= '9') ||
			(main_sentence[i] >= 'A' && main_sentence[i] <= 'Z') ||
			(main_sentence[i] >= 'a' && main_sentence[i] <= 'z') ||
			(main_sentence[i] == '#') ||
			(main_sentence[i] == '-'))
		{
			flag = true;
			buffer[j] = main_sentence[i];
			j++;
			if ((main_sentence[i + 1] == '\0'))
			{
				break;
			}
			i++;
		}

		if (flag == true)
		{
			buffer[j] = '\0';
			addWord(buffer);
		}
	}

	content = new char[strlen(main_sentence) + 1];
	strncpy(content, main_sentence, strlen(main_sentence) + 1);
}

void swap(Sentence & first, Sentence & second)
{
	Sentence temp = first;
	first = second;
	second = temp;
}

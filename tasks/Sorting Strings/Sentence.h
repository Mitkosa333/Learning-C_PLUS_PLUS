#ifndef SENTENCE_H
#define SENTENCE_H

#include <iostream>

#include "WordFactory.h"
#include "Date.h"
#include "Hashtag.h"
#include "Simple.h"

class Sentence
{
public:
	Sentence();
	Sentence(const char*);
	Sentence(const Sentence&);
	Sentence& operator=(const Sentence&);
	Sentence& operator=(const char*);
	~Sentence();

public:
	unsigned similarities(const Word&) const;
	void printHashtagWords() const;
	const char* getSentence() const;

private:
	bool extentionCheck() const;
	void extend();
	void setNewSentence(const Sentence&);
	void addWord(const char*);
	void clear();
	void setSentenceFromChar(const char*);
	
private:
	char* content;
	Word * * words;
	unsigned num_words;
};

void swap(Sentence& first, Sentence& second);

#endif //SENTENCE_H

#ifndef TEXT_H
#define TEXT_H

#include <fstream>
#include "Sentence.h"

class Text
{
public:
	Text();
	Text(std::ifstream&);
	Text(const Text&);
	Text& operator= (const Text&);
	~Text();

public:
	void WordCompareData(const char*);
	Sentence& operator[] (const char*);
	Text& operator+= (const Text&);
	Text& operator+= (const Sentence&);

private:
	bool extentionCheck() const;
	void extend();
	void sort(const Word&);
	void printHashtags() const;
	void addSentence(const char*);
	void addSentence(const Sentence&);
	void setNewText(const Text&);
	void sortANDprintMostSimilar(const Word&);
	void sortANDprintMostSimilar(const char*);
	void printMesseges(const Word&);
	void clear();

private:
	Sentence * lines;
	unsigned num_lines;
};

Text operator+(const Text&, const Text&);
Text operator+(const Text&, const Sentence&);
Text operator+(const Sentence&, const Text&);

#endif // TEXT_H

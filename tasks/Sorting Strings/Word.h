#ifndef WORD_H
#define WORD_H

#include <iostream>

const unsigned MAX_SIZE = 15;
const char types[4][MAX_SIZE] = {"NOT_DEFINED","SIMPLE","HASHTAG","DATE"};

enum WordType
{
	NOT_DEFINED,
	SIMPLE,
	HASHTAG,
	DATE
};

class Word
{
public:
	Word();
	Word(const Word&);
	Word& operator=(const Word&);
	virtual ~Word();

public:
	virtual unsigned compare(const Word&) const = 0;
	virtual Word* clone() const = 0;
	const char* getType() const;
	const char* getContent() const;
private:
	void setWord(const Word&);

protected:
	char* content;
	WordType type;
};

#endif // WORD_H

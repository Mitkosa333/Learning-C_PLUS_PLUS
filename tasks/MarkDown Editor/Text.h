#ifndef TEXT_H
#define TEXT_H

#include <fstream>
#include <iostream>

#include "String.h"

const unsigned italic = 1;
const unsigned bold = 2;
const unsigned combine = 3;
const char symbol = '*';

class Text 
{
private:
	String* content;
	unsigned numOfLines;
	char nameOfSourceFile[_MAX_PATH];

private:
	bool LoadFile();
	void TransformFileExtToMd();
	unsigned CountLinesInFile(std::ifstream&) const;
	void ChooseCommand(const unsigned);
	Text& operator=(const Text&);

public:
	Text();
	Text(const char*);
	Text(const Text&);
	
	unsigned getNumOfLines() const { return numOfLines; }
	unsigned getWordsOnLine(const unsigned);

	void makeHeading(const unsigned);
	void makeItalic(const unsigned, const unsigned, const unsigned);
	void makeBold(const unsigned, const unsigned, const unsigned);
	void makeCombine(const unsigned, const unsigned, const unsigned);
	void addLine(const String&);
	void remove(const unsigned);

	bool SaveFile();
	~Text();
};


#endif // TEXT_H

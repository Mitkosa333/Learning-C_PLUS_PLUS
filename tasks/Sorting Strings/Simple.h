#ifndef SIMPLE_H
#define SIMPLE_H

#include <iostream>
#include "Word.h"

const unsigned BUFFER_SIZE = 38;

class Simple : public Word
{
public:
	Simple(const char*);
	Simple& operator= (const Simple&);
	unsigned compare(const Word&) const;
	Word* clone() const;
private:
	unsigned differences(const char*) const;
	void cap_into_lower(char*) const;
	unsigned convert_to_percent(const char*) const;
};


int Min(const unsigned, const unsigned);
int Max(const unsigned, const unsigned);

#endif //SIMPLE_H

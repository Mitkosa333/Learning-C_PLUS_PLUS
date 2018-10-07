#ifndef HASHTAG_H
#define HASHTAG_H

#include <iostream>
#include "Word.h"

class Hashtag : public Word
{
public:
	Hashtag(const char*);
	Hashtag& operator= (const Hashtag&);
	unsigned compare(const Word&) const;
	Word* clone() const;
};

#endif // HASHTAG_H

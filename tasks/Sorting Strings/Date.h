#ifndef DATE_H
#define DATE_H

#include <iostream>
#include "CheckDates.h"
#include "Word.h"

class Date : public Word
{
public:
	Date(const char*);
	Date& operator= (const Date&);
	unsigned compare(const Word&) const;
	Word* clone() const;

private:
	unsigned dayDifference(const char*) const;
	unsigned checkTheDifference(unsigned, unsigned, unsigned, unsigned, unsigned, unsigned) const;
};

#endif // DATE_H

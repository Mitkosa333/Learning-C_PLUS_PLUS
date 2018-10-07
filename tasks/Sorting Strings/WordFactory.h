#ifndef WORDFACTORY_H
#define WORDFACTORY_H

#include "Word.h"
#include "Date.h"
#include "Hashtag.h"
#include "Simple.h"

class WordFactory
{
public:
	Word * Create(const char*);

};

#endif // WORDFACTORY_H

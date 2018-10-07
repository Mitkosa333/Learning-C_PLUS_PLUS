#ifndef TEXT_H
#define TEXT_H

#include "Post.h"

class Text : public Post
{
public:
	Text(const char*, const char*, const unsigned);


public:
	void WriteInHTML(const char*) const;
	void WriteHTMLSpecifics(std::ofstream& file) const;

};


#endif //TEXT_H

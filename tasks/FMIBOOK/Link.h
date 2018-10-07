#ifndef LINK_H
#define LINK_H

#include "Post.h"

class Link : public Post
{
public:
	Link(const char*, const char*, const char*, const unsigned);
	~Link();

public:
	void WriteInHTML(const char*) const;
	void WriteHTMLSpecifics(std::ofstream& file) const;

private:
	char* link;

};

#endif //LINK_H

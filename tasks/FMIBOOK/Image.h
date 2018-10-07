#ifndef IMAGE_H
#define IMAGE_H

#include "Post.h"

class Image : public Post
{
public:
	Image(const char*, const char*, const char*, const unsigned);
	~Image();

public:
	void WriteInHTML(const char*) const;
	void WriteHTMLSpecifics(std::ofstream& file) const;

private:
	char* path;

};


#endif //IMAGE_H

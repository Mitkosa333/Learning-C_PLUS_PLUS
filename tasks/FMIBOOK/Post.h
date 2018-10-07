#ifndef POST_H
#define POST_H

#include <iostream>
#include <fstream>

const unsigned MAX_TEXT = 4096;

class Post
{
public:
	Post();

	virtual void WriteInHTML(const char*) const = 0;
	virtual void WriteHTMLSpecifics(std::ofstream& file) const = 0;
	virtual ~Post();

public:
	unsigned getId() const { return id; }
	const char* getCreator() const { return creator; }
	void changeCreatorName(const char*);

protected:
	void setAttributes(const char*, const char*, const unsigned);
	void CreateFileNameById(const char*, char*) const;

protected:
	char* creator;
	unsigned id;
	char* text;
};

#endif //POST_H

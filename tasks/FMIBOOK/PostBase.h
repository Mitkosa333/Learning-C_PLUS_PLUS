#ifndef POSTBASE_H
#define POSTBASE_H

#include "Text.h"
#include "Link.h"
#include "Image.h"
#include "Basic.h"

#include <iostream>

const unsigned MAX_LINK = 2048;

class PostBase
{
public:
	PostBase();
	~PostBase();

	Post* getPost(const unsigned) const;

private:
	//Because I don't want the PostBase to be coppied
	PostBase(const PostBase&);
	PostBase& operator= (const PostBase&);

public:
	bool CreatePost(const char*);
	bool RemovePost(const unsigned, char*);
	void ViewPost(const char*);
	void ViewAllPosts(const char*, const char*);

public:
	void ChangeUsername(const char*, const char*);

private:
	bool isUserOwningAnyPosts(const char*) const;
	void CreateFileNameByName(const char*, const char*, char*) const;

private:
	void DoubleMaxPost();
	void Clean();

private:
	Post** posts;
	unsigned numOfPosts;
	unsigned randomNumGenerator;
};




#endif //POSTBASE_H

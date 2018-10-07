#ifndef FMIBOOK_H
#define FMIBOOK_H

#include "UserBase.h"
#include "PostBase.h"

class Fmibook
{
public:
	static Fmibook& getInstance();

public:
	void ChoosingCommand();

private:
	void Info();
	void CreatePost(const char*);
	void RemovePost(const char*);
	void ViewPost(const char*);
	void ViewAllPosts(const char*);
	void ChangeNickname(const char*);

private:
	Fmibook();
	Fmibook(const Fmibook&);
	void operator=(const Fmibook&);
	~Fmibook();

private:
	UserBase allUsers;
	PostBase allPosts;
};


#endif //FMIBOOK_H

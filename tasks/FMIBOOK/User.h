#ifndef USER_H
#define USER_H

#include <iostream>

#include "PostBase.h"

class User 
{
public:
	User();
	User(const char*, const short);
	User(const User&);
	User& operator=(const User&);

	bool getBlockedStatus() const { return is_blocked; }
	const char* getName() const { return nickname; } 
	short getAge() const { return age; }
	unsigned getNumOfPosts() const { return numOfOwnedPosts; }

	~User();
public:
	void ChangeNickname(const char*);
	void setBlockStatus(const bool);
	bool RemovePost(PostBase&, char*);
	void AddToPostNumber();
	void RemoveFromPostNumber();

protected:
	void setName(const char*);

protected:
	void Clear();
	void setNewUser(const char*, const short);
	void setOldUser(const char*, const short, const bool, const unsigned);

protected:
	char* nickname;
	short age;
	bool is_blocked;
	unsigned numOfOwnedPosts;
};

#endif //USER_H

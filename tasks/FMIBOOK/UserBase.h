#ifndef USERBASE_H
#define USERBASE_H

#include "Basic.h"
#include "Admin.h"

class UserBase
{
public:
	UserBase();

	~UserBase();

	bool UserManagement(const char*, const char*);

private:
	//Because I don't want the UserBase to be coppied
	UserBase(const UserBase&);
	UserBase& operator= (const UserBase&);

public:
	User* ChooseUser(const char*);
	Moderator* ChooseModerator(const char*);
	User* YoungestUser();
	User* OldestUser();
	User* UserWithMostPosts();
	void printBlockedUsers() const;
	bool isUsernameFree(const char*);
	unsigned getNumUsers() const { return numOfCurUsers; }
	unsigned getNumMods() const { return numOfCurModerators; }

private:
	void BlockUser(const Moderator&);
	void UnblockUser(const Moderator&);
	void AddUser(const Admin&);
	void AddModerator(const Admin&);
	bool RemoveUser(const Admin&);
	bool RemoveModerator(const Admin&);

private:
	void Clean();
	void DoubleMaxUsers();
	void DoubleMaxMods();

private:
	User* users;
	unsigned numOfCurUsers;
	Moderator* moderators;
	unsigned numOfCurModerators;
	Admin admin;
};


#endif //USERBASE_H

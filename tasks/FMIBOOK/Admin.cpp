#include "Admin.h"

Admin::Admin()
	:Moderator("Admin",21)
{
}

Admin::Admin(const char * nickname, const short age)
	: Moderator(nickname, age)
{

}

Admin & Admin::operator=(const Admin & obj)
{
	if (this != &obj)
	{	
		Moderator::operator=(obj);
	}
	return *this;
}

void Admin::AddUser(User* users, const unsigned curUsers, const char* newUser, const short age) const
{
	User tempUser(newUser, age);
	users[curUsers] = tempUser;
}

void Admin::AddModerator(Moderator* moderators, const unsigned curModerators, const char* newMod, const short age) const
{
	Moderator tempMod(newMod, age); 
	moderators[curModerators] = tempMod;
}

bool Admin::RemoveUser(User* users, unsigned& curUsers, const char* nickname) const
{
	unsigned wantedUser = 0;
	bool found = false;
	while (wantedUser < curUsers)
	{
		if (strcmp(nickname, users[wantedUser].getName()))
		{
			found = true;
			break;
		}
		wantedUser++;
	}

	if (found == false)
	{
		return false;
	}

	for (unsigned i = wantedUser; i + 1 < curUsers; i++)
	{
		users[i] = users[i + 1];
	}
	curUsers--;
	return true;
}

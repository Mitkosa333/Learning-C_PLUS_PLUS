#ifndef ADMIN_H
#define ADMIN_H

#include "Moderator.h"

class Admin : public Moderator
{
public:
	Admin();
	Admin(const char*, const short);
	Admin& operator=(const Admin&);

public:
	void AddUser(User*, const unsigned, const char*, const short) const;
	void AddModerator(Moderator*, const unsigned, const char*, const short) const;
	bool RemoveUser(User*, unsigned&, const char*) const;

};

#endif // ADMIN_H

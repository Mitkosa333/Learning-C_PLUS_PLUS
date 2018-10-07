#ifndef MODERATOR_H
#define MODERATOR_H

#include "User.h"


class Moderator : public User
{
public:
	Moderator();
	Moderator(const char*, const short);
	Moderator& operator=(const Moderator&);

public:
	void Block(User&) const;
	void Unblock(User&) const;
	bool RemovePost(PostBase&, char*);

};


#endif //MODERATOR_H

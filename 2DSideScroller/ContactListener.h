#pragma once
#include <Box2D/Box2D.h>

class ContactListener : public b2ContactListener
{
public:
	int numFootContacts;
	ContactListener();
	~ContactListener();

	virtual void BeginContact(b2Contact *);

	virtual void EndContact(b2Contact *);
};


#include "ContactListener.h"

ContactListener::ContactListener()
{
	numFootContacts = 0;
}

ContactListener::~ContactListener()
{
}

void ContactListener::BeginContact(b2Contact * contact)
{
	void* fixtureUserData = contact->GetFixtureA()->GetUserData();
	if ((int)fixtureUserData == 3)
	{
		numFootContacts++;
	}

	fixtureUserData = contact->GetFixtureB()->GetUserData();
	if ((int)fixtureUserData == 3)
	{
		numFootContacts++;
	}
}

void ContactListener::EndContact(b2Contact * contact)
{
	void* fixtureUserData = contact->GetFixtureA()->GetUserData();
	if ((int)fixtureUserData == 3)
	{
		numFootContacts--;
	}

	fixtureUserData = contact->GetFixtureB()->GetUserData();
	if ((int)fixtureUserData == 3)
	{
		numFootContacts--;
	}
}
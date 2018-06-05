#pragma once
#include "ActorClass.h"

class BulletActor :
	public ActorClass
{
public:
	BulletActor();
	~BulletActor();

	virtual bool Frame() override;
	bool isOutofScreen();
private:

};


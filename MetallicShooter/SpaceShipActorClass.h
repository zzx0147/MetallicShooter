#pragma once
#include "ActorClass.h"
class SpaceShipActorClass :
	public ActorClass
{
public:
	SpaceShipActorClass();
	~SpaceShipActorClass();
	
	virtual bool Frame() override;
};
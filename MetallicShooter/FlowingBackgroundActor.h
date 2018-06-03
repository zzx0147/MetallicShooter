#pragma once
#include "ActorClass.h"
class FlowingBackgroundActor :
	public ActorClass
{
public:
	FlowingBackgroundActor();
	~FlowingBackgroundActor();

	virtual bool Frame() override;
};


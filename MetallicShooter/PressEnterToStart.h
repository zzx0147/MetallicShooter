#pragma once
#include "ActorClass.h"
class PressEnterToStart :
	public ActorClass
{
public:
	PressEnterToStart();
	~PressEnterToStart();

	virtual bool Frame() override;
};
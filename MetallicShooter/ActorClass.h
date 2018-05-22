#pragma once
#include "BitmapClass.h"
class ActorClass :
	public BitmapClass
{
public:
	ActorClass();
	~ActorClass();
	virtual bool Frame();
};


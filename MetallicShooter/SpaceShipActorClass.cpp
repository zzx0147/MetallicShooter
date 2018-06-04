#include "stdafx.h"
#include "SpaceShipActorClass.h"
#include "InputClass.h"


SpaceShipActorClass::SpaceShipActorClass()
{
}


SpaceShipActorClass::~SpaceShipActorClass()
{
}

bool SpaceShipActorClass::Frame()
{
	XMINT2 vector2;
	vector2.x = 0;
	vector2.y = 0;
	
	if (InputClass::GetInputObject()->IsKeyDown(VK_RIGHT))
	{
		vector2.x += 6;
	}
	
	if (InputClass::GetInputObject()->IsKeyDown(VK_LEFT))
	{
		vector2.x -= 6;
	}

	if (InputClass::GetInputObject()->IsKeyDown(VK_UP))
	{
		vector2.y -= 6;
	}

	if (InputClass::GetInputObject()->IsKeyDown(VK_DOWN))
	{
		vector2.y += 6;
	}

	if (vector2.y != 0 && vector2.x != 0)
	{
		vector2.x = vector2.x/6*5;
		vector2.y = vector2.y/6*5;
	}

	SetNextPosX(GetPreviousPosX() + vector2.x);
	SetNextPosY(GetPreviousPosY() + vector2.y);

	return true;
}

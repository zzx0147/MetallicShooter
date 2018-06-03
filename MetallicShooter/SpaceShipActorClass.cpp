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

	if (InputClass::GetInputObject()->IsKeyDown(VK_RIGHT))
	{
		SetNextPosX(GetPreviousPosX() + 5);
	}
	
	if (InputClass::GetInputObject()->IsKeyDown(VK_LEFT))
	{
		SetNextPosX(GetPreviousPosX() -5);
	}

	if (InputClass::GetInputObject()->IsKeyDown(VK_UP))
	{
		SetNextPosY(GetPreviousPosY() - 5);
	}

	if (InputClass::GetInputObject()->IsKeyDown(VK_DOWN))
	{
		SetNextPosY(GetPreviousPosY() + 5);
	}

	return true;
}

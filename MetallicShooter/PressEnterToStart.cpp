#include "stdafx.h"
#include "PressEnterToStart.h"
#include "InputClass.h"
#include "GameStateClass.h"
PressEnterToStart::PressEnterToStart()
{
}


PressEnterToStart::~PressEnterToStart()
{
}

bool PressEnterToStart::Frame()
{
	if (InputClass::GetInputObject()->IsKeyDownOnce(VK_RETURN))
	{
		GameStateClass::SetGameStateEnum(GameStateEnum::INGAME);
	}
	return false;
}

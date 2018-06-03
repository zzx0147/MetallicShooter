#include "stdafx.h"
#include "FlowingBackgroundActor.h"


FlowingBackgroundActor::FlowingBackgroundActor()
{
}


FlowingBackgroundActor::~FlowingBackgroundActor()
{
}

bool FlowingBackgroundActor::Frame()
{
	static bool once = false;
	if (once)
	{
		SetNextPosY(GetPreviousPosY() + 1);
		if (GetPreviousPosY() > 1080)
		{
			SetNextPosY(-1080);
		}
	}
	once = true;
	return false;
}

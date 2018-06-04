#include "stdafx.h"
#include "BulletActor.h"


BulletActor::BulletActor()
{
}


BulletActor::~BulletActor()
{
}

bool BulletActor::Frame()
{
	SetNextPosY(GetPreviousPosY()-5);
	return false;
}

bool BulletActor::isOutofScreen()
{
	int x = GetPreviousPosX();
	int y = GetPreviousPosY();
	int width = GetBitmapWidth();
	int height = GetBitmapHeight();

	if ((y < 0 - height || y>GetScreenHeight()) &&( x < 0 - width || x>GetScreenWidth()))
	{
		return true;
	}
	return false;
}

#include "stdafx.h"
#include "SpaceShipActorClass.h"
#include "InputClass.h"


SpaceShipActorClass::SpaceShipActorClass()
{
}


SpaceShipActorClass::~SpaceShipActorClass()
{
}

bool SpaceShipActorClass::InitalizeBullet(CreatorHelperClass* creatorHelper,ID3D11Device* device, ID3D11DeviceContext* deviceContext, const int& screenWidth, const int& screenHeight, WCHAR* textureFilename, const int& bitmapWidth, const int& bitmapHeight, const int& renderPriority, const int& enabledStatesCount, GameStateEnum* enabledStates)
{
	m_BulletActor = creatorHelper->CreateObject<BulletActor>();
	if (!m_BulletActor)
	{
		return false;
	}
	
	if (!m_BulletActor->Initialize(device, deviceContext, screenWidth, screenHeight, textureFilename,
		bitmapWidth, bitmapHeight, renderPriority, enabledStatesCount, enabledStates))
	{
		return false;
	}
	return true;
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

	if (InputClass::GetInputObject()->IsKeyDownOnce(VK_SPACE))
	{
		m_BulletActor->InitPos(GetNextPosX(), GetNextPosY());
		m_BulletActor->SetNextPosX(GetNextPosX()+GetBitmapWidth()/2-m_BulletActor->GetBitmapWidth()/2);
		m_BulletActor->SetIsVisible(true);
	}

	return true;
}

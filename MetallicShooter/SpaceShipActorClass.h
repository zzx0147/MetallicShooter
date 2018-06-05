#pragma once
#include "ActorClass.h"
#include "BulletActor.h"
#include "CreatorHelperClass.h"
class SpaceShipActorClass :
	public ActorClass
{
public:
	SpaceShipActorClass();
	~SpaceShipActorClass();
	
	bool InitalizeBullet(CreatorHelperClass*,ID3D11Device*, ID3D11DeviceContext* deviceContext, const int&, const int&, WCHAR*, const int&, const int&, const int&, const int&, GameStateEnum*);

	virtual bool Frame() override;
private:
	BulletActor* m_BulletActor = nullptr;
	int m_NumberOfBullets = 30;
	int m_bulletCount = 0;
};
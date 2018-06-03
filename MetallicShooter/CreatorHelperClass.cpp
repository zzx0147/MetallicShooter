#include "stdafx.h"
#include "CreatorHelperClass.h"


CreatorHelperClass::CreatorHelperClass()
{
}

CreatorHelperClass::~CreatorHelperClass()
{
}

bool CreatorHelperClass::Initalize(RenderManager* renderManager, ActorManager* actorManager)
{
	if (!renderManager)
	{
		return false;
	}
	if (!actorManager)
	{
		return false;
	}

	m_RenderManager = renderManager;
	m_ActorManager = actorManager;
	
	return true;
}

//template<class T>
//T* CreatorHelperClass::CreateObject()
//{
//	T* temp = new T();
//	return temp;
//}
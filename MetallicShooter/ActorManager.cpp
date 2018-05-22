#include "stdafx.h"
#include "ActorManager.h"


ActorManager::ActorManager()
{
}


ActorManager::~ActorManager()
{
}

void ActorManager::addActor(ActorClass* newActor)
{
	ActorList.push_back(newActor);
}

void ActorManager::Frame()
{
	list<ActorClass*>::iterator itor;
	for (itor = ActorList.begin(); itor != ActorList.end(); itor++)
	{
		(*itor)->Frame();
	}
}
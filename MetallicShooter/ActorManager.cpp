#include "stdafx.h"
#include "ActorManager.h"


ActorManager::ActorManager()
{
}


ActorManager::~ActorManager()
{
}

bool ActorManager::Initialize()
{
	m_ActorList = new list<ActorClass*>();
	return true;
}

void ActorManager::AddActor(ActorClass* newActor)
{
	m_ActorList->push_back(newActor);
}

void ActorManager::Frame()
{
	list<ActorClass*>::iterator itor;
	if (m_ActorList->empty())
	{
		return;
	}

	for (itor = m_ActorList->begin(); itor != m_ActorList->end(); itor++)
	{
		if ((*itor)->GetIsVisible() && (*itor)->GetIsFitState())
		{
			(*itor)->Frame();
		}
	}
}
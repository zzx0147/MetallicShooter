#pragma once
#include <list>
#include "ActorClass.h"
using namespace std;

class ActorManager
{
public:
	ActorManager();
	~ActorManager();
	bool Initialize();
	void Frame();
	void AddActor(ActorClass*);
	
private:
	list<ActorClass*>* m_ActorList = nullptr;
};


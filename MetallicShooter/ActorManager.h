#pragma once
#include <list>
#include "ActorClass.h"
using namespace std;

class ActorManager
{
public:
	ActorManager();
	~ActorManager();
	void addActor(ActorClass*);
	void Frame();
private:
	list<ActorClass*> ActorList;
};


#pragma once
#include "RenderManager.h"
#include "ActorManager.h"

class CreatorHelperClass
{
public:
	CreatorHelperClass();
	~CreatorHelperClass();
	bool Initalize(RenderManager*,ActorManager*);
	
	template<typename T, typename std::enable_if<std::is_base_of<BitmapClass, T>::value>::type* = nullptr>
	T* CreateObject()
	{
		T* temp = new T();
		ActorClass* newActor = dynamic_cast<ActorClass*>(temp);
		if (newActor)
		{
			m_ActorManager->AddActor(newActor);
		}

		m_RenderManager->AddRenderTarget(temp);

		return temp;
	}

	template<typename T, typename std::enable_if<std::is_base_of<BitmapClass, T>::value>::type* = nullptr>
	T* CreateObject(int num)
	{
		T* temp = new T[num];
		ActorClass* newActor = dynamic_cast<ActorClass*>(temp);
		if (newActor)
		{
			for (int i = 0; i < num; ++i)
			{
				m_ActorManager->AddActor(newActor + i);
			}
		}
		for (int i = 0; i < num; ++i)
		{
			m_RenderManager->AddRenderTarget(temp + i);
		}


		return temp;
	}

private:
	RenderManager* m_RenderManager = nullptr;
	ActorManager* m_ActorManager = nullptr;
};
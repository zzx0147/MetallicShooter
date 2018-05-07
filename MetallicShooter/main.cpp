#include "stdafx.h"
#include "SystemClass.h"

int APIENTRY wWinMain(_In_ HINSTANCE hinstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR IpCmdLine,
	_In_ int nCmdShow)
{
	SystemClass* System = new SystemClass;
	if (!System)
	{
		return -1;
	}

	if (System->Initialize())
	{
		System->Run();
	}

	System->Shutdown();
	delete System;
	System = nullptr;

	return 0;
}

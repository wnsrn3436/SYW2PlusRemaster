#include "StdAfx.h"

DWORD WINAPI ThreadProc(LPVOID iParam)
{
	Awake();
	return 0;
}

void Awake()
{
	UseMessageBox(false);
	HasPermission(true);
	LoadScene(SCENE::UNKNOWN_11);

	UseMapEditor(true);
	UsePlayerStart(false);
}
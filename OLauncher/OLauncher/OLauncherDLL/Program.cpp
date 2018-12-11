#include "StdAfx.h"

CodePatcher Patcher;

DWORD WINAPI ThreadProc(LPVOID iParam)
{
	Awake();
	return 0;
}

void Awake()
{
	SetMessageBoxState(false);
	SetPermission(true);
	LoadScene(SCENE::UNKNOWN_11);
}

void SetMessageBoxState(bool useMessageBox)
{
	Patcher.Clear();
	Patcher.Push(useMessageBox ? IACODE::_8B_MOV : IACODE::_C3_RETN);
	Patcher.WritePatch(0x465250);
}

void SetPermission(bool hasPermission)
{
	Patcher.Clear();
	Patcher.Push(hasPermission ? TRUE : FALSE);
	Patcher.WritePatch(0x4ED81C);
}

void LoadScene(SCENE scene)
{
	Patcher.Clear();
	Patcher.Push(scene);
	Patcher.WritePatch(0x4ED818);
}
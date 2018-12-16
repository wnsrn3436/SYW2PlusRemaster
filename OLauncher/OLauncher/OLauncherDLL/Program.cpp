#include "StdAfx.h"

void OnStart()
{
	char dllDirectory[MAX_PATH];
	GetDllDirectory(dllDirectory, _countof(dllDirectory));

	LoadConfigsXml(string(dllDirectory) + string("Configs.xml"));
}

void OnUpdate()
{
	char str[1024] = { 0, };
	sprintf_s(str, "게임 시간 : %d", GetGamePlayTime());

	RECT rt = { 100,100,400,300 };

	HDC dc = GetDC(NULL);
	DrawText(dc, str, -1, &rt, DT_CENTER | DT_WORDBREAK);
	ReleaseDC(NULL, dc);
}
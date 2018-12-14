#include "StdAfx.h"

void OnAwake()
{
	char dllDirectory[MAX_PATH];
	GetDllDirectory(dllDirectory, _countof(dllDirectory));

	LoadConfigsXml(string(dllDirectory) + string("Configs.xml"));
}

void OnUpdate()
{

}
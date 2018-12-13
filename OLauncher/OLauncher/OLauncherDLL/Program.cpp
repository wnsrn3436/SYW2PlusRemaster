#include "StdAfx.h"

void Awake()
{
	UseMessageBox(false);
	HasPermission(true);
	LoadScene(SCENE::UNKNOWN_11);

	UseMapEditor(true);
	UsePlayerStart(false);
	UseMapUnitLoad(true);
}
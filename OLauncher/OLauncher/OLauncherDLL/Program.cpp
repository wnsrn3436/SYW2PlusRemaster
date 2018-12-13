#include "StdAfx.h"

void Awake()
{
	UseMessageBox(false);
	HasPermission(true);
	SetButtonSystem(2);
	SetGameSpeed(4);
	LoadScene(SCENE::UNKNOWN_11);

	//UseMapEditor(true);
	//UsePlayerStart(false);
	//UseMapUnitLoad(true);
	//UseLimitedMapSelect(false);
}
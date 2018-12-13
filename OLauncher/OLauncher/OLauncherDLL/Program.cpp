#include "StdAfx.h"

void Awake()
{
	char dllDirectory[MAX_PATH];
	GetDllDirectory(dllDirectory, _countof(dllDirectory));

	LoadConfigsXml(string(dllDirectory) + string("Configs.xml"));
}

void LoadConfigsXml(string xmlPath)
{
	XMLDocument document;
	document.LoadFile(xmlPath.c_str());

	XMLElement *element = document.RootElement();

	UseMessageBox(find_element(element, "Config[@name='UseMessageBox']")->IntText());
	HasPermission(find_element(element, "Config[@name='HasPermission']")->IntText());
	SetButtonSystem(find_element(element, "Config[@name='SetButtonSystem']")->IntText());
	SetGameSpeed(find_element(element, "Config[@name='SetGameSpeed']")->IntText());
	UseMapEditor(find_element(element, "Config[@name='UseMapEditor']")->IntText());
	UsePlayerStart(find_element(element, "Config[@name='UsePlayerStart']")->IntText());
	UseMapUnitLoad(find_element(element, "Config[@name='UseMapUnitLoad']")->IntText());
	UseLimitedMapSelect(find_element(element, "Config[@name='UseLimitedMapSelect']")->IntText());

	LoadScene(SCENE::UNKNOWN_11);
}
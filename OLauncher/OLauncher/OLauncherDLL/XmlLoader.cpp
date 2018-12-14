#include "StdAfx.h"

void LoadConfigsXml(string xmlPath)
{
	XMLDocument document;
	document.LoadFile(xmlPath.c_str());

	XMLElement *element = document.RootElement();
	element = find_element(element, "Category[@used='1']");

	SetButtonSystem(find_element(element, "Config[@name='SetButtonSystem']")->IntText());
	SetGameSpeed(find_element(element, "Config[@name='SetGameSpeed']")->IntText());
	UseMapEditor(find_element(element, "Config[@name='UseMapEditor']")->IntText());
	UsePlayerStart(find_element(element, "Config[@name='UsePlayerStart']")->IntText());
	UseMapUnitLoad(find_element(element, "Config[@name='UseMapUnitLoad']")->IntText());
	UseLimitedMapSelect(find_element(element, "Config[@name='UseLimitedMapSelect']")->IntText());
}
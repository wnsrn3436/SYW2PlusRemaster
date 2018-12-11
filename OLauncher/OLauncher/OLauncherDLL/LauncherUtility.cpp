#include "StdAfx.h"

CodePatcher Patcher;

void UseMessageBox(bool useMessageBox)
{
	Patcher.Clear();
	Patcher.Push(useMessageBox ? IACODE::_8B_MOV : IACODE::_C3_RETN);
	Patcher.WritePatch(0x465250);
}

void HasPermission(bool hasPermission)
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

void UseMapEditor(bool useMapEditor)
{
	// 맵에디터 변수
	Patcher.Clear();
	Patcher.Push(useMapEditor ? TRUE : FALSE);
	Patcher.WritePatch(0xB93988);

	// 일반게임 팅김 방지
	int patchAddress = 0x41BD8F;
	if (useMapEditor)
	{
		Patcher.Clear();
		for (int i = 0; i < 6; i++)
			Patcher.Push(IACODE::_90_NOP);
		Patcher.WritePatch(patchAddress);
	}
	else
	{
		BYTE jmpAddress[sizeof(int)];
		CalculateJmp(2, patchAddress, 0x41BE46, jmpAddress);

		Patcher.Clear();
		Patcher.Push(2, IACODE::_0F_ESCAPE, IACODE2::_85_JNE_JNZ);
		Patcher.Push(jmpAddress, sizeof(jmpAddress));
		Patcher.WritePatch(patchAddress);
	}
}
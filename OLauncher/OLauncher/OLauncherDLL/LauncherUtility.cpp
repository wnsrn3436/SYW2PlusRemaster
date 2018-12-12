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
		CalculateAddress(6, patchAddress, 0x41BE46, jmpAddress);

		Patcher.Clear();
		Patcher.Push(2, IACODE::_0F_ESCAPE, IACODE2::_85_JNE_JNZ);
		Patcher.Push(jmpAddress, 4);
		Patcher.WritePatch(patchAddress);
	}
}

void UsePlayerStart(bool usePlayerStart)
{
	int patchAddress[]
	{
		0x41F1CF, // 조선 건물
		0x41F251, // 일본 건물
		0x41F293, // 조선, 일본 일꾼
		0x41F2E6, // 명 건물
		0x41F328  // 명 일꾼
	};

	if (usePlayerStart)
	{
		BYTE callAddress[sizeof(int)];

		for (int i = 0; i < sizeof(patchAddress); i++)
		{
			CalculateAddress(5, patchAddress[i], 0x443190, callAddress);

			Patcher.Clear();
			Patcher.Push(IACODE::_E8_CALL);
			Patcher.Push(callAddress, 4);
			Patcher.WritePatch(patchAddress);
		}
	}
	else
	{
		Patcher.Clear();

		for (int i = 0; i < 5; i++)
			Patcher.Push(IACODE::_90_NOP);

		for (int i = 0; i < sizeof(patchAddress); i++)
			Patcher.WritePatch(patchAddress[i]);
	}
}
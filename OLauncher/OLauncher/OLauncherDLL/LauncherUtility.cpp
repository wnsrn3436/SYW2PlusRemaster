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
	DWORD patchAddress = 0x41BD8F;

	if (useMapEditor)
	{
		Patcher.Clear();
		for (int i = 0; i < 6; i++)
			Patcher.Push(IACODE::_90_NOP);
		Patcher.WritePatch(patchAddress);
	}
	else
	{
		BYTE calAddress[sizeof(DWORD)];
		CalculateAddress(6, patchAddress, 0x41BE46, calAddress);

		Patcher.Clear();
		Patcher.Push(2, IACODE::_0F_ESCAPE, IACODE2::_85_JNE_JNZ);
		Patcher.Push(calAddress, 4);
		Patcher.WritePatch(patchAddress);
	}
}

void UsePlayerStart(bool usePlayerStart)
{
	DWORD patchAddress[]
	{
		0x41F1CF, // 조선 건물
		0x41F251, // 일본 건물
		0x41F293, // 조선, 일본 일꾼
		0x41F2E6, // 명 건물
		0x41F328  // 명 일꾼
	};

	if (usePlayerStart)
	{
		BYTE calAddress[sizeof(DWORD)];

		for (int i = 0; i < sizeof(patchAddress) / sizeof(DWORD); i++)
		{
			CalculateAddress(5, patchAddress[i], 0x443190, calAddress);

			Patcher.Clear();
			Patcher.Push(IACODE::_E8_CALL);
			Patcher.Push(calAddress, 4);
			Patcher.WritePatch(patchAddress);
		}
	}
	else
	{
		Patcher.Clear();

		for (int i = 0; i < 5; i++)
			Patcher.Push(IACODE::_90_NOP);

		for (int i = 0; i < sizeof(patchAddress) / sizeof(DWORD); i++)
			Patcher.WritePatch(patchAddress[i]);
	}
}

vector<BYTE> UseMapUnitLoadCodes;
void UseMapUnitLoad(bool useMapUnitLoad)
{
	DWORD patchAddress = 0x41F356;
	UseMapUnitLoadCodes.clear();

	if (useMapUnitLoad)
	{
		// 유닛 생성 코드 복사
		DWORD start = 0x4C3EF9, until = 0x4C3F73;

		UseMapUnitLoadCodes.resize(until - start, IACODE::_90_NOP);
		CopyCode(start, until, &UseMapUnitLoadCodes[0]);
		UseMapUnitLoadCodes.push_back(IACODE::_C3_RETN);

		// Call 주소 재조정
		CalculateAddress(5, (DWORD)&UseMapUnitLoadCodes[0x4C3F3F - start], 0x443190, &UseMapUnitLoadCodes[0x4C3F3F - start + 1], 4);
		CalculateAddress(5, (DWORD)&UseMapUnitLoadCodes[0x4C3F4F - start], 0x40F840, &UseMapUnitLoadCodes[0x4C3F4F - start + 1], 4);
		CalculateAddress(5, (DWORD)&UseMapUnitLoadCodes[0x4C3F63 - start], 0x40F860, &UseMapUnitLoadCodes[0x4C3F63 - start + 1], 4);

		// 패치
		BYTE calAddress[sizeof(DWORD)];
		CalculateAddress(5, patchAddress, (DWORD)&UseMapUnitLoadCodes[0], calAddress);

		Patcher.Clear();
		Patcher.Push(IACODE::_E9_JMP_NEAR);
		Patcher.Push(calAddress, 4);
		Patcher.WritePatch(patchAddress);
	}
	else
	{
		Patcher.Clear();
		Patcher.Push(5, IACODE::_C3_RETN, IACODE::_90_NOP, IACODE::_90_NOP, IACODE::_90_NOP, IACODE::_90_NOP);
		Patcher.WritePatch(patchAddress);
	}
}
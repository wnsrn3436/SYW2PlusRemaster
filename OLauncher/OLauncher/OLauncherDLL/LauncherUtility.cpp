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
		Patcher.Clear();
		Patcher.Push(2, IACODE::_0F_ESCAPE, IACODE2::_85_JNE_JNZ);
		Patcher.PushCalculate(6, patchAddress, 0x41BE46);
		Patcher.WritePatch(patchAddress);
	}
}

void UsePlayerStart(bool usePlayerStart)
{
	// 조선건물, 일본건물, 조선/일본일꾼, 명건물, 명일꾼
	DWORD patchAddress[]{ 0x41F1CF, 0x41F251, 0x41F293, 0x41F2E6, 0x41F328 };
	SIZE_T arraySize = _countof(patchAddress);

	if (usePlayerStart)
	{
		for (SIZE_T i = 0; i < arraySize; i++)
		{
			Patcher.Clear();
			Patcher.Push(IACODE::_E8_CALL);
			Patcher.PushCalculate(5, patchAddress[i], 0x443190);
			Patcher.WritePatch(patchAddress[i]);
		}
	}
	else
	{
		Patcher.Clear();

		for (int i = 0; i < 5; i++)
			Patcher.Push(IACODE::_90_NOP);

		for (SIZE_T i = 0; i < arraySize; i++)
			Patcher.WritePatch(patchAddress[i]);
	}
}

CodePatcher UseMapUnitLoadCodes;
void UseMapUnitLoad(bool useMapUnitLoad)
{
	DWORD patchAddress = 0x41F356;
	UseMapUnitLoadCodes.Clear();

	if (useMapUnitLoad)
	{
		// 유닛 생성 코드 복사
		DWORD start = 0x4C3EF9, until = 0x4C3F73;
		UseMapUnitLoadCodes.PushCodes(start, until);
		UseMapUnitLoadCodes.Push(IACODE::_C3_RETN);

		// Call 주소 재조정
		UseMapUnitLoadCodes.AdjustAddress(5, 0x4C3F3F - start, 0x443190);
		UseMapUnitLoadCodes.AdjustAddress(5, 0x4C3F4F - start, 0x40F840);
		UseMapUnitLoadCodes.AdjustAddress(5, 0x4C3F63 - start, 0x40F860);

		// 패치
		Patcher.Clear();
		Patcher.Push(IACODE::_E9_JMP_NEAR);
		Patcher.PushCalculate(5, patchAddress, UseMapUnitLoadCodes.GetAddress(0));
		Patcher.WritePatch(patchAddress);
	}
	else
	{
		Patcher.Clear();
		Patcher.Push(5, IACODE::_C3_RETN, IACODE::_90_NOP, IACODE::_90_NOP, IACODE::_90_NOP, IACODE::_90_NOP);
		Patcher.WritePatch(patchAddress);
	}
}

void UseLimitedMapSelect(bool useLimitedMapSelect)
{
	Patcher.Clear();
	Patcher.Push(useLimitedMapSelect ? IACODE::_7D_JNL_JGE : IACODE::_EB_JMP_SHORT);
	Patcher.WritePatch(0x4CB9FD);
}

void SetButtonSystem(BYTE system)
{
	Patcher.Clear();
	Patcher.Push(system);
	Patcher.WritePatch(0x669590);
}

void SetGameSpeed(BYTE speed)
{
	// 멀티에서 속도 적용
	Patcher.Clear();
	Patcher.Push(2, IACODE::_90_NOP, IACODE::_90_NOP);
	Patcher.WritePatch(0x4165DB);
	Patcher.WritePatch(0x4165E3);

	// 속도 패치
	Patcher.Clear();
	Patcher.Push(speed);
	Patcher.WritePatch(0x6695A4);
}
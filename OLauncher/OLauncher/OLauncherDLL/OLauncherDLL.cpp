#include "stdafx.h"

DWORD WINAPI Awake(LPVOID lParam)
{
	BYTE codes[CODE_MAX];

	// 정품 인증
	codes[0] = 0x01;
	WriteBytes((LPVOID)0x4ED81C, codes, 1);

	// 씬 이동
	codes[0] = 0x04;
	WriteBytes((LPVOID)0x4ED818, codes, 1);

	return 0;
}

void WriteBytes(LPVOID address, BYTE codes[], SIZE_T size)
{
	DWORD dwOldProtect;

	VirtualProtect(address, size, PAGE_EXECUTE_READWRITE, &dwOldProtect);
	memcpy(address, codes, size);
	VirtualProtect(address, size, dwOldProtect, &dwOldProtect);
}
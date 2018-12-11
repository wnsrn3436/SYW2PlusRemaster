#include "StdAfx.h"

CodePatcher::CodePatcher()
{
	Codes = new vector<BYTE>();
}

CodePatcher::~CodePatcher()
{
	delete Codes;
}

void CodePatcher::Clear()
{
	Codes->clear();
}

void CodePatcher::Push(BYTE code)
{
	Codes->push_back(code);
}

void CodePatcher::Push(BYTE codes[], SIZE_T size)
{
	for (int i = 0; i < (int)size; i++)
		Codes->push_back(codes[i]);
}

void CodePatcher::Push(SIZE_T size, BYTE firstCode, ...)
{
	Codes->push_back(firstCode);

	va_list args;
	va_start(args, firstCode);
	for (int i = 1; i < (int)size; i++)
	{
		BYTE code = va_arg(args, BYTE);
		Codes->push_back(code);
	}
	va_end(args);
}

void CodePatcher::WritePatch(int address)
{
	WritePatch((LPVOID)address);
}

void CodePatcher::WritePatch(LPVOID address)
{
	DWORD dwOldProtect;
	int size = sizeof(BYTE) * Codes->size();

	VirtualProtect(address, size, PAGE_EXECUTE_READWRITE, &dwOldProtect);
	memcpy(address, &(*Codes)[0], size);
	VirtualProtect(address, size, dwOldProtect, &dwOldProtect);
}
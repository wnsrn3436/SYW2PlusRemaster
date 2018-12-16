#include "StdAfx.h"

DWORD CodePatcher::Calculate(SIZE_T opSize, DWORD startAddress, DWORD destAddress)
{
	return destAddress - startAddress - opSize;
}

void CodePatcher::Calculate(SIZE_T opSize, DWORD startAddress, DWORD destAddress, BYTE *result)
{
	Calculate(opSize, startAddress, destAddress, result, sizeof(DWORD));
}

void CodePatcher::Calculate(SIZE_T opSize, DWORD startAddress, DWORD destAddress, BYTE *result, SIZE_T size)
{
	DWORD address = Calculate(opSize, startAddress, destAddress);
	memcpy(result, &address, size);
}

void CodePatcher::Copy(DWORD startAddress, DWORD untilAddress, BYTE *dest)
{
	memcpy(dest, (DWORD *)startAddress, untilAddress - startAddress);
}

DWORD CodePatcher::GetValue(DWORD address)
{
	DWORD value;
	memcpy(&value, (DWORD *)address, 4);
	return value;
}

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

DWORD CodePatcher::GetAddress(int codeIndex)
{
	return (DWORD)&(*Codes)[codeIndex];
}

void CodePatcher::Push(BYTE code)
{
	Codes->push_back(code);
}

void CodePatcher::Push(BYTE codes[], SIZE_T size)
{
	for (SIZE_T i = 0; i < size; i++)
		Codes->push_back(codes[i]);
}

void CodePatcher::Push(SIZE_T size, BYTE firstCode, ...)
{
	Codes->push_back(firstCode);

	va_list args;
	va_start(args, firstCode);
	for (SIZE_T i = 1; i < size; i++)
	{
		BYTE code = va_arg(args, BYTE);
		Codes->push_back(code);
	}
	va_end(args);
}

void CodePatcher::PushCalculate(SIZE_T opSize, DWORD destAddress)
{
	PushCalculate(opSize, (DWORD)&(*Codes)[Codes->size() - 1], destAddress);
}

void CodePatcher::PushCalculate(SIZE_T opSize, DWORD startAddress, DWORD destAddress)
{
	int index = Codes->size();
	Codes->resize(Codes->size() + sizeof(DWORD));

	Calculate(opSize, startAddress, destAddress, &(*Codes)[index]);
}

void CodePatcher::PushCodes(DWORD startAddress, DWORD untilAddress)
{
	int index = Codes->size();
	Codes->resize(Codes->size() + (untilAddress - startAddress));

	Copy(startAddress, untilAddress, &(*Codes)[index]);
}

void CodePatcher::AdjustAddress(SIZE_T opSize, int codeIndex, DWORD destAddress)
{
	Calculate(opSize, (DWORD)&(*Codes)[codeIndex], destAddress, &(*Codes)[codeIndex + opSize - sizeof(DWORD)]);
}

void CodePatcher::WritePatch(DWORD address)
{
	WritePatch((LPVOID)address);
}

void CodePatcher::WritePatch(LPVOID address)
{
	DWORD dwOldProtect;
	SIZE_T size = Codes->size();

	VirtualProtect(address, size, PAGE_EXECUTE_READWRITE, &dwOldProtect);
	memcpy(address, &(*Codes)[0], size);
	VirtualProtect(address, size, dwOldProtect, &dwOldProtect);
}
#include "StdAfx.h"

DWORD CalculateAddress(SIZE_T opSize, DWORD startAddress, DWORD destAddress)
{
	return destAddress - startAddress - opSize;
}

void CalculateAddress(SIZE_T opSize, DWORD startAddress, DWORD destAddress, BYTE *result)
{
	CalculateAddress(opSize, startAddress, destAddress, result, sizeof(DWORD));
}

void CalculateAddress(SIZE_T opSize, DWORD startAddress, DWORD destAddress, BYTE *result, SIZE_T size)
{
	DWORD address = CalculateAddress(opSize, startAddress, destAddress);
	memcpy(result, &address, size);
}

void CopyCode(DWORD startAddress, DWORD untilAddress, BYTE *dest)
{
	memcpy(dest, (DWORD *)startAddress, untilAddress - startAddress);
}
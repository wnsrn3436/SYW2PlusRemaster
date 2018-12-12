#include "StdAfx.h"

int CalculateAddress(SIZE_T opSize, int startAddress, int destAddress)
{
	return destAddress - startAddress - opSize;
}

void CalculateAddress(SIZE_T opSize, int startAddress, int destAddress, BYTE *result)
{
	int address = CalculateAddress(opSize, startAddress, destAddress);
	memcpy(result, &address, sizeof(int));
}
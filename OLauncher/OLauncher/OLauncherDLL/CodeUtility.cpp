#include "StdAfx.h"

int CalculateJmp(SIZE_T opSize, int startAddress, int destAddress)
{
	return destAddress - startAddress - opSize - sizeof(int);
}

void CalculateJmp(SIZE_T opSize, int startAddress, int destAddress, BYTE *result)
{
	int jmpAddress = CalculateJmp(opSize, startAddress, destAddress);
	memcpy(result, &jmpAddress, sizeof(int));
}
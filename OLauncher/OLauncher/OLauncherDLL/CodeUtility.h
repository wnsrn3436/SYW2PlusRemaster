#pragma once

DWORD CalculateAddress(SIZE_T opSize, DWORD startAddress, DWORD destAddress);
void CalculateAddress(SIZE_T opSize, DWORD startAddress, DWORD destAddress, BYTE *result);
void CalculateAddress(SIZE_T opSize, DWORD startAddress, DWORD destAddress, BYTE *result, SIZE_T size);
void CopyCode(DWORD startAddress, DWORD untilAddress, BYTE *dest);
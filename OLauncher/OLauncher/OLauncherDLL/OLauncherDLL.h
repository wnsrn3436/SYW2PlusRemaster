#pragma once

#define CODE_MAX 1024

DWORD WINAPI Awake(LPVOID lParam);
void WriteBytes(LPVOID address, BYTE code[], SIZE_T size);
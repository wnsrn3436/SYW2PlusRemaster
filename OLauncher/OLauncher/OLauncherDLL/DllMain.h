#pragma once

DWORD WINAPI ThreadProc(LPVOID lParam);
void GetDllPath(char dest[], SIZE_T size);
void GetDllDirectory(char dest[], SIZE_T size);
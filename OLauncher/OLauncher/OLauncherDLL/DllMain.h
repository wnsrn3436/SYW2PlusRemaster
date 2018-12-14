#pragma once

bool HookIAT(LPCSTR szDllName, PROC pfnOrg, PROC pfnNew);

typedef BOOL(WINAPI *PFMessageBoxA)(HWND hWnd, LPCTSTR lpText, LPCTSTR lpCaption, UINT uType);
BOOL WINAPI OnMessageBoxA(HWND hWnd, LPCTSTR lpText, LPCTSTR lpCaption, UINT uType);

DWORD WINAPI ThreadProc(LPVOID lParam);
void GetDllPath(char dest[], SIZE_T size);
void GetDllDirectory(char dest[], SIZE_T size);
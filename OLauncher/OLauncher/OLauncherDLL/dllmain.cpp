#include "StdAfx.h"

extern "C" __declspec(dllexport) bool WINAPI DllMain(HINSTANCE hInstDll, DWORD fdwReason, LPVOID lpvReserved)
{
	HANDLE hThread;

	switch (fdwReason)
	{
		case DLL_PROCESS_ATTACH:
			hThread = CreateThread(NULL, 0, ThreadProc, NULL, 0, NULL);
			CloseHandle(hThread);
			break;

		case DLL_PROCESS_DETACH:
			break;

		case DLL_THREAD_ATTACH:
			break;

		case DLL_THREAD_DETACH:
			break;
	}

	return true;
}

DWORD WINAPI ThreadProc(LPVOID lParam)
{
	Awake();
	return 0;
}

void GetDllPath(char dest[], SIZE_T size)
{
	HMODULE module = nullptr;
	GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, (LPCSTR)&GetDllPath, &module);
	GetModuleFileName(module, dest, size);
}

void GetDllDirectory(char dest[], SIZE_T size)
{
	GetDllPath(dest, size);
	(*(strrchr(dest, '\\') + 1)) = NULL;
}
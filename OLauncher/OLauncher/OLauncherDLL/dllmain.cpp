#include "stdafx.h"

extern "C" __declspec(dllexport) bool WINAPI DllMain(HINSTANCE hInstDll, DWORD fdwReason, LPVOID lpvReserved)
{
	HANDLE hThread;

	switch (fdwReason)
	{
		case DLL_PROCESS_ATTACH:
			hThread = CreateThread(NULL, 0, Awake, NULL, 0, NULL);
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
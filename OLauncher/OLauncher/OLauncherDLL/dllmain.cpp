#include "StdAfx.h"

bool canAwake = true;
CodePatcher UpdateCodes;

FARPROC orgMessageBoxA;

extern "C" __declspec(dllexport) bool WINAPI DllMain(HINSTANCE hInstDll, DWORD fdwReason, LPVOID lpvReserved)
{
	HANDLE hThread;

	switch (fdwReason)
	{
		case DLL_PROCESS_ATTACH:
			// 후킹
			orgMessageBoxA = GetProcAddress(GetModuleHandle("user32.dll"), "MessageBoxA");
			HookIAT("user32.dll", orgMessageBoxA, (PROC)OnMessageBoxA);

			// OnAwake 호출
			hThread = CreateThread(NULL, 0, OnAwake, NULL, 0, NULL);
			CloseHandle(hThread);
			break;

		case DLL_PROCESS_DETACH:
			// 후킹 해제
			HookIAT("user32.dll", (PROC)OnMessageBoxA, orgMessageBoxA);
			break;

		case DLL_THREAD_ATTACH:
			break;

		case DLL_THREAD_DETACH:
			break;
	}

	return true;
}

bool HookIAT(LPCSTR szDllName, PROC pfnOrg, PROC pfnNew)
{
	HMODULE hMod = GetModuleHandle(NULL);

	PBYTE pAddr = (PBYTE)hMod;
	pAddr += *((DWORD*)&pAddr[0x3C]);

	DWORD dwRVA = *((DWORD*)&pAddr[0x80]);
	PIMAGE_IMPORT_DESCRIPTOR pImportDesc = (PIMAGE_IMPORT_DESCRIPTOR)((DWORD)hMod + dwRVA);

	for (; pImportDesc->Name; pImportDesc++)
	{
		LPCSTR szLibName = (LPCSTR)((DWORD)hMod + pImportDesc->Name);

		if (!_stricmp(szLibName, szDllName))
		{
			PIMAGE_THUNK_DATA pThunk = (PIMAGE_THUNK_DATA)((DWORD)hMod + pImportDesc->FirstThunk);

			for (; pThunk->u1.Function; pThunk++)
			{
				if (pThunk->u1.Function == (DWORD)pfnOrg)
				{
					DWORD dwOldProtect;

					VirtualProtect((LPVOID)&pThunk->u1.Function, 4, PAGE_EXECUTE_READWRITE, &dwOldProtect);
					pThunk->u1.Function = (DWORD)pfnNew;
					VirtualProtect((LPVOID)&pThunk->u1.Function, 4, dwOldProtect, &dwOldProtect);

					return true;
				}
			}
		}
	}

	return false;
}

BOOL WINAPI OnMessageBoxA(HWND hWnd, LPCTSTR lpText, LPCTSTR lpCaption, UINT uType)
{
	if (canAwake)
	{
		canAwake = false;

		// OnBeginUpdate 패치
		CodePatcher patcher;
		patcher.Push(IACODE::_E8_CALL);
		patcher.PushCalculate(5, 0x4232C8, (DWORD)&OnBeginUpdate);
		patcher.WritePatch(0x4232C8);

		// UpdateCodes로 점프 패치
		UpdateCodes.Codes->reserve(UPDATE_CODE_SIZE);
		patcher.Clear();
		patcher.Push(IACODE::_E9_JMP_NEAR);
		patcher.PushCalculate(5, 0x4232CD, UpdateCodes.GetAddress(0));
		patcher.WritePatch(0x4232CD);

		// OnStart 호출
		UseMessageBox(false);
		OnStart();

		return false;
	}
	else
		return ((PFMessageBoxA)orgMessageBoxA)(hWnd, lpText, lpCaption, uType);
}

DWORD WINAPI OnAwake(LPVOID lParam)
{
	HasPermission(true);
	LoadScene(SCENE::UNKNOWN_11);
	return 0;
}

void OnBeginUpdate()
{
	UpdateCodes.Clear();
	OnUpdate();

	// 기존 코드 복원
	UpdateCodes.Push(6, IACODE::_6A_PUSH, 0x00, IACODE::_6A_PUSH, 0x00, IACODE::_6A_PUSH, 0x00);
	UpdateCodes.Push(4, 0x8D, 0x4C, 0x24, 0x1C);
	UpdateCodes.Push(IACODE::_E9_JMP_NEAR);
	UpdateCodes.PushCalculate(5, 0x4232D2);
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
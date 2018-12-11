#pragma once

DWORD WINAPI ThreadProc(LPVOID iParam);
void Awake();
void SetMessageBoxState(bool useMessageBox);
void SetPermission(bool hasPermission);
void LoadScene(SCENE scene);
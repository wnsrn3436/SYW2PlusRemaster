#pragma once

class CodePatcher
{
public:
	static DWORD Calculate(SIZE_T opSize, DWORD startAddress, DWORD destAddress);
	static void Calculate(SIZE_T opSize, DWORD startAddress, DWORD destAddress, BYTE *result);
	static void Calculate(SIZE_T opSize, DWORD startAddress, DWORD destAddress, BYTE *result, SIZE_T size);
	static void Copy(DWORD startAddress, DWORD untilAddress, BYTE *dest);
	static DWORD GetValue(DWORD address);

public:
	vector<BYTE> *Codes;

	CodePatcher();
	~CodePatcher();

	void Clear();
	DWORD GetAddress(int codeIndex);
	void Push(BYTE code);
	void Push(BYTE codes[], SIZE_T size);
	void Push(SIZE_T size, BYTE firstCode, ...);
	void PushCalculate(SIZE_T opSize, DWORD destAddress);
	void PushCalculate(SIZE_T opSize, DWORD startAddress, DWORD destAddress);
	void PushCodes(DWORD startAddress, DWORD untilAddress);
	void AdjustAddress(SIZE_T opSize, int codeIndex, DWORD destAddress);
	void WritePatch(DWORD address);
	void WritePatch(LPVOID address);
};
#pragma once

class CodePatcher
{
public:
	CodePatcher();
	~CodePatcher();

	void Clear();
	void Push(BYTE code);
	void Push(BYTE codes[], SIZE_T size);
	void Push(vector<BYTE> *codes);
	void Push(SIZE_T size, BYTE firstCode, ...);
	void WritePatch(DWORD address);
	void WritePatch(LPVOID address);

private:
	vector<BYTE> *Codes;
};
#pragma once

using namespace std;

class CodePatcher
{
public:
	CodePatcher();
	~CodePatcher();

	void Clear();
	void Push(BYTE code);
	void Push(BYTE codes[], SIZE_T size);
	void Push(SIZE_T size, BYTE firstCode, ...);
	void WritePatch(int address);
	void WritePatch(LPVOID address);

private:
	vector<BYTE> *Codes;
};
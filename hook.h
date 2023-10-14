#ifndef HOOK_H
#define HOOK_H

#include "Base.h"

class Int3Hook
{
public:
	void Initialize(void* HookAddr, int Size, PVECTORED_EXCEPTION_HANDLER VehFunc);

	void Hook();

	void HookJmpAddr();

	void UnHook();

	void UnHookJmpAddr();

	void* GetHookAddr();

	BYTE* GetJmpAddr();
private:
	BYTE oHookbyte;//原始字节
	BYTE oJmpbyte;
	void* hVEH;//异常处理函数句柄
	BYTE* HookAddr;//Hook地址
	BYTE* JmpAddr;//下一条指令的地址
};

void HookInitialize();

#endif // !HOOK_H
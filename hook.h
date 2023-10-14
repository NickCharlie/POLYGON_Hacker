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
	BYTE oHookbyte;//ԭʼ�ֽ�
	BYTE oJmpbyte;
	void* hVEH;//�쳣���������
	BYTE* HookAddr;//Hook��ַ
	BYTE* JmpAddr;//��һ��ָ��ĵ�ַ
};

void HookInitialize();

#endif // !HOOK_H
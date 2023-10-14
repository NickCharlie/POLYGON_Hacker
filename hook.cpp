#include "hook.h"
#include "engine.h"
#include "aimbot.h"

Int3Hook Spawn_Int3;

void Int3Hook::Initialize(void* HookAddr, int Size, PVECTORED_EXCEPTION_HANDLER VehFunc)
{
	hVEH = AddVectoredExceptionHandler(1, VehFunc);//增加VEH异常

	this->HookAddr = (BYTE*)HookAddr;
	oHookbyte = *(BYTE*)HookAddr;//读入原始字节
	JmpAddr = (BYTE*)(this->HookAddr + Size);//计算下一条指令的地址
	oJmpbyte = *(BYTE*)JmpAddr;
}

void Int3Hook::Hook()
{
	DWORD Protect;
	VirtualProtect(HookAddr, 1, PAGE_EXECUTE_READWRITE, &Protect);//可读可写
	*HookAddr = 0xCC;//int3异常hook
	VirtualProtect(HookAddr, 1, Protect, &Protect);//还原保护
}

void Int3Hook::HookJmpAddr()
{
	DWORD Protect;
	VirtualProtect((BYTE*)JmpAddr, 1, PAGE_EXECUTE_READWRITE, &Protect);//可读可写
	*(BYTE*)JmpAddr = 0xCC;//int3异常hook
	VirtualProtect((BYTE*)JmpAddr, 1, Protect, &Protect);//还原保护
}

void Int3Hook::UnHook()
{
	DWORD Protect;
	VirtualProtect(HookAddr, 1, PAGE_EXECUTE_READWRITE, &Protect);//可读可写
	*HookAddr = oHookbyte;//还原原始字节
	VirtualProtect(HookAddr, 1, Protect, &Protect);//还原保护

}

void Int3Hook::UnHookJmpAddr()
{
	DWORD Protect;
	VirtualProtect((BYTE*)JmpAddr, 1, PAGE_EXECUTE_READWRITE, &Protect);//可读可写
	*(BYTE*)JmpAddr = oJmpbyte;//还原原始字节
	VirtualProtect((BYTE*)JmpAddr, 1, Protect, &Protect);//还原保护

}

void* Int3Hook::GetHookAddr()
{
	return HookAddr;
}

BYTE* Int3Hook::GetJmpAddr()
{
	return JmpAddr;
}


LONG NTAPI AimbotException(_EXCEPTION_POINTERS* ExceptionInfo) {
	if (ExceptionInfo->ExceptionRecord->ExceptionAddress == Spawn_Int3.GetHookAddr()) {
		Spawn_Int3.UnHook();
		Spawn_Int3.HookJmpAddr();

		Aimbot& Instance = Aimbot::GetInstance();
		Vector3* SpawnLocation = (Vector3*)(ExceptionInfo->ContextRecord->R8);
		Vector3* startVelocity = (Vector3*)(ExceptionInfo->ContextRecord->R9);

		bool IsAim = Instance.CanAim();	
		if (IsAim && Options.OpenAimbot) {
			//获取当前自瞄对象离准星多远
			float Distance = (float)Instance.GetAimDistance();

			if (Options.SilentAimbot && Options.SilentRange >= Distance)
			{
				FRotator AimRota = Instance.GetAimRotation();
				Vector3 AimVector = GetForwardVector(AimRota);
				*startVelocity = AimVector;
			}


			if (Options.bulletTrack)
			{
				*SpawnLocation = Instance.GetAimLocation();
			}
		}


		return -1;
	}
	else if (ExceptionInfo->ExceptionRecord->ExceptionAddress == Spawn_Int3.GetJmpAddr())
	{
		Spawn_Int3.Hook();
		Spawn_Int3.UnHookJmpAddr();
		return -1;
	}

	return 0;
}


void HookInitialize()
{
	Spawn_Int3.Initialize(_Spawn, 2, AimbotException);
	Spawn_Int3.Hook();
}
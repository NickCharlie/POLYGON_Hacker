#include "class.h"
#include "engine.h"

void* UGameInstance::GetPlayerController()
{
	DWORD64 Data = *(DWORD64*)(this + 0x38);
	DWORD64 Player = *(DWORD64*)(Data);

	return *(void**)(Player + 0x30);
}

AActor* UGameInstance::GetPlayer()
{
	DWORD64 Data = *(DWORD64*)(this + 0x38);
	DWORD64 Player = *(DWORD64*)(Data);
	DWORD64 PlayerController = *(DWORD64*)(Player + 0x30);

	return *(AActor**)(PlayerController + 0x2B8);
}


string AActor::GetName()
{
	uint32_t Id = *(uint32_t*)((BYTE*)this + 0x18);
	return ::GetName(Id);
	// return ::GetName(Id);
}

bool AActor::IsVisible(AActor* LocalPlayer, int32_t BoneIndex)
{
	TArray<AActor*> ActorsToIgnore;
	//ActorsToIgnore.Initialize();
	ActorsToIgnore.push(LocalPlayer, this);

	Vector3 End = GetBoneLocation(this->Mesh, BoneIndex);
	bool ret = LineTraceSingle(LocalPlayer->Controller->PlayerCameraManager->Pos, End, ActorsToIgnore);

	ActorsToIgnore.Pop();
	return ret;
}
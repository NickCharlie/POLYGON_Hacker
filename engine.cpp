#include "engine.h"

constexpr int Strick = 2;
uint8_t* GameBase = NULL;
uint8_t** GName = NULL;
UWorld** GWorld = NULL;

void* _Spawn = NULL;

fn_GetBoneMatrix _GetBoneMatrix = NULL;
fn_LineTraceSingle _LineTraceSingle = NULL;
fn_GetForwardVector _GetForwardVector = NULL;
fn_ProjectWorldLocationToScreen _ProjectWorldLocationToScreen = NULL;

float Width = 0;
float Height = 0;

void EngineInit(HWND hWnd)
{
	RECT Rect;
	GetClientRect(hWnd, &Rect);
	Width = (float)(Rect.right / 2.f);
	Height = (float)(Rect.bottom / 2.f);


	GameBase = (uint8_t*)GetModuleHandleA(0);
	GName = (uint8_t**)(GameBase + 0x7E24A80);
	GWorld = (UWorld**)(GameBase + 0x8014D88);

	_Spawn = (GameBase + 0x23E2850);
	_GetBoneMatrix = (fn_GetBoneMatrix)(GameBase + 0x4B1C680);
	_LineTraceSingle = (fn_LineTraceSingle)(GameBase + 0x4D0E4B0);
	_GetForwardVector = (fn_GetForwardVector)(GameBase + 0x1968920);
	_ProjectWorldLocationToScreen = (fn_ProjectWorldLocationToScreen)(GameBase + 0x4F88150);
}

string GetName(uint32_t Id)
{
	uint32_t Block = Id >> 16;
	uint32_t Offset = Id & 65535;

	FNameEntry* Info = (FNameEntry*)(GName[2 + Block] + 2 * Offset);

	return string(Info->AnsiName, Info->Len);
}

UWorld* GetWorld()
{
	return *GWorld;
}

bool WorldToScreen(Vector3 WorldLocation, Vector2& ScreenLocation)
{
	void* PlayerColl = GetWorld()->OwningGameInstance->GetPlayerController();
	return _ProjectWorldLocationToScreen(PlayerColl, WorldLocation, ScreenLocation, false);
}

Vector3 GetBoneLocation(void* Mesh, int32_t BoneIndex)
{
	Vector3 Pos;
	FMatrix Matrix;

	_GetBoneMatrix(Mesh, &Matrix, BoneIndex);

	Pos.X = Matrix._41;
	Pos.Y = Matrix._42;
	Pos.Z = Matrix._43;

	return Pos;
}

Vector3 GetForwardVector(FRotator InRot)
{
	return _GetForwardVector(InRot);
}
bool LineTraceSingle(Vector3 Start, Vector3 End, TArray<AActor*>& ActorsToIgnore)
{
	FHitResult OutHit;
	return _LineTraceSingle(GetWorld(), Start, End, 0, true, ActorsToIgnore, 0, OutHit, true, { 0,0,0,0 }, { 0,0,0,0 }, 0.f);
}

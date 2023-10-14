#ifndef ENGINE_H
#define ENGINE_H

#include "base.h"
#include "struct.h"
#include "class.h"
#include "enum.h"

typedef bool (WINAPI* fn_ProjectWorldLocationToScreen)(void* pthis, Vector3 WorldLocation, Vector2& ScreenLocation, bool bPlayerViewportRelative);

typedef FMatrix* (WINAPI* fn_GetBoneMatrix)(void* mesh, FMatrix* Matrix, int32_t BoneIndex);

typedef bool (WINAPI* fn_LineTraceSingle)(UWorld* WorldContextObject, Vector3 Start, Vector3 End, int TraceChannel,
	bool bTraceComplex, TArray<AActor*>& ActorsToIgnore, int DrawDebugType, FHitResult& OutHit, bool bIgnoreSelf, FLinearColor
	TraceColor, FLinearColor TraceHitColor, float DrawTime);

typedef Vector3 (WINAPI* fn_GetForwardVector)(FRotator InRot);



void EngineInit(HWND hWnd);

string GetName(uint32_t Id);

UWorld* GetWorld();

bool WorldToScreen(Vector3 WorldLocation, Vector2& ScreenLocation);

Vector3 GetBoneLocation(void* Mesh, int32_t BoneIndex);

bool LineTraceSingle(Vector3 Start, Vector3 End, TArray<AActor*>& ActorsToIgnore);

// string GetNameNew(FName* Name, wchar_t* str);

Vector3 GetForwardVector(FRotator InRot);

extern float Width;
extern float Height;
extern void* _Spawn;

extern DWORD64 _GetName;

#endif


#pragma once
#include "base.h"
#include "enum.h"

struct Vector2
{
	double X = 0, Y = 0;
};

struct Vector2f
{
	float X = 0, Y = 0;
};

struct Vector3 : public Vector2
{
	Vector3() {};

	Vector3(double A, double B, double C)
	{
		X = A;
		Y = B;
		Z = C;
	};

	double Z = 0;
};

struct Vector4 : public Vector3
{
	double W = 0;
};

struct FMatrix
{
	double _11, _12, _13, _14;
	double _21, _22, _23, _24;
	double _31, _32, _33, _34;
	double _41, _42, _43, _44;
};

struct FHitResult
{
	char pa_00[0x00E8];
};

struct FRotator
{
	double Pitch = 0;
	double Yaw = 0;
	double Roll = 0;
};

struct FLinearColor
{
	float R, G, B, A;
};

struct BoneIdx
{
	BoneIdx()
	{
		head = BoneFNames::Head;
		neck_01 = BoneFNames::neck_01;
		spine_03 = BoneFNames::spine_03;
		spine_02 = BoneFNames::spine_02;
		spine_01 = BoneFNames::spine_01;
		pelvis = BoneFNames::pelvis;

		hand_l = BoneFNames::hand_l;
		lowerarm_l = BoneFNames::lowerarm_l;
		upperarm_l = BoneFNames::upperarm_l;
		clavicle_l = BoneFNames::clavicle_l;
		clavicle_r = BoneFNames::clavicle_r;
		upperarm_r = BoneFNames::upperarm_r;
		lowerarm_r = BoneFNames::lowerarm_r;
		hand_r = BoneFNames::hand_r;

		ball_l = BoneFNames::ball_l;
		foot_l = BoneFNames::foot_l;
		calf_l = BoneFNames::calf_l;
		thigh_l = BoneFNames::thigh_l;
		thigh_r = BoneFNames::thigh_r;
		calf_r = BoneFNames::calf_r;
		foot_r = BoneFNames::foot_r;
		ball_r = BoneFNames::ball_r;
	}

	int head, neck_01, spine_03, spine_02, spine_01, pelvis;
	int hand_l, lowerarm_l, upperarm_l, clavicle_l, clavicle_r, upperarm_r, lowerarm_r, hand_r;
	int ball_l, foot_l, calf_l, thigh_l, thigh_r, calf_r, foot_r, ball_r;
};

struct BoneName
{
	uint32_t Name;
	int A;
	int B;
};

struct FTransform
{
	Vector4 Rotation;
	Vector4 Translation;
	Vector4 Scale3D;
};

struct FNameEntry
{
	uint16_t bIsWide : 1;
	uint16_t LowercaseProbeHash : 5;
	uint16_t Len : 10;

	union
	{
		char AnsiName[1024];
		wchar_t	WideName[1024];
	};
};

struct FName
{
	struct
	{
		int Index;
		int Number;
	};
};
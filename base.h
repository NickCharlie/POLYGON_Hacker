#pragma once

#include <Windows.h>
#include <iostream>
using namespace std;

struct _Options
{
	bool OpenMenu = true;

	bool NoDiff = false;
	bool MaxAmmo = false;
	bool NoRecoil = false;
	bool FullAuto = false;
	bool MaxStamina = false;
	bool MuzzleVelocityMultiplier = false;
	float Mobility = 1.3f;

	bool DrawBone = false;
	bool DrawRange = false;
	bool DrawRadar = false;
	bool DrawBlood = false;
	bool DrawBox2D = false;
	bool DrawBox3D = false;
	bool DrawLosLine = false;
	bool DrawSnapLine = false;

	bool OpenAimbot = false;
	bool bulletTrack = false;
	bool SilentAimbot = false;
	bool MemoryAimbot = false;

	float SilentRange = 30.f;
};


extern _Options Options;
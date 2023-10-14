#include "aimbot.h"


void Aimbot::Push(AActor* Player, AActor* Actor)
{
	Vector2 Screen;
	Vector3 ActorPos = GetBoneLocation(Actor->Mesh, BoneFNames::Head);
	WorldToScreen(ActorPos, Screen);

	double Distance = sqrt(pow(Screen.X - (double)Width, 2) + pow(Screen.Y - (double)Height, 2));

	if (TempPreviousDistance > Distance)
	{
		TempEnemy = Actor;
		TempLocalPlayer = Player;
		TempPreviousDistance = Distance;
	}

	return;
}

void Aimbot::Clear()
{
	Enemy = TempEnemy;
	LocalPlayer = TempLocalPlayer;
	PreviousDistance = TempPreviousDistance;

	TempEnemy = NULL;
	TempLocalPlayer = NULL;
	TempPreviousDistance = 100000.f;

}

double Aimbot::GetAimDistance()
{
	return PreviousDistance;
}

Vector3 Aimbot::GetAimLocation()
{
	return GetBoneLocation(Enemy->Mesh, BoneFNames::Head);
}

void Aimbot::MemoryAimbot()
{
	if (CanAim())
	{
		FRotator AimRota = Aimbot::GetInstance().GetAimRotation();

		// 获取当前自瞄对象离准星多远
		float Distance = (float)Aimbot::GetInstance().GetAimDistance();
		if (Options.SilentRange >= Distance) {
			LocalPlayer->ControllerYawRotation = (float)AimRota.Yaw;
			LocalPlayer->ControllerPitchRotation = (float)AimRota.Pitch;
		}
	}
}

FRotator Aimbot::GetAimRotation()
{
	Vector3 EnemyPos = GetBoneLocation(Enemy->Mesh, BoneFNames::Head);
	Vector3 CameraPos = LocalPlayer->Controller->PlayerCameraManager->Pos;

	Vector3 diff{ EnemyPos.X - CameraPos.X,
			  EnemyPos.Y - CameraPos.Y,
			  EnemyPos.Z - CameraPos.Z,
	};

	FRotator AimRotation{ 0 };
	AimRotation.Yaw = atan2(diff.Y, diff.X) * 180 / 3.1415926;
	AimRotation.Pitch = atan2(diff.Z, sqrt(diff.X * diff.X + diff.Y * diff.Y)) * 180 / 3.1415926;

	return AimRotation;
}

bool Aimbot::CanAim()
{
	if (!Enemy || !LocalPlayer)
		return false;

	return true;
}

bool Aimbot::IsVisible()
{
	return CanAim() ? !Enemy->IsVisible(LocalPlayer, BoneFNames::Head) : false;
}
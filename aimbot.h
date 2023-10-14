#ifndef AIMBOT_H
#define AIMBOT_H


#include "base.h"
#include "engine.h"

class Aimbot
{
public:

	static Aimbot& GetInstance(){
		static Aimbot Instance;
		return Instance;
	}

	void Push(AActor* Player,AActor* Actor);

	void Clear();

	bool CanAim();

	bool IsVisible();

	void MemoryAimbot();

	double GetAimDistance();

	FRotator GetAimRotation();

	Vector3 GetAimLocation();
private:
	Aimbot() {};
	Aimbot(Aimbot&) {};

	AActor* TempEnemy = NULL;
	AActor* TempLocalPlayer = NULL;
	double TempPreviousDistance = 100000.f;

	AActor* Enemy = NULL;
	AActor* LocalPlayer = NULL;
	double PreviousDistance = 100000.f;
};

#endif // !AIMBOT_H

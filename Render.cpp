#include "Render.h"

Render::Render(AActor* LocalPlayer, AActor* Actor)
{
	this->Actor = Actor;
	this->LocalPlayer = LocalPlayer;

	for (int32_t i = 0; i < BoneFNames::Max; i++)
	{
		Vector2 Screen{ 0 };
		BonePos[i] = GetBoneLocation(Actor->Mesh, i);
		BoneIs[i] = WorldToScreen(BonePos[i], Screen);

		BonePoint[i].X = (float)(Screen.X);
		BonePoint[i].Y = (float)(Screen.Y);
	}
}

void Render::DrawBone(ImColor Color)
{
	DrawPartBone(0, 6, Color);
	DrawPartBone(6, 8, Color);
	DrawPartBone(14, 8, Color);
}

void Render::DrawPartBone(int32_t start, int32_t end, ImColor Color)
{
	BoneIdx Id;
	int32_t* Bone = (int32_t*)&Id;
	// Vector2f Point, oPoint;
	Vector2f Point, oPoint;

	for (int32_t i = start; i < start + end; i++)
	{

		Point = BonePoint[Bone[i]];

		if (i != start)
		{
			ImGui::GetForegroundDrawList()->AddLine({ (float)oPoint.X, (float)oPoint.Y }, { (float)Point.X, (float)Point.Y }, Color);
		}

		oPoint = Point;
	}
}

void Render::DrawBox2D(ImColor Color)
{
	int LeftIndex = FindLeftPoint();
	int RightIndex = FindRightPoint();
	int LowestIndex = FindLowestPoint();
	int HighesIndex = FindHighestPoint();
	Vector3 head = GetBoneLocation(Actor->Mesh, BoneFNames::Head);
	Vector2 headpoint{};
	head.Z += 30;
	if (WorldToScreen(head, headpoint) && BoneIs[LeftIndex] && BoneIs[RightIndex]
		&& BoneIs[LowestIndex] && BoneIs[HighesIndex])
	{
		ImGui::GetForegroundDrawList()->AddRect({ (float)BonePoint[LeftIndex].X,(float)headpoint.Y }, { (float)BonePoint[RightIndex].X,(float)BonePoint[LowestIndex].Y }, Color);
	}
}

void Render::DrawBox3D(ImColor Color)
{
	Vector3 Pos = BonePos[BoneFNames::Root];//取得底部坐标
	double Height = BonePos[BoneFNames::Head].Z;//取得高度

	Vector3 Top_Pos[4], Bottom_Pos[4];
	Vector2 Top_Point[4], Bottom_Point[4];
	Vector2f Top_Pointf[4], Bottom_Pointf[4];

	for (int i = 0; i < 4; i++)
	{
		int offset = 45 + i * 90;

		Bottom_Pos[i].X = Pos.X + cos((Actor->RootComponent->ModelYaw + offset) * 3.1415926 / 180.f) * 55.f;
		Bottom_Pos[i].Y = Pos.Y + sin((Actor->RootComponent->ModelYaw + offset) * 3.1415926 / 180.f) * 55.f;
		Bottom_Pos[i].Z = Pos.Z;

		Top_Pos[i] = Bottom_Pos[i];
		Top_Pos[i].Z = Height;

		if (!WorldToScreen(Bottom_Pos[i], Bottom_Point[i])
			|| !WorldToScreen(Top_Pos[i], Top_Point[i]))
		{
			break;
		}

		Top_Pointf[i].X = (float)Top_Point[i].X;
		Top_Pointf[i].Y = (float)Top_Point[i].Y;
		Bottom_Pointf[i].X = (float)Bottom_Point[i].X;
		Bottom_Pointf[i].Y = (float)Bottom_Point[i].Y;

		//画直线高
		ImGui::GetForegroundDrawList()->AddLine({ Bottom_Pointf[i].X,Bottom_Pointf[i].Y }, { Top_Pointf[i].X,Top_Pointf[i].Y }, Color);

		if (i)
		{
			//画上面跟下面的长方形
			ImGui::GetForegroundDrawList()->AddLine({ Bottom_Pointf[i - 1].X,Bottom_Pointf[i - 1].Y }, { Bottom_Pointf[i].X,Bottom_Pointf[i].Y }, Color);
			ImGui::GetForegroundDrawList()->AddLine({ Top_Pointf[i - 1].X,Top_Pointf[i - 1].Y }, { Top_Pointf[i].X,Top_Pointf[i].Y }, Color);

			if (i == 3)
			{
				ImGui::GetForegroundDrawList()->AddLine({ Bottom_Pointf[0].X,Bottom_Pointf[0].Y }, { Bottom_Pointf[i].X,Bottom_Pointf[i].Y }, Color);
				ImGui::GetForegroundDrawList()->AddLine({ Top_Pointf[0].X,Top_Pointf[0].Y }, { Top_Pointf[i].X,Top_Pointf[i].Y }, Color);
			}
		}

	}
}

void Render::DrawRadar(ImColor Color)
{
	Vector3 Pos = BonePos[BoneFNames::Root];
	Vector3 CameraPos = LocalPlayer->Controller->PlayerCameraManager->Pos;

	Pos.X = (Pos.X - CameraPos.X) / 150; // 150 缩放比例
	Pos.Y = (Pos.Y - CameraPos.Y) / 150;
	double R = sqrt(pow(Pos.X, 2) + pow(Pos.Y, 2));

	double Angle = atan2(Pos.Y, Pos.X) * 180 / 3.1415926f;
	Angle = LocalPlayer->ControllerYawRotation - Angle;
	Angle = Angle * 3.1415926f / 180;

	Vector2f Point;
	Point.X = Width + (float)(-(R * sin(Angle)));
	Point.Y = Height + (float)(-(R * cos(Angle)));//求出绘制的点

	ImGui::GetForegroundDrawList()->AddRectFilled({ Point.X - 2,Point.Y - 2 }, { Point.X + 2,Point.Y + 2 }, Color);
	ImGui::GetForegroundDrawList()->AddRect({ Point.X - 3,Point.Y - 3 }, { Point.X + 3,Point.Y + 3 }, ImColor(0, 0, 0));


	ImGui::GetForegroundDrawList()->AddLine({ Width - 70,Height }, { Width + 70,Height }, ImColor(0, 0, 0));
	ImGui::GetForegroundDrawList()->AddLine({ Width,Height - 70 }, { Width,Height + 70 }, ImColor(0, 0, 0));

	ImGui::GetForegroundDrawList()->AddRectFilled({ Width - 2,Height - 2 }, { Width + 2,Height + 2 }, ImColor(255, 255, 255));
	ImGui::GetForegroundDrawList()->AddRect({ Width - 3,Height - 3 }, { Width + 3,Height + 3 }, ImColor(0, 0, 0));//绘制出自己的方块

}

void Render::DrawBlood(ImColor Color)
{
	int LeftIndex = FindLeftPoint();
	int LowestIndex = FindLowestPoint();
	int HighesIndex = FindHighestPoint();

	if (BoneIs[LeftIndex]
		&& BoneIs[LowestIndex]
		&& BoneIs[HighesIndex])
	{
		if (Actor->HealthStatsComponent->Health < 50)
			Color = ImColor(255, 0, 0);

		float FilledW = (float)(Actor->HealthStatsComponent->Health) / 100.f * (BonePoint[HighesIndex].Y - BonePoint[LowestIndex].Y);
		ImGui::GetForegroundDrawList()->AddRect({ BonePoint[LeftIndex].X - 5,BonePoint[LowestIndex].Y }, { BonePoint[LeftIndex].X - 2,BonePoint[HighesIndex].Y }, ImColor(0, 0, 0));
		ImGui::GetForegroundDrawList()->AddRectFilled({ BonePoint[LeftIndex].X - 4,BonePoint[LowestIndex].Y }, { BonePoint[LeftIndex].X - 3,BonePoint[LowestIndex].Y + FilledW }, Color);
	}
}

void Render::DrawLosLine(ImColor Color)
{
	Vector2 StartPoint, EndPoint;
	Vector3 StartPos, EndPos;

	StartPos = BonePos[BoneFNames::Head];

	EndPos.X = StartPos.X + cos(Actor->RootComponent->ModelYaw * 3.1415926f / 180.f) * 700;
	EndPos.Y = StartPos.Y + sin(Actor->RootComponent->ModelYaw * 3.1415926f / 180.f) * 700;
	EndPos.Z = StartPos.Z + sin(0 * 3.1415926f / 180.f) * 700;

	if (WorldToScreen(StartPos, StartPoint) && WorldToScreen(EndPos, EndPoint))
	{
		ImGui::GetForegroundDrawList()->AddCircleFilled({ (float)StartPoint.X,(float)StartPoint.Y }, 2, Color);
		ImGui::GetForegroundDrawList()->AddLine({ (float)StartPoint.X,(float)StartPoint.Y }, { (float)EndPoint.X,(float)EndPoint.Y }, Color);
	}

}

void Render::DrawSnapLine(ImColor Color)
{
	if (BoneIs[BoneFNames::Root])
	{
		ImGui::GetForegroundDrawList()->AddLine({ Width, Height * 2 }, { BonePoint[BoneFNames::Root].X,BonePoint[BoneFNames::Root].Y}, Color);
	}
}

int Render::FindLeftPoint()
{
	int ret = 0;

	for (int i = 0; i < BoneFNames::Max; i++)
	{
		if (BonePoint[i].X < BonePoint[ret].X)
			ret = i;
	}

	return ret;
}

int Render::FindRightPoint()
{
	int ret = 0;

	for (int i = 0; i < BoneFNames::Max; i++)
	{
		if (BonePoint[i].X > BonePoint[ret].X)
			ret = i;
	}

	return ret;
}

int Render::FindHighestPoint()
{
	int ret = 0;

	for (int i = 0; i < BoneFNames::Max; i++)
	{
		if (BonePoint[i].Y < BonePoint[ret].Y)
			ret = i;
	}

	return ret;
}

int Render::FindLowestPoint()
{
	int ret = 0;

	for (int i = 0; i < BoneFNames::Max; i++)
	{
		if (BonePoint[i].Y > BonePoint[ret].Y)
			ret = i;
	}

	return ret;
}
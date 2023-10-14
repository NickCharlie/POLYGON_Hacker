#include "menu.h"

_Options Options;

void Player()
{
    if (ImGui::BeginTabItem("Player"))
    {
        ImGui::Checkbox(u8"武器::无扩散", &Options.NoDiff);
        ImGui::Checkbox(u8"武器::无后座", &Options.NoRecoil);
        ImGui::Checkbox(u8"武器::全自动", &Options.FullAuto);
        ImGui::Checkbox(u8"武器::无限子弹", &Options.MaxAmmo);
        ImGui::Checkbox(u8"人物::无限耐力", &Options.MaxStamina);
        ImGui::Checkbox(u8"子弹::子弹瞬击", &Options.MuzzleVelocityMultiplier);
        ImGui::SliderFloat(u8"人物::人物速度", &Options.Mobility, 0.f, 10.f);

        ImGui::EndTabItem();
    }
}

void Esp()
{
    if (ImGui::BeginTabItem("ESP"))
    {

        ImGui::Checkbox(u8"2D 雷达", &Options.DrawRadar);
        ImGui::Checkbox(u8"2D 方框", &Options.DrawBox2D);
        ImGui::Checkbox(u8"3D 方框", &Options.DrawBox3D);
        ImGui::Checkbox(u8"自瞄范围", &Options.DrawRange);
        ImGui::Checkbox(u8"人物骨骼", &Options.DrawBone);
        ImGui::Checkbox(u8"人物血条", &Options.DrawBlood);
        ImGui::Checkbox(u8"人物朝向", &Options.DrawLosLine);
        ImGui::Checkbox(u8"人物连线", &Options.DrawSnapLine);

        ImGui::EndTabItem();
    }
}

void Aimbot()
{
    if (ImGui::BeginTabItem("Aimbot"))
    {

        ImGui::Checkbox(u8"开启自瞄", &Options.OpenAimbot);
        ImGui::Checkbox(u8"内存自瞄", &Options.MemoryAimbot);
        ImGui::Checkbox(u8"静默自瞄", &Options.SilentAimbot);
        ImGui::Checkbox(u8"子弹追踪", &Options.bulletTrack);
        ImGui::SliderFloat(u8"静默范围", &Options.SilentRange, 0.f, 960.f);

        ImGui::EndTabItem();
    }
}
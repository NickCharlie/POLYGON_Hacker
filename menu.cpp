#include "menu.h"

_Options Options;

void Player()
{
    if (ImGui::BeginTabItem("Player"))
    {
        ImGui::Checkbox(u8"����::����ɢ", &Options.NoDiff);
        ImGui::Checkbox(u8"����::�޺���", &Options.NoRecoil);
        ImGui::Checkbox(u8"����::ȫ�Զ�", &Options.FullAuto);
        ImGui::Checkbox(u8"����::�����ӵ�", &Options.MaxAmmo);
        ImGui::Checkbox(u8"����::��������", &Options.MaxStamina);
        ImGui::Checkbox(u8"�ӵ�::�ӵ�˲��", &Options.MuzzleVelocityMultiplier);
        ImGui::SliderFloat(u8"����::�����ٶ�", &Options.Mobility, 0.f, 10.f);

        ImGui::EndTabItem();
    }
}

void Esp()
{
    if (ImGui::BeginTabItem("ESP"))
    {

        ImGui::Checkbox(u8"2D �״�", &Options.DrawRadar);
        ImGui::Checkbox(u8"2D ����", &Options.DrawBox2D);
        ImGui::Checkbox(u8"3D ����", &Options.DrawBox3D);
        ImGui::Checkbox(u8"���鷶Χ", &Options.DrawRange);
        ImGui::Checkbox(u8"�������", &Options.DrawBone);
        ImGui::Checkbox(u8"����Ѫ��", &Options.DrawBlood);
        ImGui::Checkbox(u8"���ﳯ��", &Options.DrawLosLine);
        ImGui::Checkbox(u8"��������", &Options.DrawSnapLine);

        ImGui::EndTabItem();
    }
}

void Aimbot()
{
    if (ImGui::BeginTabItem("Aimbot"))
    {

        ImGui::Checkbox(u8"��������", &Options.OpenAimbot);
        ImGui::Checkbox(u8"�ڴ�����", &Options.MemoryAimbot);
        ImGui::Checkbox(u8"��Ĭ����", &Options.SilentAimbot);
        ImGui::Checkbox(u8"�ӵ�׷��", &Options.bulletTrack);
        ImGui::SliderFloat(u8"��Ĭ��Χ", &Options.SilentRange, 0.f, 960.f);

        ImGui::EndTabItem();
    }
}
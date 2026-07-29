#include "Gang.h"

Gang::Gang()
{
    name = "강사라";
    Hp = 180;
    MaxHp = 180;
    Mp = 200;
    MaxMp = 200;
    Attack = 35;
    Defense = 15;
    Str = 10;
    Dex = 25;
    Intel = 10;
    Luk = 15;
}

// 1. 근접 데미지 (힘과 민첩 영향)
int Gang::GetMeleeDamage(const StatBonus& bonus)
{
    // 보기 좋게 최종 스탯을 먼저 계산해 둡니다.
    int finalStr = Str + bonus.str;
    int finalDex = Dex + bonus.dex;

    // 계산식에 최종 스탯을 대입합니다.
    int Damage = Attack + (finalStr * 0.5) + (finalDex * 0.5);

    return Damage;
}

// 2. 스킬 데미지 (지능과 운 영향)
int Gang::GetSkillDamage(const StatBonus& bonus)
{
    // 마법/스킬 데미지에 영향을 주는 스탯을 합산합니다.
    int finalIntel = Intel + bonus.intel;
    int finalLuk = Luk + bonus.luk;

    // 계산식에 최종 스탯을 대입합니다.
    int Damage = Attack + (finalIntel * 0.8) + (finalLuk * 0.8);

    return Damage;
}
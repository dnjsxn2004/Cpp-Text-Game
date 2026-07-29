#include "Ryu.h"

Ryu::Ryu()
{
    name = "류노스케";
    Hp = 150;
    MaxHp = 150;
    Mp = 300;
    MaxMp = 300;
    Attack = 50;
    Defense = 10;
    Str = 5;
    Dex = 5;
    Intel = 30;
    Luk = 10;
}

// 1. 근접 데미지 (힘과 민첩 영향)
int Ryu::GetMeleeDamage(const StatBonus& bonus)
{
    // 보기 좋게 최종 스탯을 먼저 계산해 둡니다.
    int finalStr = Str + bonus.str;
    int finalDex = Dex + bonus.dex;

    // 계산식에 최종 스탯을 대입합니다.
    int Damage = Attack + (finalStr * 0.5) + (finalDex * 0.5);

    return Damage;
}

// 2. 스킬 데미지 (지능과 운 영향)
int Ryu::GetSkillDamage(const StatBonus& bonus)
{
    // 마법/스킬 데미지에 영향을 주는 스탯을 합산합니다.
    int finalIntel = Intel + bonus.intel;
    int finalLuk = Luk + bonus.luk;

    // 계산식에 최종 스탯을 대입합니다.
    int Damage = Attack + (finalIntel * 0.8) + (finalLuk * 0.8);

    return Damage;
}
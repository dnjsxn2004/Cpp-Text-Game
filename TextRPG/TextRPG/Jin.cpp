#include "Jin.h"

Jin::Jin()
{
    name = "진태식";
    Hp = 300;
    MaxHp = 300;
    Mp = 100;
    MaxMp = 100;
    Attack = 45;
    Defense = 25;
    Str = 20;
    Dex = 10;
    Intel = 5;
    Luk = 5;
    // 나머지 변수(Level, Gold 등)는 부모의 기본값(1, 0)을 그대로 따름
}

// 1. 근접 데미지 (힘과 민첩 영향)
int Jin::GetMeleeDamage(const StatBonus& bonus)
{
    // 보기 좋게 최종 스탯을 먼저 계산해 둡니다.
    int finalStr = Str + bonus.str;
    int finalDex = Dex + bonus.dex;

    // 계산식에 최종 스탯을 대입합니다.
    int Damage = Attack + (finalStr * 0.5) + (finalDex * 0.5);

    return Damage;
}

// 2. 스킬 데미지 (지능과 운 영향)
int Jin::GetSkillDamage(const StatBonus& bonus)
{
    // 마법/스킬 데미지에 영향을 주는 스탯을 합산합니다.
    int finalIntel = Intel + bonus.intel;
    int finalLuk = Luk + bonus.luk;

    // 계산식에 최종 스탯을 대입합니다.
    int Damage = Attack + (finalIntel * 0.8) + (finalLuk * 0.8);

    return Damage;
}
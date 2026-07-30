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

// 1. 평타 데미지 계산
int Jin::GetMeleeDamage(const StatBonus& equipBonus, const StatBonus& potionBonus)
{
    //장비 보너스와 포션 보너스를 하나로 통합
    StatBonus totalBonus = equipBonus + potionBonus;

    //통합된 보너스를 내 기본 스탯과 합산
    int finalStr = Str + totalBonus.str;
    int finalDex = Dex + totalBonus.dex;
    int finalAtt = Attack + totalBonus.att;
    //최종 스탯을 공식에 대입
    int Damage = finalAtt + (finalStr * 0.5) + (finalDex * 0.5);

    return Damage;
}

// 2. 스킬 데미지 계산
int Jin::GetSkillDamage(const StatBonus& equipBonus, const StatBonus& potionBonus)
{
    //보너스 통합
    StatBonus totalBonus = equipBonus + potionBonus;

    //통합된 보너스를 내 기본 스탯과 합산
    int finalIntel = Intel + totalBonus.intel;
    int finalLuk = Luk + totalBonus.luk;
    int finalAtt = finalAtt + totalBonus.att;
    //최종 스탯을 공식에 대입
    int Damage = finalAtt + (finalIntel * 0.8) + (finalLuk * 0.8);

    return Damage;
}

int Jin::GetTrueDefense(const StatBonus& equipBonus, const StatBonus& potionBonus)
{
    //장비 보너스와 포션 보너스를 하나로 통합
    StatBonus totalBonus = equipBonus + potionBonus;

    //통합된 보너스를 내 기본 스탯과 합산
    int finalStr = Str + totalBonus.str;
    int finalDex = Dex + totalBonus.dex;
    int finalDef = Defense + totalBonus.def;
    //최종 스탯을 공식에 대입
    int FinalDefense = finalDef + (finalStr * 0.5) + (finalDex * 0.5);

    return FinalDefense;
}
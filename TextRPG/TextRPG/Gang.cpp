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

// 1. 평타 데미지 계산
int Gang::GetMeleeDamage(const StatBonus& equipBonus, const StatBonus& potionBonus)
{
    //장비 보너스와 포션 보너스를 하나로 통합
    StatBonus totalBonus = equipBonus + potionBonus;

    //통합된 보너스를 내 기본 스탯과 합산
    int FinalStr = Str + totalBonus.str;
    int FinalDex = Dex + totalBonus.dex;
    int finalAtt = Attack + totalBonus.att;
    //최종 스탯을 공식에 대입
    int Damage = finalAtt + (FinalStr * 0.5) + (FinalDex * 0.5);

    return Damage;
}

// 2. 스킬 데미지 계산
int Gang::GetSkillDamage(const StatBonus& equipBonus, const StatBonus& potionBonus)
{
    //보너스 통합
    StatBonus totalBonus = equipBonus + potionBonus;

    //통합된 보너스를 내 기본 스탯과 합산
    int FinalIntel = Intel + totalBonus.intel;
    int FinalLuk = Luk + totalBonus.luk;
    int finalAtt = Attack + totalBonus.att;
    //최종 스탯을 공식에 대입
    int Damage = finalAtt + (FinalIntel * 0.8) + (FinalLuk * 0.8);

    return Damage;
}

int Gang::GetTrueDefense(const StatBonus& equipBonus, const StatBonus& potionBonus)
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
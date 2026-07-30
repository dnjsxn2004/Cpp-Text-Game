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

// 1. 평타 데미지 계산
int Ryu::GetMeleeDamage(const StatBonus& equipBonus, const StatBonus& potionBonus)
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
int Ryu::GetSkillDamage(const StatBonus& equipBonus, const StatBonus& potionBonus)
{
    //보너스 통합
    StatBonus totalBonus = equipBonus + potionBonus;

    //통합된 보너스를 내 기본 스탯과 합산
    int finalIntel = Intel + totalBonus.intel;
    int finalLuk = Luk + totalBonus.luk;
    int finalAtt = Attack + totalBonus.att;
    //최종 스탯을 공식에 대입
    int Damage = finalAtt + (finalIntel * 0.8) + (finalLuk * 0.8);

    return Damage;
}

// 3. 실질 방어력 계산
int Ryu::GetTrueDefense(const StatBonus& equipBonus, const StatBonus& potionBonus)
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
#pragma once
#include "Player.h"

// 1. Jin 클래스
class Jin : public Player
{
public:
    Jin();

    int GetMeleeDamage(const StatBonus& equipBonus, const StatBonus& potionBonus) override;
    int GetSkillDamage(const StatBonus& equipBonus, const StatBonus& potionBonus) override;
};


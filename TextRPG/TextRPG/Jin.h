#pragma once
#include "Player.h"

// 1. Jin 클래스 (예: 전사 타입)
class Jin : public Player
{
public:
    Jin();

    int GetMeleeDamage(const StatBonus& equipBonus, const StatBonus& potionBonus) override;
    int GetSkillDamage(const StatBonus& equipBonus, const StatBonus& potionBonus) override;
};


#pragma once
#include "Player.h"

// 2. Gang 클래스
class Gang : public Player
{
public:
    Gang();

    int GetMeleeDamage(const StatBonus& equipBonus, const StatBonus& potionBonus) override;
    int GetSkillDamage(const StatBonus& equipBonus, const StatBonus& potionBonus) override;
    int GetTrueDefense(const StatBonus& equipBonus, const StatBonus& potionBonus) override;
};

#pragma once
#include "Player.h"

class Ryu : public Player
{
public:
    Ryu();

    int GetMeleeDamage(const StatBonus& equipBonus, const StatBonus& potionBonus) override;
    int GetSkillDamage(const StatBonus& equipBonus, const StatBonus& potionBonus) override;
    int GetTrueDefense(const StatBonus& equipBonus, const StatBonus& potionBonus) override;

    std::string GetDescription() const;
};
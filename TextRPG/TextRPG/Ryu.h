#pragma once
#include "Player.h"

class Ryu : public Player
{
public:
    Ryu();

    int GetMeleeDamage(const StatBonus& bonus) override;
    int GetSkillDamage(const StatBonus& bonus) override;
};
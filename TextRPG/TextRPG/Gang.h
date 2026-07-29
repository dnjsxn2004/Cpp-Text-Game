#pragma once
#include "Player.h"

// 2. Gang 클래스 (예: 도적/궁수 타입)
class Gang : public Player
{
public:
    Gang();

    int GetMeleeDamage(const StatBonus& bonus) override;
    int GetSkillDamage(const StatBonus& bonus) override;
};


#pragma once

#ifndef MONSTER_H
#define MONSTER_H

#include <string>
#include <iostream>

class GameContext;

class Monster
{
private:
    std::string Name;
    int Hp;
    int MaxHp;
    int Attack;
    int Defense;
    int ExpReward;
    int GoldReward;

    std::string SkillName;
    int SkillProbability;
    float SkillMultiplier;

public:
    Monster();

    Monster(
        std::string Name,
        int Hp,
        int Attack,
        int Defense,
        int ExpReward,
        int GoldReward,
        std::string SkillName,
        int SkillProbability,
        float SkillMultiplier
    );

    std::string GetName()           const { return Name; }
    int         GetHp()             const { return Hp; }
    int         GetMaxHp()          const { return MaxHp; }
    int         GetAttack()         const { return Attack; }
    int         GetDefense()        const { return Defense; }
    int         GetExpReward()      const { return ExpReward; }
    int         GetGoldReward()     const { return GoldReward; }
    std::string GetSkillName()      const { return SkillName; }
    int         GetSkillProbability() const { return SkillProbability; }
    float       GetSkillMultiplier()  const { return SkillMultiplier; }

    void SetName(const std::string& name);
    void SetHp(int hp);
    void SetMaxHp(int maxHp);
    void SetAttack(int attack);
    void SetDefense(int defense);
    void SetExpReward(int expReward);
    void SetGoldReward(int goldReward);
    void SetSkillName(const std::string& skillName);
    void SetSkillProbability(int skillProbability);
    void SetSkillMultiplier(float skillMultiplier);

    int  TakeDamage(int damage);
    bool IsDead() const;
    void PrintInfo() const;
    int  CalculateAttackDamage() const;
};

Monster SpawnRandomMonster(GameContext& Context);
Monster SpawnMiddleBoss(GameContext& Context);
Monster SpawnFinalBoss(GameContext& Context);

#endif

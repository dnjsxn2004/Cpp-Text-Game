#pragma once

#ifndef MONSTER_H
#define MONSTER_H

#include <string>
#include <iostream>

using namespace std;

class GameContext;


class Monster
{
private:
    string Name;
    int Hp;
    int MaxHp;
    int Attack;
    int Defense;
    int ExpReward;
    int GoldReward;

    string SkillName;
    int SkillProbability;  // 0 ~ 100 사이의 스킬 발동 확률
    float SkillMultiplier; // 스킬 발동 시 공격력 증폭 배수

public:
   
    Monster();

    Monster(
        string Name,
        int Hp,
        int Attack,
        int Defense,
        int ExpReward,
        int GoldReward,
        string SkillName,
        int SkillProbability,
        float SkillMultiplier
    );

    // Getter 메서드 유지
    string GetName() const { return Name; }
    int GetHp() const { return Hp; }
    int GetMaxHp() const { return MaxHp; }
    int GetAttack() const { return Attack; }
    int GetDefense() const { return Defense; }
    int GetExpReward() const { return ExpReward; }
    int GetGoldReward() const { return GoldReward; }
    // 배틀 함수에서 써서 추가
    string GetSkillName() const { return SkillName; }
    int GetSkillProbability() const { return SkillProbability; }
    float GetSkillMultiplier() const { return SkillMultiplier; }

   
    void SetName(const string& name);
    void SetHp(int hp);
    void SetMaxHp(int maxHp);
    void SetAttack(int attack);
    void SetDefense(int defense);
    void SetExpReward(int expReward);
    void SetGoldReward(int goldReward);
    void SetSkillName(const string& skillName);
    void SetSkillProbability(int skillProbability);
    void SetSkillMultiplier(float skillMultiplier);

    // 전투 관련 메서드 유지
    int TakeDamage(int damage);
    bool IsDead() const;
    void PrintInfo() const;

  
    int CalculateAttackDamage() const;
};


Monster SpawnRandomMonster(GameContext& Context);

// 중간보스 생성 함수 추가
Monster SpawnMiddleBoss(GameContext& Context);

//최종보스 생성 함수 추가
Monster SpawnFinalBoss(GameContext& Context);

#endif

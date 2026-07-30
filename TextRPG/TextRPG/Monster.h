#pragma once
#ifndef MONSTER_H
#define MONSTER_H

#include <string>
#include <iostream>

using namespace std;

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

    // [신규] 스킬 관련 변수 추가
    string SkillName;
    int SkillProbability;  // 0 ~ 100 사이의 스킬 발동 확률
    float SkillMultiplier; // 스킬 발동 시 공격력 증폭 배수


public:
    // 생성자
    Monster(string Name, int Hp, int Attack, int Defense, int ExpReward, int GoldReward, string SkillName, int SkillProbability, float SkillMultiplier);

    // Getter 메서드 (전투 시스템에서 팀원이 가져다 쓸 함수들)
    string GetName() const { return Name; }
    int GetHp() const { return Hp; }
    int GetMaxHp() const { return MaxHp; }
    int GetAttack() const { return Attack; }
    int GetDefense() const { return Defense; }
    int GetExpReward() const { return ExpReward; }
    int GetGoldReward() const { return GoldReward; }

    // 전투 관련 메서드
    int TakeDamage(int damage);
    bool IsDead() const;
    void PrintInfo() const;
    // [신규] 확률적 스킬 발동을 포함한 최종 공격 데미지 계산 함수
    int CalculateAttackDamage() const;
};


// GameContext 클래스 전방 선언
class GameContext;

// 랜덤 조우를 위한 몬스터 생성 도우미 함수 (레벨 스케일링 적용)
Monster SpawnRandomMonster(GameContext& Context);

Monster SpawnFinalBoss(GameContext& Context);

#endif
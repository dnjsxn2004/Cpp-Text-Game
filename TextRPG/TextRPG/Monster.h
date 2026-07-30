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

public:
    // 생성자
    Monster();
    Monster(string Name, int Hp, int Attack, int Defense, int ExpReward, int GoldReward);

    // Getter 메서드 (전투 시스템에서 팀원이 가져다 쓸 함수들)
    string getName() const { return Name; }
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
};


// GameContext 클래스 전방 선언
class GameContext;

// 랜덤 조우를 위한 몬스터 생성 도우미 함수 (레벨 스케일링 적용)
Monster SpawnRandomMonster(int playerLevel);

#endif
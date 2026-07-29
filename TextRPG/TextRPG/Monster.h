#pragma once
#ifndef MONSTER_H
#define MONSTER_H

#include <string>
#include <iostream>

using namespace std;

class Monster
{
private:
    string name;
    int hp;
    int maxHp;
    int attack;
    int defense;
    int expReward;
    int goldReward;

public:
    // 생성자
    Monster(string name, int hp, int attack, int defense, int expReward, int goldReward);

    // Getter 메서드 (전투 시스템에서 팀원이 가져다 쓸 함수들)
    string getName() const { return name; }
    int getHp() const { return hp; }
    int getMaxHp() const { return maxHp; }
    int getAttack() const { return attack; }
    int getDefense() const { return defense; }
    int getExpReward() const { return expReward; }
    int getGoldReward() const { return goldReward; }

    // 전투 관련 메서드
    void takeDamage(int damage);
    bool isDead() const;
    void printInfo() const;
};

// 랜덤 조우를 위한 몬스터 생성 도우미 함수 (레벨 스케일링 적용)
Monster SpawnRandomMonster(int playerLevel);

#endif
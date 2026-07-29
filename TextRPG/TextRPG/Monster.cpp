#include "Monster.h"
#include <cstdlib>
#include <ctime>

// 생성자 초기화
Monster::Monster(string name, int hp, int attack, int defense, int expReward, int goldReward)
    : name(name), hp(hp), maxHp(hp), attack(attack), defense(defense), expReward(expReward), goldReward(goldReward) {}

// 데미지 처리 함수 (방어력 계산 포함)
void Monster::takeDamage(int damage) {
    int actualDamage = damage - defense;
    if (actualDamage < 1) actualDamage = 1; // 최소 데미지 1 보장

    hp -= actualDamage;
    if (hp < 0) hp = 0;

    cout << name << "이(가) " << actualDamage << "의 피해를 입었습니다! (남은 HP: " << hp << "/" << maxHp << ")\n";
}

// 사망 체크
bool Monster::isDead() const {
    return hp <= 0;
}

// 몬스터 정보 출력
void Monster::printInfo() const {
    cout << "[" << name << "] HP: " << hp << " | ATK: " << attack
        << " | DEF: " << defense << " | 보상: " << expReward << "EXP, " << goldReward << "G\n";
}

// =========================================================================
// [기획서 반영] 몬스터 랜덤 생성 및 스케일링 로직
// =========================================================================
int GetRandomNum(int min, int max) {
    return min + rand() % ((max - min) + 1);
}

Monster SpawnRandomMonster(int playerLevel) {
    // 1. 기획서 1번 요구사항: 레벨 비례 랜덤 스탯 베이스 계산
    int baseHp = GetRandomNum(playerLevel * 20, playerLevel * 30);
    int baseAtk = GetRandomNum(playerLevel * 5, playerLevel * 10);

    // (방어력, 경험치, 골드는 기획서에 공식이 없어 임의의 스케일링 적용)
    int baseDef = GetRandomNum(playerLevel * 2, playerLevel * 4);
    int baseExp = GetRandomNum(playerLevel * 10, playerLevel * 15);
    int baseGold = GetRandomNum(playerLevel * 20, playerLevel * 30);

    // 2. 기획서 2번 요구사항: 3종의 일반 몬스터 목록 및 특징 부여
    int monsterType = rand() % 3; // 0, 1, 2 랜덤 조우

    string name;
    int finalHp, finalAtk, finalDef, finalExp, finalGold;

    if (monsterType == 0) {
        // [짭새] 체력이 높고 방어력이 낮음, 골드를 적게 줌
        name = "짭새";
        finalHp = (int)(baseHp * 1.2);   finalAtk = baseAtk;
        finalDef = (int)(baseDef * 0.5); finalExp = baseExp;       finalGold = (int)(baseGold * 0.5);
    }
    else if (monsterType == 1) {
        // [짜바리] 표준적인 스탯, 골드를 많이 줌
        name = "짜바리";
        finalHp = baseHp;                finalAtk = baseAtk;
        finalDef = baseDef;              finalExp = baseExp;       finalGold = (int)(baseGold * 1.5);
    }
    else {
        // [칼잽이] 체력이 낮지만 공격력/방어력이 매우 높음, 경험치를 많이 줌
        name = "칼잽이";
        finalHp = (int)(baseHp * 0.8);   finalAtk = (int)(baseAtk * 1.3);
        finalDef = (int)(baseDef * 1.2); finalExp = (int)(baseExp * 1.5); finalGold = baseGold;
    }

    // 최종 완성된 몬스터 객체 반환
    return Monster(name, finalHp, finalAtk, finalDef, finalExp, finalGold);
}
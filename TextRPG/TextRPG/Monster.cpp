#include "Monster.h"
#include <cstdlib>
#include <ctime>
#include "Player.h"
#include "GameContext.h"

// 생성자 초기화
Monster::Monster(string Name, int Hp, int Attack, int Defense, int ExpReward, int GoldReward)
    : Name(Name), Hp(Hp), MaxHp(Hp), Attack(Attack), Defense(Defense), ExpReward(ExpReward), GoldReward(GoldReward) {}
// 게임 컨텍스트 처리용 기본 생성자 추가
Monster::Monster()
    : Name("default monster"),
    Hp(50),
    MaxHp(50),
    Attack(10),
    Defense(3),
    ExpReward(10),
    GoldReward(10)
{
}

// 데미지 처리 함수 (방어력 계산 포함)
int Monster::TakeDamage(int Damage) {
    int ActualDamage = Damage - Defense;
    if (ActualDamage < 1) ActualDamage = 1; // 최소 데미지 1 보장

 

    return ActualDamage;
}

// 사망 체크
bool Monster::IsDead() const {
    return Hp <= 0;
}

// 몬스터 정보 출력
void Monster::PrintInfo() const {
    cout << "[" << Name << "] HP: " << Hp << " | ATK: " << Attack
        << " | DEF: " << Defense << " | reward: " << ExpReward << "EXP, " << GoldReward << "G\n";
}

// =========================================================================
// [기획서 반영] 몬스터 랜덤 생성 및 스케일링 로직
// =========================================================================
int GetRandomNum(int Min, int Max) {
    return Min + rand() % ((Max - Min) + 1);
}

Monster SpawnRandomMonster(GameContext& context) 
{
    Player& Player = context.GetPlayer();

    // 1. 기획서 1번 요구사항: 레벨 비례 랜덤 스탯 베이스 계산
    int BaseHp = GetRandomNum(Player.GetLevel() * 20, Player.GetLevel() * 30);
    int BaseAtk = GetRandomNum(Player.GetLevel() * 5, Player.GetLevel() * 10);

    // (방어력, 경험치, 골드는 기획서에 공식이 없어 임의의 스케일링 적용)
    int BaseDef = GetRandomNum(Player.GetLevel() * 2, Player.GetLevel() * 4);
    int BaseExp = GetRandomNum(Player.GetLevel() * 10, Player.GetLevel() * 15);
    int BaseGold = GetRandomNum(Player.GetLevel() * 20, Player.GetLevel() * 30);

    // 2. 기획서 2번 요구사항: 3종의 일반 몬스터 목록 및 특징 부여
    int MonsterType = rand() % 3; // 0, 1, 2 랜덤 조우

    string Name;
    int FinalHp, FinalAtk, FinalDef, FinalExp, FinalGold;

    if (MonsterType == 0) {
        // [짭새] 체력이 높고 방어력이 낮음, 골드를 적게 줌
        Name = "monster1";
        FinalHp = (int)(BaseHp * 1.2);   FinalAtk = BaseAtk;
        FinalDef = (int)(BaseDef * 0.5); FinalExp = BaseExp;       FinalGold = (int)(BaseGold * 0.5);
    }
    else if (MonsterType == 1) {
        // [짜바리] 표준적인 스탯, 골드를 많이 줌
        Name = "monster2";
        FinalHp = BaseHp;                FinalAtk = BaseAtk;
        FinalDef = BaseDef;              FinalExp = BaseExp;       FinalGold = (int)(BaseGold * 1.5);
    }
    else {
        // [칼잽이] 체력이 낮지만 공격력/방어력이 매우 높음, 경험치를 많이 줌
        Name = "monster3";
        FinalHp = (int)(BaseHp * 0.8);   FinalAtk = (int)(BaseAtk * 1.3);
        FinalDef = (int)(BaseDef * 1.2); FinalExp = (int)(BaseExp * 1.5); FinalGold = BaseGold;
    }

    // 최종 완성된 몬스터 객체 반환
    return Monster(Name, FinalHp, FinalAtk, FinalDef, FinalExp, FinalGold);
}
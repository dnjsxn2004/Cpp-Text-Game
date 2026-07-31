#include "Monster.h"
#include <cstdlib>
#include <ctime>
#include "Player.h"
#include "GameContext.h"
#include <vector>

// 생성자 초기화
Monster::Monster(string Name, int Hp, int Attack, int Defense, int ExpReward, int GoldReward, string SkillName, int SkillProbability, float SkillMultiplier)
    : Name(Name), Hp(Hp), MaxHp(Hp), Attack(Attack), Defense(Defense), ExpReward(ExpReward), GoldReward(GoldReward), SkillName(SkillName), SkillProbability(SkillProbability), SkillMultiplier(SkillMultiplier){}

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
        << " | DEF: " << Defense << " | 보상: " << ExpReward << "EXP, " << GoldReward << "G\n";
}

// =========================================================================
// [기획서 반영] 몬스터 랜덤 생성 및 스케일링 로직
// =========================================================================
int GetRandomNum(int Min, int Max) 
{
    return Min + rand() % ((Max - Min) + 1);
}

// =========================================================================
// [신규] 확률적 스킬 공격 데미지 계산 함수
// =========================================================================
int Monster::CalculateAttackDamage() const
{
    int Roll = GetRandomNum(1, 100); // 1~100 사이의 난수 생성

    // 스킬 발동 확률(SkillProbability) 안에 난수 값이 들어오면 스킬 발동!
    if (Roll <= SkillProbability) 
    {
        int SkillDamage = static_cast<int>(Attack * SkillMultiplier);
        
        return SkillDamage;
    }

    // 확률을 뚫지 못하면 일반 공격
    return Attack;
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

    string Name, SkillName;
    int FinalHp, FinalAtk, FinalDef, FinalExp, FinalGold, SkillProbability;
    float SkillMultiplier;

    if (MonsterType == 0) {
        // [짭새] 체력이 높고 방어력이 낮음, 골드를 적게 줌
        Name = "짭새";
        FinalHp = (int)(BaseHp * 1.2);   FinalAtk = BaseAtk;
        FinalDef = (int)(BaseDef * 0.5); FinalExp = BaseExp;       FinalGold = (int)(BaseGold * 0.5);
        SkillName = "테이저건 발사";
        SkillProbability = 15;
        SkillMultiplier = 1.3f;
    }
    else if (MonsterType == 1) {
        // [짜바리] 표준적인 스탯, 골드를 많이 줌
        Name = "짜바리";
        FinalHp = BaseHp;                FinalAtk = BaseAtk;
        FinalDef = BaseDef;              FinalExp = BaseExp;       FinalGold = (int)(BaseGold * 1.5);
        SkillName = "조잡한 주먹 연타";
        SkillProbability = 20; // 20%
        SkillMultiplier = 1.5f;
    }
    else 
    {
        // [칼잽이] 체력이 낮지만 공격력/방어력이 매우 높음, 경험치를 많이 줌
        Name = "칼잽이";
        FinalHp = (int)(BaseHp * 0.8);   FinalAtk = (int)(BaseAtk * 1.3);
        FinalDef = (int)(BaseDef * 1.2); FinalExp = (int)(BaseExp * 1.5); FinalGold = BaseGold;
        SkillName = "모가지에 칼침 꼽기";
        SkillProbability = 30; // 30%
        SkillMultiplier = 1.8f;
    }

    // 최종 완성된 몬스터 객체 반환
    return Monster(Name, FinalHp, FinalAtk, FinalDef, FinalExp, FinalGold, SkillName,SkillProbability, SkillMultiplier);
}

// =========================================================================
// 최종 보스 생성 로직
// =========================================================================
Monster SpawnFinalBoss(GameContext& Context) 
{
    Player& CurrentPlayer = Context.GetPlayer();
    string PlayerName = CurrentPlayer.GetName();
    int Level = CurrentPlayer.GetLevel();

    string BossName = "[최종 보스]";
    string SkillName;

    // 플레이어의 선택에 따른 최종 보스 라이벌 매칭
    if (PlayerName == "진태식") 
    {
        BossName += "류노스케";
        SkillName = "이마나리롤";
    }
    else if (PlayerName == "류노스케") 
    {
        BossName += "진태식";
        SkillName = "유도식테이크다운";
    }

   

    // 최종 보스 스케일링 (일반 몬스터 베이스보다 압도적으로 강함)
    int BaseHp = Level * 50;
    int BaseAtk = Level * 10;
    int BaseDef = Level * 5;

    // 보스 버프 적용
    int FinalHp = BaseHp * 5;
    int FinalAtk = BaseAtk * 2;
    int FinalDef = BaseDef * 2;
    int FinalExp = Level * 150;
    int FinalGold = Level * 300;

    int SkillProbability = 60; // 보스는 60% 확률로 스킬을 자주 사용
    float SkillMultiplier = 2.5f; // 보스의 스킬은 2.5배의 막대한 피해

    return Monster(BossName, FinalHp, FinalAtk, FinalDef, FinalExp, FinalGold, SkillName, SkillProbability, SkillMultiplier);
}


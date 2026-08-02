#include "Monster.h"
#include "GameContext.h"
#include "Player.h"

#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;


Monster::Monster()
    : Name(" "),
    Hp(1),
    MaxHp(1),
    Attack(0),
    Defense(0),
    ExpReward(0),
    GoldReward(0),
    SkillName("없음"),
    SkillProbability(0),
    SkillMultiplier(1.0f)
{
}


Monster::Monster(
    string Name,
    int Hp,
    int Attack,
    int Defense,
    int ExpReward,
    int GoldReward,
    string SkillName,
    int SkillProbability,
    float SkillMultiplier
)
    : Name(Name),
    Hp(Hp),
    MaxHp(Hp),
    Attack(Attack),
    Defense(Defense),
    ExpReward(ExpReward),
    GoldReward(GoldReward),
    SkillName(SkillName),
    SkillProbability(SkillProbability),
    SkillMultiplier(SkillMultiplier)
{
}


void Monster::SetName(const string& name)
{
    Name = name;
}

void Monster::SetHp(int hp)
{
    Hp = hp;

    if (Hp < 0)
    {
        Hp = 0;
    }

    if (Hp > MaxHp)
    {
        Hp = MaxHp;
    }
}

void Monster::SetMaxHp(int maxHp)
{
    MaxHp = maxHp;

    if (MaxHp < 1)
    {
        MaxHp = 1;
    }

    if (Hp > MaxHp)
    {
        Hp = MaxHp;
    }
}

void Monster::SetAttack(int attack)
{
    Attack = attack;
}

void Monster::SetDefense(int defense)
{
    Defense = defense;
}

void Monster::SetExpReward(int expReward)
{
    ExpReward = expReward;
}

void Monster::SetGoldReward(int goldReward)
{
    GoldReward = goldReward;
}

void Monster::SetSkillName(const string& skillName)
{
    SkillName = skillName;
}

void Monster::SetSkillProbability(int skillProbability)
{
    SkillProbability = skillProbability;

    if (SkillProbability < 0)
    {
        SkillProbability = 0;
    }

    if (SkillProbability > 100)
    {
        SkillProbability = 100;
    }
}

void Monster::SetSkillMultiplier(float skillMultiplier)
{
    SkillMultiplier = skillMultiplier;

    if (SkillMultiplier < 0.0f)
    {
        SkillMultiplier = 0.0f;
    }
}

// 실제 데미지 처리 구현
int Monster::TakeDamage(int damage)
{
    if (damage < 0)
    {
        damage = 0;
    }

    Hp -= damage;

    if (Hp < 0)
    {
        Hp = 0;
    }

    return damage;
}


bool Monster::IsDead() const
{
    return Hp <= 0;
}


void Monster::PrintInfo() const
{
    cout << "==============================" << endl;
    cout << "몬스터 이름: " << Name << endl;
    cout << "HP: " << Hp << " / " << MaxHp << endl;
    cout << "공격력: " << Attack << endl;
    cout << "방어력: " << Defense << endl;
    cout << "경험치 보상: " << ExpReward << endl;
    cout << "골드 보상: " << GoldReward << endl;
    cout << "스킬: " << SkillName << endl;
    cout << "스킬 확률: " << SkillProbability << "%" << endl;
    cout << "==============================" << endl;
}


int Monster::CalculateAttackDamage() const
{
    int chance = rand() % 100 + 1;

    if (chance <= SkillProbability)
    {
        return static_cast<int>(Attack * SkillMultiplier);
    }

    return Attack;
}

// 일반 전투용 스폰 몬스터로 수정
Monster SpawnRandomMonster(GameContext& Context)
{
    Player& player = Context.GetPlayer();
    int level = player.GetLevel();

    int randomIndex = rand() % 3;

    int hpScale = (level - 1) * 25;
    int attackScale = (level - 1) * 5;
    int defenseScale = (level - 1) * 2;
    int rewardScale = (level - 1) * 15;
    
    
    //지역 변수로 살짝 수정했습니다.
    switch (randomIndex)
    {
    case 0:
        return Monster(
            "양아치",
            80 + hpScale,
            15 + attackScale,
            3 + defenseScale,
            30 + rewardScale,
            50 + rewardScale,
            "비열한 기습",
            20,
            1.5f
        );

    case 1:
        return Monster(
            "불량배",
            110 + hpScale,
            18 + attackScale,
            5 + defenseScale,
            40 + rewardScale,
            70 + rewardScale,
            "각목 후려치기",
            25,
            1.6f
        );

    default:
        return Monster(
            "조직원",
            140 + hpScale,
            22 + attackScale,
            7 + defenseScale,
            50 + rewardScale,
            90 + rewardScale,
            "급소 찌르기",
            30,
            1.7f
        );
    }
}


Monster SpawnMiddleBoss(GameContext& Context)
{
    Player& player = Context.GetPlayer();
    int level = player.GetLevel();

    int hpScale = (level - 1) * 40;
    int attackScale = (level - 1) * 7;
    int defenseScale = (level - 1) * 3;
    int rewardScale = (level - 1) * 30;

    return Monster(
        "중간보스",
        260 + hpScale,
        35 + attackScale,
        15 + defenseScale,
        120 + rewardScale,
        200 + rewardScale,
        "압도적인 연격",
        40,
        1.8f
    );
}


Monster SpawnFinalBoss(GameContext& Context)
{
    Player& player = Context.GetPlayer();
    string playerName = player.GetName();
    int level = player.GetLevel();

    int hpScale = (level - 1) * 60;
    int attackScale = (level - 1) * 10;
    int defenseScale = (level - 1) * 4;
    int rewardScale = (level - 1) * 50;


    if (playerName == "진태식")
    {
        return Monster(
            "류노스케",
            420 + hpScale,
            48 + attackScale,
            18 + defenseScale,
            300 + rewardScale,
            500 + rewardScale,
            "용의 일격",
            60,
            2.0f
        );
    }

    if (playerName == "류노스케")
    {
        return Monster(
            "진태식",
            500 + hpScale,
            42 + attackScale,
            25 + defenseScale,
            300 + rewardScale,
            500 + rewardScale,
            "업어치기",
            60,
            2.0f
        );
    }
    
    return Monster(
        "최종보스",
        450 + hpScale,
        45 + attackScale,
        20 + defenseScale,
        300 + rewardScale,
        500 + rewardScale,
        "최후의 일격",
        60,
        2.0f
    );
}

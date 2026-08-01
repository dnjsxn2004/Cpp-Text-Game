#include "Battle.h"
#include "GameContext.h"
#include "Player.h"
#include "ConsolUI.h"
#include "InputManager.h"
#include "StatBonus.h"
#include <algorithm>
#include <random>
#include <iostream>

// 확률생성
int Battle::CheckChance()
{
	// 난수 생성기
	std::random_device rd;
	std::mt19937 gen(rd());

	// 1~100 범위의 정수 생성
	std::uniform_int_distribution<int> Number(1, 100);

	int Chance= Number(gen);
	return Chance;   // 1~100 범위의 다양한 확률공식에 사용될 값을 반환
}

// 현재 설정된 주사위 종류에 따라 주사위를 굴립니다.
int Battle::RollDice()
{
	// 난수 생성기
	std::random_device rd;
	std::mt19937 gen(rd());

	// 1~6 범위의 정수 생성
	std::uniform_int_distribution<int> dice(1, 6);

	int DiceValue = dice(gen);
	return DiceValue;   // 1~6 범위의 주사위 값을 반환
}



// 1부터 6까지의 일반 주사위 값을 반환합니다.
int Battle::RollNormalDice()
{
	return RollDice();
}

// 1부터 6까지의 일반 주사위 값을 반환하고 그 값에 +1을 더합니다 (6이 나올 경우 더하지 않습니다.)
int Battle::RollLuckyDice()
{
	if (RollDice() < 6)
	{
		return RollDice() + 1;
	}
	else
	{
		return RollDice();
	}
}

// 1부터 6까지의 일반 주사위 값을 2번 반환하고 그 중 큰 값을 반환합니다.
int Battle::RollDoubleDice()
{
	int FirstDiceValue = RollDice();
	int SecondDiceValue = RollDice();

	//std::cout << "첫 번째: " << FirstDiceValue << std::endl;
	//std::cout << "두 번째: " << SecondeDiceValue << std::endl;

	return (std::max)(FirstDiceValue, SecondDiceValue);
}

// 1과 6만 나오는 주사위입니다.
int Battle::RollExtremeDice()
{
	if (RollDice() < 4)
	{
		return 1;
	}
	else
	{
		return 6;
	}
}

// 주사위를 굴리고 나온 값에 따라 일반데미지의 값을 반환합니다.
int Battle::PlayerDiceMeleeDamage(GameContext& context1, GameContext& context2, const StatBonus& equipBonus, const StatBonus& potionBonus)
{
	Player& player = context1.GetPlayer();
	Monster& monster = context2.GetMonster();

	int DiceNumber = RollDice();
	int Damage = 0;

	IsDamageChoice = true;

	switch (DiceNumber)
	{
	case 1:
		return 0;
	case 2:
		Damage = (player.GetMeleeDamage( equipBonus, potionBonus) - monster.GetDefense()) / 2;
		break;
	case 3:
	case 4:
		Damage = (player.GetMeleeDamage( equipBonus, potionBonus) - monster.GetDefense());
		break;
	case 5:
		Damage = (player.GetMeleeDamage( equipBonus, potionBonus) - monster.GetDefense()) * 2;
		break;
	case 6:
		CheckChance();
		if (CheckChance() > 50)
		{
			IsMonsterStunned = true;
			ConsoleUI::PrintMessage("상대가 스턴에 걸렸습니다.");
		}
		else
		{
			IsMonsterStunned = false;
		}
		Damage = (player.GetMeleeDamage( equipBonus, potionBonus) - monster.GetDefense()) * 2;
		break;
	}
	if (Damage <= 0)
	{
		Damage = 1;
	}
	return Damage;
}

// 주사위를 굴리고 나온 값에 따라 스킬데미지의 값을 반환합니다.
int Battle::PlayerDiceSkillDamage(GameContext& context1, GameContext& context2, const StatBonus& equipBonus, const StatBonus& potionBonus)
{
	Player& player = context1.GetPlayer();
	Monster& monster = context2.GetMonster();

	int DiceNumber = RollDice();
	int Damage = 0;

	IsDamageChoice = false;

	switch (DiceNumber)
	{
	case 1:
		return 0;
	case 2:
		 Damage = (player.GetSkillDamage( equipBonus, potionBonus) - monster.GetDefense()) / 2;
		break;
	case 3:
	case 4:
		Damage = (player.GetSkillDamage( equipBonus, potionBonus) - monster.GetDefense());
		break;
	case 5:
		Damage = (player.GetSkillDamage( equipBonus, potionBonus) - monster.GetDefense()) * 2;
		break;
	case 6:
		int Chance = CheckChance();
		if (Chance > 50)
		{
			IsMonsterStunned = true;
			ConsoleUI::PrintMessage("상대가 스턴에 걸렸습니다.");
		}
		else
		{
			IsMonsterStunned = false;
		}
		Damage = (player.GetSkillDamage( equipBonus,  potionBonus) - monster.GetDefense()) * 2;
		break;
	}
	if (Damage <= 0)
	{
		Damage = 1;
	}
	return Damage;
}

// ISDamageChoice 값에 따라 일반or스킬공격값 반환.
int Battle::PlayerDiceDamage(GameContext& context1, GameContext& context2, const StatBonus& equipBonus, const StatBonus& potionBonus)
{
	if (IsDamageChoice)
	{
		return PlayerDiceMeleeDamage(context1, context2, equipBonus, potionBonus);
	}
	else
	{
		return PlayerDiceSkillDamage(context1, context2, equipBonus, potionBonus);
	}
}

// 도망의 성공여부 값을 반환합니다.
bool Battle::PlayerRunaway(GameContext& context)
{
	if (RollDice() > 3)
	{
		return true;
	}
	else
	{
		return false;
	}
}

// 플레이어 턴을 카운트합니다.
int Battle::PlayerTurnCount()
{
	return 1;
}

// 처치한 몬스터 킬을 카운트합니다.
int Battle::GetMonsterKillCount(GameContext& context)
{
	MonsterkillCount += 1;
	return MonsterkillCount;
}

// 일반몬스터의 일반데미지 값을 반환합니다.
int Battle::NormalMonsterMeleeDamage(GameContext& context1, GameContext& context2, const StatBonus& equipBonus, const StatBonus& potionBonus)
{
	Player& player = context1.GetPlayer();
	Monster& monster = context2.GetMonster();
	if ((monster.GetAttack() - player.GetTrueDefense(equipBonus, potionBonus)) > 0)
	{
		return (monster.GetAttack() - player.GetTrueDefense(equipBonus, potionBonus));
	}
	else
	{
		return 1;
	}
}

//중간보스몬스터의 일반데미지와 스킬데미지 값을 반환합니다. 
int Battle::MiddleBossMonsterDamage(GameContext& context1, GameContext& context2, const StatBonus& equipBonus, const StatBonus& potionBonus)
{
	Player& player = context1.GetPlayer();
	Monster& monster = context2.GetMonster();
	if ((monster.CalculateAttackDamage() - player.GetTrueDefense(equipBonus, potionBonus)) > 0)
	{
		return (monster.CalculateAttackDamage() - player.GetTrueDefense(equipBonus, potionBonus));
	}
	else
	{
		return 1;
	}
}


//최종보스몬스터의 일반데미지와 스킬데미지 값을 반환합니다.           //moster.cpp 메세지 출력 필요
int Battle::FinalBossMonsterDamage(GameContext& context1, GameContext& context2, const StatBonus& equipBonus, const StatBonus& potionBonus)
{
	Player& player = context1.GetPlayer();
	Monster& monster = context2.GetMonster();
	if ((monster.CalculateAttackDamage() - player.GetTrueDefense(equipBonus, potionBonus)) > 0)
	{
		return (monster.CalculateAttackDamage() - player.GetTrueDefense(equipBonus, potionBonus));
	}
	else
	{
		return 1;
	}
}

// 승패 판정에 대한 값을 반환합니다.
bool Battle::CheckBattleResult(GameContext& context1, GameContext& context2)     //승패여부 true: 승 false:패
{
	Player& player = context1.GetPlayer();
	Monster& monster = context2.GetMonster();
	
	if (monster.GetHp()<=0 )
	{
		BattleReward(context1,context2);
		GetMonsterKillCount(context2);
		return true;
	}
	else if(player.GetHp()<=0)
	{
		return false;
	}
}

// 배틀 승리시 보상
void Battle::BattleReward(GameContext& context1, GameContext& context2)
{
	Player& player = context1.GetPlayer();
	Monster& monster = context2.GetMonster();
	player.SetExp(player.GetExp() + monster.GetExpReward());
	player.SetGold(player.GetGold() + monster.GetGoldReward());
}

#include "Battle.h"
#include "GameContext.h"
#include "Player.h"
#include "Battle.h"
#include "GameContext.h"
#include "ConsolUI.h"
#include "InputManager.h"
#include <algorithm>
#include <random>
#include <iostream>

Battle::Battle()
	: TurnCount(1), LastDiceValue(0), IsPlayerDefending(false), IsMonsterStunned(false), CurrentDiceType(DiceType::Normal), BattleResult(BattleResult::None)
{
}

// 전투 내부 상태를 초기값으로 되돌립니다.
void Battle::InitializeBattle()
{
	TurnCount = 1;
	lastDiceValue = 0;

	IsPlayerDefending = false;
	IsmonsterStunned = false;

	BattleResult = BattleResult::None;
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

int Battle::RollDoubleDice()
{
	int FirstDiceValue = RollDice();
	int SecondDiceValue = RollDice();

	//std::cout << "첫 번째: " << FirstDiceValue << std::endl;
	//std::cout << "두 번째: " << FirstDiceValue << std::endl;

	return std::max(FirstDiceValue, SecondDiceValue);
}

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

int Battle::PlayerDiceDamage()
{
	switch (RollDice())
	{
	case 1:
		return 0;
		break;
	case 2:
		return (Player.GetMeleeDamage(const StatBonus & equipBonus, const StatBonus & potionBonus) - Monster.GetDefense()) / 2;
		break;
	case 3:
		return (Player.GetMeleeDamage(const StatBonus & equipBonus, const StatBonus & potionBonus) - Monster.GetDefense());
		break;
	case 4:
		return (Player.GetMeleeDamage(const StatBonus & equipBonus, const StatBonus & potionBonus) - Monster.GetDefense());
		break;
	case 5:
		return (Player.GetMeleeDamage(const StatBonus & equipBonus, const StatBonus & potionBonus) - Monster.GetDefense()) * 2;
		break;
	case 6:
		RollDice();
		if (RollDice() >= 4)
		{
			IsMonsterStunned = true;
		}
		else
		{
			IsMonsterStunned = false;
		}
		return (Player.GetMeleeDamage(const StatBonus & equipBonus, const StatBonus & potionBonus) - Monster.GetDefense()) * 2;
		break;
	}
}

bool PlayerRunaway(GameContext& context)
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

int PlayerAttack(GameContext& context)
{
	Battle PlayerDiceDamage();
	return  
}
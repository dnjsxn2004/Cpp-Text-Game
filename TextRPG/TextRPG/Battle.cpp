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
	std::uniform_int_distribution<int> Chance(1, 100);

	int CheckChance= Chance(gen);
	return CheckChance;   // 1~6 범위의 주사위 값을 반환
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
int Battle::PlayerDiceMeleeDamage(GameContext& context, const StatBonus& equipBonus, const StatBonus& potionBonus)
{
	Player& player = context.GetPlayer();
	Monster& monster = context.GetMonster();
	int DiceNumber = RollDice();
	IsDamageChoice = true;
	switch (DiceNumber)
	{
	case 1:
		return 0;
		break;
	case 2:
		return (player.GetMeleeDamage( equipBonus, potionBonus) - monster.GetDefense()) / 2;
		break;
	case 3:
		return (player.GetMeleeDamage( equipBonus, potionBonus) - monster.GetDefense());
		break;
	case 4:
		return (player.GetMeleeDamage( equipBonus, potionBonus) - monster.GetDefense());
		break;
	case 5:
		return (player.GetMeleeDamage( equipBonus, potionBonus) - monster.GetDefense()) * 2;
		break;
	case 6:
		CheckChance();
		if (CheckChance() >= 4)
		{
			IsMonsterStunned = true;
			ConsoleUI::PrintMessage("상대가 스턴에 걸렸습니다.");
		}
		else
		{
			IsMonsterStunned = false;
		}
		return (player.GetMeleeDamage( equipBonus, potionBonus) - monster.GetDefense()) * 2;
		break;
	}
}

// 주사위를 굴리고 나온 값에 따라 스킬데미지의 값을 반환합니다.
int Battle::PlayerDiceSkillDamage(GameContext& context, const StatBonus& equipBonus, const StatBonus& potionBonus)
{
	Player& player = context.GetPlayer();
	Monster& monster = context.GetMonster();
	int DiceNumber = RollDice();
	IsDamageChoice = false;
	switch (DiceNumber)
	{
	case 1:
		return 0;
		break;
	case 2:
		return (player.GetSkillDamage( equipBonus, potionBonus) - monster.GetDefense()) / 2;
		break;
	case 3:
		return (player.GetSkillDamage( equipBonus, potionBonus) - monster.GetDefense());
		break;
	case 4:
		return (player.GetSkillDamage( equipBonus, potionBonus) - monster.GetDefense());
		break;
	case 5:
		return (player.GetSkillDamage( equipBonus, potionBonus) - monster.GetDefense()) * 2;
		break;
	case 6:
		CheckChance();
		if (CheckChance() >= 4)
		{
			IsMonsterStunned = true;
			ConsoleUI::PrintMessage("상대가 스턴에 걸렸습니다.");
		}
		else
		{
			IsMonsterStunned = false;
		}
		return (player.GetSkillDamage( equipBonus,  potionBonus) - monster.GetDefense()) * 2;
		break;
	}
}

// ISDamageChoice 값에 따라 일반or스킬공격값 반환.
int Battle::PlayerDiceDamage(GameContext& context, const StatBonus& equipBonus, const StatBonus& potionBonus)
{
	if (IsDamageChoice)
	{
		return PlayerDiceMeleeDamage(context, equipBonus,  potionBonus);
	}
	else
	{
		return PlayerDiceSkillDamage( context,  equipBonus, potionBonus);
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
int Battle::NormalMonsterMeleeDamage(GameContext& context)
{
	Player& player = context.GetPlayer();
	Monster& monster = context.GetMonster();
	return (monster.GetAttack() - player.GetDefense());
}

//보스몬스터의 일반데미지 값을 반환합니다.
int Battle::BossMonsterMeleeDamage(GameContext& context)
{
	Player& player = context.GetPlayer();
	Monster& monster = context.GetMonster();
	return (monster.GetAttack() - player.GetDefense());
}

//보스몬스터의 스킬데미지 값을 반환합니다.
int Battle::BossMonsterSkillDamage(GameContext& context)
{
	Player& player = context.GetPlayer();
	Monster& monster = context.GetMonster();
	return (monster.GetAttack() - player.GetDefense());
}

//보스몬스터의 일반데미지 값을 반환합니다.
int Battle::BossMonsterMeleeDamage(GameContext& context)
{
	Player& player = context.GetPlayer();
	Monster& monster = context.GetMonster();
	return (monster.GetAttack() - player.GetDefense());
}

//보스몬스터의 스킬데미지 값을 반환합니다.
int Battle::BossMonsterSkillDamage(GameContext& context)
{
	Player& player = context.GetPlayer();
	Monster& monster = context.GetMonster();
	return (monster.GetAttack() - player.GetDefense());
}

// 승패 판정에 대한 값을 반환
bool Battle::CheckBattleResult(GameContext& context)     //승패여부 true: 승 false:패
{
	Player& player = context.GetPlayer();
	Monster& monster = context.GetMonster();
	
	if (monster.GetHp()<=0 )
	{

		GetMonsterKillCount(context);
		return true;
	}
	else if(player.GetHp()<=0)
	{
		return false;
	}
}

// 

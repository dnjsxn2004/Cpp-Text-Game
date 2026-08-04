#include "Battle.h"
#include "GameContext.h"
#include "Player.h"
#include "ConsolUI.h"
#include "InputManager.h"
#include "StatBonus.h"
#include "BattleResult.h"

#include <iostream>
#include <algorithm>
#include <random>

// [추가] 생성자
Battle::Battle(GameContext& context)
	: context(context)
{
	// [추가] 전투 상태 초기화
	IsDamageChoice = true;

	// [추가] 기존 Battle.h에 존재하던 상태값 초기화
	IsPlayerDefending = false;

	IsMonsterStunned = false;

	// [추가] 전투 결과 처리 여부 초기화
	// 보상 중복 지급을 막기 위해 CheckBattleResult()에서 사용
	IsBattleResult = false;

	MonsterkillCount = 0;
	LastDiceValue = 0;
	TrunCount = 0;

	// [추가] 현재 사용하는 주사위 종류 초기화
	CurrentDiceType = DiceType::Normal;
}

// [추가] 전투 전체 실행 함수
BattleResult Battle::RunBattle(GameContext & context)
{
	Player& player = context.GetPlayer();
	Monster& monster = context.GetMonster();

	std::vector<std::string> diceLines;
	std::vector<std::string> logLines;
	std::vector<std::string> actionLines;
	std::vector<std::string> statusLines;

	bool isBattleRunning = true;

	actionLines =
	{
		"1. 일반 공격",
		"2. 스킬 사용",
		"3. 아이템 사용",
		"4. 도망"
	};

	ConsoleUI::AddLog(
		logLines,
		monster.GetName() + " 등장!"
	);

	while (isBattleRunning)
	{
		statusLines.clear();

		statusLines.push_back(
			"PLAYER : " + player.GetName());

		statusLines.push_back(
			"HP : " +
			std::to_string(player.GetHp()) +
			" / " +
			std::to_string(player.GetMaxHp()));

		statusLines.push_back(
			"MP : " +
			std::to_string(player.GetMp()) +
			" / " +
			std::to_string(player.GetMaxMp()));

		statusLines.push_back("");

		statusLines.push_back(
			"MONSTER : " + monster.GetName());

		statusLines.push_back(
			"HP : " +
			std::to_string(monster.GetHp()) +
			" / " +
			std::to_string(monster.GetMaxHp()));

		UIScreen screen;

		screen.a = diceLines;
		screen.b = logLines;
		screen.c = actionLines;
		screen.d = statusLines;

		ConsoleUI::DrawFullLayout(screen);

		int choice =
			InputManager::InputInMassegeToRange(
				"선택 : ",
				1,
				4
			);

		// 일반 공격
		if (choice == 1)
		{
			StatBonus equipBonus;
			StatBonus potionBonus;

			int damage =
				this->PlayerDiceMeleeDamage(
					context,
					context,
					equipBonus,
					potionBonus
				);

			diceLines =
				ConsoleUI::PrintDiceResult(
					this->GetLastDiceValue());

			monster.SetHp(
				monster.GetHp() - damage
			);

			ConsoleUI::AddLog(
				logLines,
				ConsoleUI::
				PrintPlayerMeleeAttackResultMessage(
					player.GetName(),
					monster.GetName(),
					damage
				)
			);

			if (monster.GetHp() <= 0)
			{
				ConsoleUI::AddLog(
					logLines,
					ConsoleUI::PrintBattleVictory(
						monster.GetName()
					)
				);

				ConsoleUI::AddLog(
					logLines,
					ConsoleUI::PrintReward(
						monster.GetExpReward(),
						monster.GetGoldReward()
					)
				);

				BattleReward(context, context);

				break;
			}

			int monsterDamage =
				monster.GetAttack();

			player.SetHp(
				player.GetHp() - monsterDamage
			);

			ConsoleUI::AddLog(
				logLines,
				ConsoleUI::PrintMonsterAttackResult(
					monster.GetName(),
					player.GetName(),
					monsterDamage
				)
			);

			if (player.GetHp() <= 0)
			{
				ConsoleUI::AddLog(
					logLines,
					ConsoleUI::PrintBattleDefeat(
						player.GetName()
					)
				);

				break;
			}
		}

		// 스킬 공격
		else if (choice == 2)
		{
			const int skillMpCost = 10;

			if (player.GetMp() < skillMpCost)
			{
				ConsoleUI::AddLog(
					logLines,
					ConsoleUI::PrintNotEnoughMp()
				);
				continue;
			}

			player.SetMp(
				player.GetMp() - skillMpCost
			);

			StatBonus equipBonus;
			StatBonus potionBonus;

			int damage =
				this->PlayerDiceSkillDamage(
					context,
					context,
					equipBonus,
					potionBonus
				);

			diceLines =
				ConsoleUI::PrintDiceResult(
					this->GetLastDiceValue()
				);

			monster.SetHp(
				monster.GetHp() - damage
			);


			ConsoleUI::AddLog(
				logLines,
				ConsoleUI::
				PrintPlayerSkillAttackResultMessage(
					player.GetName(),
					monster.GetName(),
					damage
				)
			);

			if (monster.GetHp() <= 0)
			{
				ConsoleUI::AddLog(
					logLines,
					ConsoleUI::PrintBattleVictory(
						monster.GetName()
					)
				);


				ConsoleUI::AddLog(
					logLines,
					ConsoleUI::PrintReward(
						monster.GetExpReward(),
						monster.GetGoldReward()
					)
				);

				BattleReward(context, context);

				return BattleResult::Win;

				break;
			}

			int monsterDamage =
				monster.GetAttack();

			player.SetHp(
				player.GetHp() - monsterDamage
			);

			ConsoleUI::AddLog(
				logLines,
				ConsoleUI::PrintMonsterAttackResult(
					monster.GetName(),
					player.GetName(),
					monsterDamage
				)
			);

			if (player.GetHp() <= 0)
			{
				ConsoleUI::AddLog(
					logLines,
					ConsoleUI::PrintBattleDefeat(
						player.GetName()
					)
				);
				return BattleResult::Lose;

				break;
			}
		}

		// 아이템
		else if (choice == 3)
		{
			ConsoleUI::AddLog(
				logLines,
				"아이템 기능 준비 중"
			);
		}

		// 도망
		else if (choice == 4)
		{
			int diceValue =
				this->RollDice();

			diceLines =
				ConsoleUI::PrintDiceResult(
					diceValue);

			bool success =
				(diceValue >= 4);

			if (success)
			{
				ConsoleUI::AddLog(
					logLines,
					ConsoleUI::PrintRunawaySuccess()
				);

				return BattleResult::Escape;

				break;
			}
			else
			{
				ConsoleUI::AddLog(
					logLines,
					ConsoleUI::PrintRunawayFail()
				);

				int monsterDamage = monster.GetAttack();

				player.SetHp(
					player.GetHp() - monsterDamage
				);

				ConsoleUI::AddLog(
					logLines,
					ConsoleUI::PrintMonsterAttackResult(
						monster.GetName(),
						player.GetName(),
						monsterDamage
					)
				);

				if (player.GetHp() <= 0)
				{
					ConsoleUI::AddLog(
						logLines,
						ConsoleUI::PrintBattleDefeat(
							player.GetName()
						)
					);

					break;
				}
			}

		}
	}

	UIScreen screen;

	screen.a = diceLines;
	screen.b = logLines;
	screen.c = actionLines;
	screen.d = statusLines;

	ConsoleUI::DrawFullLayout(screen);

	InputManager::Wait();

}


// 확률생성
int Battle::CheckChance()
{
	// 난수 생성기
	std::random_device rd;
	std::mt19937 gen(rd());

	// 1~100 범위의 정수 생성
	std::uniform_int_distribution<int> Number(1, 100);

	int Chance = Number(gen);
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
	int DiceValue;
	DiceValue = dice(gen);
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
	// [기존 코드 주석]
	// if (RollDice() < 6)
	// {
	// 	return RollDice() + 1;
	// }
	// else
	// {
	// 	return RollDice();
	//

	// [수정] RollDice를 여러 번 호출하지 않도록 수정
	int DiceValue = RollDice();

	if (DiceValue < 6)
	{
		return DiceValue + 1;
	}
	else
	{
		return DiceValue;
	}
}

// 1부터 6까지의 일반 주사위 값을 2번 반환하고 그 중 큰 값을 반환
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

// 주사위를 굴리고 나온 값에 따라 일반데미지의 값을 반환
int Battle::PlayerDiceMeleeDamage(GameContext& context1, GameContext& context2, const StatBonus& equipBonus, const StatBonus& potionBonus)
{
	Player& player = context1.GetPlayer();
	Monster& monster = context2.GetMonster();

	int DiceNumber = RollDice();
	int Damage = 0;

	// [추가] 마지막 주사위 값 저장
	SetLastDiceValue(DiceNumber);

	IsDamageChoice = true;

	switch (DiceNumber)
	{
	case 1:
		return 0;

	case 2:
		Damage = (player.GetMeleeDamage(equipBonus, potionBonus) - monster.GetDefense()) / 2;
		break;

	case 3:
		Damage = (player.GetMeleeDamage(equipBonus, potionBonus) - monster.GetDefense());
		break;
	case 4:
		Damage = (player.GetMeleeDamage(equipBonus, potionBonus) - monster.GetDefense());
		break;

	case 5:
		Damage = (player.GetMeleeDamage(equipBonus, potionBonus) - monster.GetDefense()) * 2;
		break;

	case 6:
		// [기존 코드 주석]
		// CheckChance();
		// if (CheckChance() > 50)
		// {
		// 	IsMonsterStunned = true;
		// 	ConsoleUI::PrintMessage("상대가 스턴에 걸렸습니다.");
		// }
		// else
		// {
		// 	IsMonsterStunned = false;
		// }

		// [수정] 확률 판정 1회만 수행
		if (CheckChance() > 50)
		{
			IsMonsterStunned = true;
		}
		else
		{
			IsMonsterStunned = false;
		}

		Damage = (player.GetMeleeDamage(equipBonus, potionBonus) - monster.GetDefense()) * 2;
		break;
	}

	if (Damage <= 0)
	{
		Damage = 1;
	}

	return Damage;
}

// 주사위를 굴리고 나온 값에 따라 스킬데미지의 값을 반환
int Battle::PlayerDiceSkillDamage(GameContext& context1, GameContext& context2, const StatBonus& equipBonus, const StatBonus& potionBonus)
{
	Player& player = context1.GetPlayer();
	Monster& monster = context2.GetMonster();

	int DiceNumber = RollDice();
	int Damage = 0;

	// [추가] 마지막 주사위 값 저장
	SetLastDiceValue(DiceNumber);

	IsDamageChoice = false;

	switch (DiceNumber)
	{
	case 1:
		return 0;

	case 2:
		Damage = (player.GetSkillDamage(equipBonus, potionBonus) - monster.GetDefense()) / 2;
		break;

	case 3:
		Damage = (player.GetSkillDamage(equipBonus, potionBonus) - monster.GetDefense());
		break;
	case 4:
		Damage = (player.GetSkillDamage(equipBonus, potionBonus) - monster.GetDefense());
		break;

	case 5:
		Damage = (player.GetSkillDamage(equipBonus, potionBonus) - monster.GetDefense()) * 2;
		break;

	case 6:
	{
		int Chance = CheckChance();

		if (Chance > 50)
		{
			IsMonsterStunned = true;

			// [기존 코드 주석]
			// ConsoleUI::PrintMessage("상대가 스턴에 걸렸습니다.");

			
		}
		else
		{
			IsMonsterStunned = false;
		}

		Damage = (player.GetSkillDamage(equipBonus, potionBonus) - monster.GetDefense()) * 2;
		break;
	}
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
bool Battle::PlayerRunaway()
{
	if (CheckChance() > 50)
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
	SetTrunCount(GetTrunCount() + 1);             //멤버변수 턴카운트를 더하는 함수입니다.
	return 1;
}

// 처치한 몬스터 킬을 카운트합니다.
int Battle::GetMonsterKillCount()
{
	return MonsterkillCount;
}

// [추가] 처치한 몬스터 킬 수를 증가
void Battle::AddMonsterKillCount()
{
	MonsterkillCount += 1;
}

// 일반몬스터의 일반데미지 값을 반환
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

//중간보스몬스터의 일반데미지와 스킬데미지 값을 반환
int Battle::MiddleBossMonsterDamage(GameContext& context1, GameContext& context2, const StatBonus& equipBonus, const StatBonus& potionBonus)
{
	Player& player = context1.GetPlayer();
	Monster& monster = context2.GetMonster();

	// [기존 코드 주석]
	// if ((monster.CalculateAttackDamage() - player.GetTrueDefense(equipBonus, potionBonus)) > 0)
	// {
	// 	return (monster.CalculateAttackDamage() - player.GetTrueDefense(equipBonus, potionBonus));
	// }
	// else
	// {
	// 	return 1;
	// }

	// [수정] CalculateAttackDamage 중복 호출 방지
	int Damage = monster.CalculateAttackDamage() - player.GetTrueDefense(equipBonus, potionBonus);

	if (Damage > 0)
	{
		return Damage;
	}
	else
	{
		return 1;
	}
}


//최종보스몬스터의 일반데미지와 스킬데미지 값을 반환.           //moster.cpp 메세지 출력 필요
int Battle::FinalBossMonsterDamage(GameContext& context1, GameContext& context2, const StatBonus& equipBonus, const StatBonus& potionBonus)
{
	Player& player = context1.GetPlayer();
	Monster& monster = context2.GetMonster();

	// [기존 코드 주석]
	// if ((monster.CalculateAttackDamage() - player.GetTrueDefense(equipBonus, potionBonus)) > 0)
	// {
	// 	return (monster.CalculateAttackDamage() - player.GetTrueDefense(equipBonus, potionBonus));
	// }
	// else
	// {
	// 	return 1;
	// }

	// [수정] CalculateAttackDamage 중복 호출 방지
	int Damage = monster.CalculateAttackDamage() - player.GetTrueDefense(equipBonus, potionBonus);

	if (Damage > 0)
	{
		return Damage;
	}
	else
	{
		return 1;
	}
}

// 승패 판정에 대한 값을 반환
bool Battle::CheckBattleResult(GameContext& context1, GameContext& context2)     //승패여부 true: 승 false:패
{
	Player& player = context1.GetPlayer();
	Monster& monster = context2.GetMonster();

	if (monster.GetHp() <= 0)
	{
		// [수정] 전투 결과 처리가 이미 끝났는지 확인하여 보상 중복 지급을 방지
		if (!IsBattleResult)
		{
			BattleReward(context1, context2);

			// 킬 수 증가는 AddMonsterKillCount()에서 처리.
			AddMonsterKillCount();

			IsBattleResult = true;
		}

		return true;
	}
	else if (player.GetHp() <= 0)
	{
		return false;
	}

	// [추가] 전투가 아직 끝나지 않은 경우
	return false;
}

// 배틀 승리시 보상
void Battle::BattleReward(GameContext& context1, GameContext& context2)
{
	Player& player = context1.GetPlayer();
	Monster& monster = context2.GetMonster();

	player.SetExp(player.GetExp() + monster.GetExpReward());
	player.SetGold(player.GetGold() + monster.GetGoldReward());


	// [추가] 기본 레벨업 처리
	while (player.GetLevel() < player.GetMaxLevel() && player.GetExp() >= player.GetMaxExp())
	{
		player.SetExp(player.GetExp() - player.GetMaxExp());
		player.SetLevel(player.GetLevel() + 1);
		player.SetMaxExp(player.GetMaxExp() + 50);

		player.SetMaxHp(player.GetMaxHp() + 20);
		player.SetMaxMp(player.GetMaxMp() + 20);
		player.SetAttack(player.GetAttack() + 5);
		player.SetDefense(player.GetDefense() + 5);

		player.SetHp(player.GetMaxHp());
		player.SetMp(player.GetMaxMp());

	}
}

int Battle::GetLastDiceValue()
{
	return LastDiceValue;
}

void Battle::SetLastDiceValue(int DiceValue)
{
	this->LastDiceValue = DiceValue;
}

int Battle::GetTrunCount()
{
	return TrunCount;
}

void Battle::SetTrunCount(int Count)
{
	this->TrunCount = Count;
}


/*
Battle.cpp 전투 진행 흐름

1. GameManager에서 전투 시작
   - GameManager는 Battle 객체를 생성한다.
   - Battle battle(context);
   - battle.RunBattle(); 형태로 전투를 실행한다.

2. RunBattle()에서 전투 전체 흐름 담당
   - Battle.cpp는 이제 단순 데미지 계산만 하지 않고,
	 플레이어 턴, 몬스터 턴, 승패 판정, 보상 지급까지 전투 진행을 담당한다.

3. 전투 시작 출력
   - ConsoleUI::PrintBattleStart(context);
   - 현재 플레이어와 몬스터 정보를 출력한다.

4. 전투 반복 조건
   - 플레이어 HP가 0보다 크고
   - 몬스터 HP가 0보다 큰 동안 전투를 반복한다.

5. 플레이어 턴
   - ConsoleUI로 현재 전투 상태와 행동 메뉴를 출력한다.
   - InputManager로 행동을 입력받는다.
   - 선택지는 일반 공격, 스킬 공격, 도망이다.

6. 일반 공격 선택 시
   - PlayerDiceMeleeDamage()에서 주사위를 굴린다.
   - 주사위 값에 따라 데미지를 계산한다.
   - 마지막 주사위 값은 SetLastDiceValue()로 저장한다.
   - 데미지가 0이면 공격 실패로 처리한다.
   - 데미지가 있으면 monster.TakeDamage(damage)로 몬스터 HP를 감소시킨다.
   - ConsoleUI로 주사위 결과와 공격 결과를 출력한다.
   - PlayerTurnCount()로 플레이어 턴 수를 증가시킨다.

7. 스킬 공격 선택 시
   - 먼저 MP가 충분한지 확인한다.
   - MP가 부족하면 ConsoleUI로 MP 부족 메시지를 출력하고 턴을 넘기지 않는다.
   - MP가 충분하면 MP를 소모한다.
   - PlayerDiceSkillDamage()에서 주사위를 굴리고 스킬 데미지를 계산한다.
   - 마지막 주사위 값은 SetLastDiceValue()로 저장한다.
   - 데미지가 0이면 스킬 실패로 처리한다.
   - 데미지가 있으면 monster.TakeDamage(damage)로 몬스터 HP를 감소시킨다.
   - ConsoleUI로 주사위 결과와 스킬 공격 결과를 출력한다.
   - PlayerTurnCount()로 플레이어 턴 수를 증가시킨다.

8. 도망 선택 시
   - PlayerRunaway()로 도망 성공 여부를 판정한다.
   - 성공하면 도망 성공 메시지를 출력하고 전투를 종료한다.
   - 실패하면 도망 실패 메시지를 출력하고 몬스터 턴으로 넘어간다.
   - 도망 실패 시 PlayerTurnCount()로 플레이어 턴 수를 증가시킨다.

9. 플레이어 공격 후 승패 판정
   - CheckBattleResult()로 몬스터 HP와 플레이어 HP를 확인한다.
   - 몬스터 HP가 0 이하이면 승리로 처리한다.
   - 승리 시 BattleReward()로 경험치와 골드를 지급한다.
   - 플레이어 HP가 0 이하이면 패배로 처리한다.
   - GetMonsterKillCount()는 조회 전용 함수로 변경
   - 실제 킬 수 증가는 AddMonsterKillCount()에서 처리
   - 보상 중복 지급 방지를 위해 IsBattleResult를 사용

10. 몬스터 스턴 처리
	- 플레이어가 주사위 6을 굴리고 스턴 확률 판정에 성공하면
	  IsMonsterStunned 값이 true가 된다.
	- 몬스터 턴 시작 전에 IsMonsterStunned를 확인한다.
	- true이면 몬스터는 행동하지 못한다.
	- 이후 IsMonsterStunned를 false로 되돌리고 다음 턴으로 넘어간다.

11. 몬스터 턴
	- 몬스터가 스턴 상태가 아니면 공격을 진행한다.
	- 현재 코드에서는 MiddleBossMonsterDamage()를 사용해 몬스터 데미지를 계산한다.
	- 계산된 데미지만큼 player.SetHp(player.GetHp() - damage)로 플레이어 HP를 감소시킨다.
	- ConsoleUI로 몬스터 공격 결과를 출력한다.

12. 몬스터 공격 후 패배 판정
	- 몬스터 공격 후 플레이어 HP가 0 이하이면 패배로 처리한다.
	- ConsoleUI로 패배 메시지를 출력하고 RunBattle()은 false를 반환한다.

13. 전투 종료 반환값
	- RunBattle()이 true를 반환하면 전투 승리 또는 도망 성공으로 처리한다.
	- RunBattle()이 false를 반환하면 플레이어 패배로 처리한다.

14. 역할 분리 기준
	- Battle.cpp: 전투 진행, 데미지 계산, 승패 판정, 보상 지급 담당
	- ConsoleUI.cpp: 출력만 담당
	- InputManager.cpp: 입력만 담당
	- GameManager.cpp: 게임 전체 흐름과 전투 시작 시점 담당
*/

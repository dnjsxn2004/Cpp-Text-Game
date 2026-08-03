#ifndef BATTLE_H_
#define BATTLE_H_
#include <iostream>
#include "GameContext.h"
#include "Player.h"
#include "ConsolUI.h"
#include "InputManager.h"
#include "StatBonus.h"
#include <algorithm>
#include <random>
#include <iostream>

class GameContext;
class Player;
class Monster;

// 전투에 사용할 주사위 종류입니다.
enum class DiceType
{
	Normal,    // 노말 다이스: 1부터 6까지 동일한 확률도 등장
	Lucky,   // 럭키 다이스: 주사위 결과에 1을 더하며 최대값은 6
	Double,  // 더블 다이스: 두번 굴린 후 더 높은 값을 사용
	extreme   // 익스트림 다이스: 1 또는 6만 등장
};

// 플레이어 공격 한 번의 결과를 저장합니다.
//
// 피해량, 주사위 값, 적중 여부, 치명타 여부, 스턴 여부를 반환하기 위해 구조체를 사용.
struct AttackResult
{
	int Damage;         // 최종 피해량
	int DiceValue;      // 공격에 사용된 주사위 값

	bool ISHit;         // 공격 적중 여부
	bool IsCritical;    // 치명타 발생 여부
	bool IsStun;        // 몬스터 스턴 발생 여부
};

class Battle
{
public:
	// 여기서 생성자 선언 초기화 안해서 cpp 에서 함
	Battle(GameContext& context);

	// [추가] 전투 전체 진행을 담당
	void RunBattle(GameContext& context);

	// 확률생성
	int CheckChance();

	// 현재 설정된 주사위 종류에 따라 주사위를 굴립니다.
	int RollDice();

	// 1부터 6까지의 일반 주사위 값을 반환합니다.
	int RollNormalDice();

	// 1부터 6까지의 일반 주사위 값을 반환하고 그 값에 +1을 더합니다 (6이 나올 경우 더하지 않습니다.)
	int RollLuckyDice();

	// 1부터 6까지의 일반 주사위 값을 2번 반환하고 그 중 큰 값을 반환합니다.
	int RollDoubleDice();

	// 1과 6만 나오는 주사위입니다.
	int RollExtremeDice();

	// 주사위를 굴리고 나온 값에 따라 일반데미지의 값을 반환합니다.
	int PlayerDiceMeleeDamage(GameContext& context1, GameContext& context2, const StatBonus& equipBonus, const StatBonus& potionBonus);

	// 주사위를 굴리고 나온 값에 따라 스킬데미지의 값을 반환합니다.
	int PlayerDiceSkillDamage(GameContext& context1, GameContext& context2, const StatBonus& equipBonus, const StatBonus& potionBonus);

	// ISDamageChoice 값에 따라 일반or스킬공격값 반환.
	int PlayerDiceDamage(GameContext& context1, GameContext& context2, const StatBonus& equipBonus, const StatBonus& potionBonus);

	// 도망의 성공여부 값을 반환합니다.
	bool PlayerRunaway();

	// 플레이어 턴을 카운트합니다.
	int PlayerTurnCount();

	// 처치한 몬스터 킬을 카운트합니다.
	int GetMonsterKillCount();

	// 일반몬스터의 일반데미지값을 반환.
	int NormalMonsterMeleeDamage(GameContext& context1, GameContext& context2, const StatBonus& equipBonus, const StatBonus& potionBonus);

	//중간보스몬스터의 일반데미지와 스킬데미지 값을 반환합니다. 
	int MiddleBossMonsterDamage(GameContext& context1, GameContext& context2, const StatBonus& equipBonus, const StatBonus& potionBonus);

	//최종보스몬스터의 일반데미지와 스킬데미지 값을 반환합니다.
	int FinalBossMonsterDamage(GameContext& context1, GameContext& context2, const StatBonus& equipBonus, const StatBonus& potionBonus);

	//승패 판정에 대한 값을 반환
	bool CheckBattleResult(GameContext& context1, GameContext& context2);

	// 배틀 승리시 보상
	void BattleReward(GameContext& context1, GameContext& context2);

	int GetLastDiceValue();

	void SetLastDiceValue(int DiceValue);

	int GetTrunCount();

	void SetTrunCount(int Count);

	void AddMonsterKillCount();


private:
	// [추가] 전투 진행에 사용할 GameContext 참조
	GameContext& context;

	int TrunCount = 0;  // 현재 턴 번호
	int LastDiceValue;  // 가장 최근에 나온 주사위 값
	int MonsterkillCount = 0; // 몬스터 킬카운트

	bool IsPlayerDefending;   // 플레이어 방어 상태
	bool IsMonsterStunned;    // 몬스터 스턴 상태
	bool IsBattleResult;     // 승패여부 true: 승 false:패
	bool IsDamageChoice; // 일반공격 or 스킬공격을 결정해줌

	DiceType CurrentDiceType;   // 현재 사용하는 주사위 종류

};

#endif

// 다이스 숫자별 데미지 1 회피 2 빗맞음 3~4 일반뎀 5 치뎀 6 치뎀+스턴(33%)?
// 다이스 
// 럭키다이스  나온값에+1
// 더블다이스 두번던지고 그중에 높은숫자적용
// 익스트림다이스 1또는6만 나오는 주사위

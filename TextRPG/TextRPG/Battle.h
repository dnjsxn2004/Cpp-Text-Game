#ifndef BATTLE_H_
#define BATTLE_H_
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
// 피해량뿐만 아니라 주사위 값, 적중 여부, 치명타 여부,
// 스턴 여부를 하나의 반환값으로 전달하기 위해 구조체를 사용합니다.
struct AttackResult
{
	int Damage;         // 최종 피해량
	int DiceValue;      // 공격에 사용된 주사위 값

	bool ISHit;         // 공격 적중 여부
	bool IsCritical;    // 치명타 발생 여부
	bool IsStun;        // 몬스터 스턴 발생 여부
};

// 배틀 시스템
//
// 역할:
// GameConText에 저장된 Player와Monster를 이용해 전투를 진행합니다.
// 플레이어 입력, 턴 진행, 피해 계산, 주사위 판정을 관리합니다.
// Player, Monster, Inventory 객체를 직접 생성하지 않습니다.

// 전투 진행을 담당하는 클래스입니다.
//
// 담당 범위:
// - 플레이어 행동 입력
// - 플레이어와 몬스터의 공격 처리
// - 주사위 판정
// - 방어, 스턴, 도망 처리
// - 전투 종료 판정

class Battle
{
public:
	Battle();

	// 전투를 시작하고 종료 결과를 반환합니다.
	//
	// 반환값:
	// BattleResult::Victory - 플레이어 승리
	// BattleResult::Defeat  - 플레이어 패배
	// BattleResult::Escape  - 도망 성공
	StartBattle(GameContext& context);

	// 전투에서 사용할 주사위 종류를 설정합니다.
	void SetDiceType(DiceType diceType);

	// 현재 설정된 주사위 종류를 반환합니다.
	DiceType GetdiceType() const;

	// 현재 전투 결과를 반환합니다.
	GetBattleResult() const;

private:
	// 새로운 전투를 시작할 수 있도록 내부 상태를 초기화합니다.
	void InitializeBattle();

	// 플레이어 턴과 몬스터 턴으로 구성한 한 턴을 처리합니다.
	//
	// 전투가 끝나지 않았다면 BattleResult::None을 반환합니다.
	ProcessTurn(GameContext& context);

	// 플레이어에게 행동을 입력받아 선택된 행동을 반환합니다.
	//
	// 실제 공격이나 방어 처리는 이 함수에서 하지 않고,
	// 선택 결과만 반환하여 입력과 전투 처리를 분리합니다.
	SelectPlayerAction();

	// 플레이어 공격을 처리하고 공격 결과를 반환합니다.
	AttackResult ProcessPlayerAttack(GameContext& context);

	// 플레이어를 방어 상태로 변경합니다.
	void ProcessPlayerDefense();

	// 몬스터 턴을 처리하고 플레이어가 받은 피해량을 반환합니다.
	//
	// 몬스터가 스턴 상태라면 0을 반환합니다.
	int ProcessMonsterTurn(GameContext& context);

	// 플레이어의 공격 결과를 계산합니다.
	AttackResult CalculatePlayerAttack(GameContext& context);

	// 몬스터가 플레이어에게 줄 최종 피해량을 계산합니다.
	int CalculateMonsterDamage(GameContext& context);

	// 몬스터에게 피해를 적용하고 남은 HP를 반환합니다.
	int ApplyDamageToMonster(GameContext& context, int Damage);

	// 플레이어에게 피해를 적용하고 남은 HP를 반환합니다.
	int ApplyDamageToPlayer(GameContext& context, int Damage);

	// 도망 성공 여부를 반환합니다.
	bool IsEscapeSuccessful();

	// 플레이어가 쓰려졌는지 반환합니다.
	bool IsPlayerDefeated(GameContext& context) const;

	// 몬스터가 쓰려졌는지 반환합니다.
	bool IsMonsterDefeated(GameContext& context) const;

private:
	int TrunCount;  // 현재 턴 번호
	int LastDiceValue;  // 가장 최근에 나온 주사위 값

	bool IsPlayerDefending;   // 플레이어 방어 상태
	bool IsMonsterStunned;    // 몬스터 스턴 상태

	DiceType CurrentDiceType;   // 현재 사용하는 주사위 종류
	BattleResult BattleResult;   // 현재 전투 결과

};

#endif

// 다이스 숫자별 데미지 1 회피 2 빗맞음 3~4 일반뎀 5 치뎀 6 치뎀+스턴(33%)?
// 다이스 
// 럭키다이스  나온값에+1
// 더블다이스 두번던지고 그중에 높은숫자적용
// 익스트림다이스 1또는6만 나오는 주사위
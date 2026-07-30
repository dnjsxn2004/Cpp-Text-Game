#ifndef BATTLE_H_
#define BATTLE_H_
#include <iostream>

class GameContext;
class Player;
class Monster;

enum class DiceType
{
	Normal,  // 일반 주사위: 1부터 6까지 동일한 확률도 등장
	//Lucky,   // 럭키 다이스: 주사위 결과에 1을 더하며 최대값은 6
	//Double,  // 더블 다이스: 두번 굴린 후 더 높은 값을 사용
	//extreme,  //
};

class Battle
{
public:
	Battle(GameContext& context) {  

	}

	bool StartBattle();             // 전투 전체를 시작하고 반복하는 멤버함수
	int ProcessTurn();             // 한턴을 진행하는 멤버함수
	int PlayerTurn();              // 플레이어 행동처리하는 멤버함수
	int MonsterTurn();             // 몬스터 행동처리하는 멤버함수

	bool StartBattle(GameContext& context);
	


	void SetDiceValue(int Dice) { this->DiceValue = Dice; }

	int GetDiceValue() { return DiceValue; }
private:
	int TrunCount;  // 턴의 값을 나타내는 멤버변수
	int DiceValue;  // 주사위 값을 나타내는 멤버변수

	bool IsBattleOver;        //전투종료여부
	bool IsPlayerDefending;   // 플레이어가 현재 방어 상태인지 확인
	bool IsMonsterStunned;    // 몬스터스턴상태 여부


};

#endif

// 다이스 숫자별 데미지 1 회피 2 빗맞음 3~4 일반뎀 5 치뎀 6 치뎀+스턴?
// 다이스 
// 럭키다이스  나온값에+1
// 더블다이스 두번던지고 그중에 높은숫자적용
// 겜블러다이스 1또는6만 나오는 주사위
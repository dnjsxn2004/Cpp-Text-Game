#ifndef BATTLE_H_
#define BATTLE_H_

class Player;
class Monster;

class Battle
{
public:
	Battle(Player* player, Monster* monster)

	void StartBattle();             // 전투 전체를 시작하고 반복하는 멤버함수
	void ProcessTurn();             // 한턴을 진행하는 멤버함수
	void PlayerTurn();              // 플레이어 행동처리하는 멤버함수
	void MonsterTurn();             // 몬스터 행동처리하는 멤버함수
	


	void SetDiceValue(int Dice) { this->DiceValue = Dice; }

	int GetDiceValue() { return DiceValue; }
private:
	Player* player;
	Monster* monster;

	int TrunCount;  // 턴의 값을 나타내는 멤버변수
	int DiceValue;  // 주사위 값을 나타내는 멤버변수

};

#endif

// 다이스 숫자별 데미지 1 회피 2 빗맞음 3~4 일반뎀 5 치뎀 6 치뎀+스턴?
// 다이스 
// 럭키다이스  나온값에+1
// 더블다이스 두번던지고 그중에 높은숫자적용
// 겜블러다이스 1또는6만 나오는 주사위
#pragma once
#include <string>

//아이템타입 클래스
enum class ItemType {
	Consumable, //소비 아이템
	Equipment, //장비 아이템
	Quest //퀘스트 아이템
};

//아이템 클래스
class Item {
private:
	std::string name; //이름

	ItemType type; //타입

	int hpRecovery;//hp회복
	
	int mpRecovery;//mp회복

	int attackBonus;//공격 보너스

	int defenceBonus;//방어 보너스

	int quantity; // 아이템 수량

//아이템 생성자
public:
	Item(const std::string& name, ItemType type, int hpRecovery = 0, int mpRecovery = 0, int attackBonus = 0, int defenceBonus = 0, int quantity = 1);

	std::string GetName() const;
	ItemType GetType() const;

	int GetHpRecovery() const;
	int GetMpRecovery() const;

	int GetAttackBonus() const;
	int GetDefenceBonus() const;

	//아이템 수량 반환
	int GetQuantity() const;

	//아이템 수량 변경
	void SetQuantity(int quantity);

};


#pragma once
#include <string>

//아이템타입 클래스
enum class ItemType {
	Consumalbe, //소비 아이템
	Equipment, //장비 아이템
	Quest //퀘스트 아이템
};

//아이템 클래스
class Item {
private:
	std::string name; //이름
	ItemType type; //타입
	int effectAmount; //효과량

//생성자
public:
	Item(const std::string& name, ItemType type, int effectAmount);

	std::string GetName() const;
	ItemType GetType() const;
	int GetEffectAmount() const;

};
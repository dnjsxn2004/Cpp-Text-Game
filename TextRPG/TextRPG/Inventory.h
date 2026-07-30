#pragma once

#include <vector>
#include "Item.h"

class GameContext;
//인벤토리 클래스
class Inventory {
private:
	//인벤토리에 들어있는 아이템 목록
	std::vector<Item> items;

	//현재 장착한 무기 인덱스
	int equippedWeaponIndex;

	//현재 장착한 방어구 인덱스
	int equippedArmorIndex;

public:
	//장착 인덱스를 -1로 초기화
	Inventory();

	//인벤토리에 아이템 추가
	void AddItem(const Item& item);
	
	//인벤토리에 저장된 전체 아이템 목록을 반환
	const std::vector<Item>& GetItems() const;

	//특정 타입의 아이템 목록을 반환
	std::vector<Item> GetItemsByType(ItemType type) const;

	//소비아이템 사용
	bool UseItem(int index, GameContext& context);

	//장비 장착
	bool EquipItem(int index, GameContext& context);

	//무기 해제
	bool UnequipWeapon(GameContext& context);

	//방어구 해제
	bool UnequipArmor(GameContext& context);

	int GetEquippedWeaponIndex() const;
	int GetEquippedArmorIndex() const;

	bool RemoveItem(int index, int quantity = 1);

	bool BuyItem(const Item& item, int quantity, GameContext& context);
};
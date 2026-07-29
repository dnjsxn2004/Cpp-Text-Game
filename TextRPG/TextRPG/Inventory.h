#pragma once

#include <vector>
#include "Item.h"
#include "Player.h"

class GameContext;
//인벤토리 클래스
class Inventory {
private:
	//인벤토리에 들어있는 아이템 목록
	std::vector<Item> items;

public:
	//인벤토리에 아이템 추가
	void AddItem(const Item& item);
	
	//인벤토리에 저장된 전체 아이템 목록을 반환
	const std::vector<Item>& GetItems() const;

	//특정 타입의 아이템 목록을 반환
	std::vector<Item> GetItemsByType(ItemType type) const;

	//아이템 사용
	bool UseItem(int index, GameContext& context);
};
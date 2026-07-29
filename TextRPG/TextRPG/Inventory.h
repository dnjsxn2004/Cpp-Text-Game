#pragma once
#include <vector>
#include "Item.h"

//인벤토리 클래스
class Inventory {
private:
	//인벤토리에 들어있는 아이템 목록
	std::vector<Item> items;

public:
	//인벤토리에 아이템 추가
	void AddItem(const Item& item);
	
	//현재 인벤토리에 있는 아이템 목록 출력
	void PrintInventory() const;
};
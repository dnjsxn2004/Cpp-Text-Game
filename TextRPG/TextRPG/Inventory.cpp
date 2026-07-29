#include "Inventory.h"
#include <vector>
using namespace std;

//인벤토리에 아이템을 추가
void Inventory::AddItem(const Item& item) {
	
	//같은 이름의 아이템이 있는지 확인
	for (Item& inventoryItem : items) {
		if (inventoryItem.GetName() == item.GetName()) {
			
			//같은 아이템이면 수량만 증가
			inventoryItem.SetQuantity(
				inventoryItem.GetQuantity() + item.GetQuantity()
			);
			return;
		}
	}
	
	items.push_back(item);
}

//인벤토리에 저장된 모든 아이템 목록을 반환
const std::vector<Item>& Inventory::GetItems() const {
	return items;
}

//지정한 타입의 아이템만 반환
std::vector<Item> Inventory::GetItemsByType(ItemType type) const {

	std::vector<Item> result;

	for (const Item& item : items) {
		if (item.GetType() == type) {
			result.push_back(item);
		}
	}
	return result;
}
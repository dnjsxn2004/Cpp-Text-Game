#include "Inventory.h"

using namespace std;

//인벤토리에 아이템을 추가
void Inventory::AddItem(const Item& item) {
	items.push_back(item);
}


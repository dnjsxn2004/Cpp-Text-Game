#include "Inventory.h"
#include "GameContext.h"

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
	//같은 아이템이 없으면 새로 추가
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

bool Inventory::UseItem(int index, GameContext& context) {
	
	//잘못된 번호를 선택했는지 확인
	if (index < 0 || index >= static_cast<int>(items.size())) {
		return false;
	}
	
	Item& item = items[index];

	//아이템 수량이 없는 경우
	if (item.GetQuantity() <= 0) {
		return false;
	}

	//소비 아이템이 아닌 경우
	if (item.GetType() != ItemType::Consumable) {
		return false;
	}

	Player& player = context.GetPlayer();

	bool itemUsed = false;

	//HP 회복
	if (item.GetHpRecovery() > 0) {
		int newHp = player.GetHp() + item.GetHpRecovery();

		//최대 HP를 넘지 않도록 제한
		if (newHp > player.GetMaxHp()) {
			newHp = player.GetMaxHp();
		}

		player.SetHp(newHp);
		itemUsed = true;
	}

	//HP와 MP회복량이 모두 0이면 사용할 수 없는 아이템
	if (!itemUsed) {
		return false;
	}

	//아이템 사용에 성공한 경우에만 수량 감소
	item.SetQuantity(item.GetQuantity() - 1);
	
	return true;
}

Inventory::Inventory()
	: equippedWeaponIndex(-1),
	  equippedArmorIndex(-1) {

}

//장비 장착 함수
bool Inventory::EquipItem(int index, GameContext& context) {

	//잘못된 인덱스인지 확인
	if (index < 0 || index >= static_cast<int>(items.size())) {
		return false;
	}

	//인덱스로 아이템 접근
	Item& newItem = items[index];

	//장비 아이템이 아니면 장착할 수 없음
	if (newItem.GetType() != ItemType::Equipment) {
		return false;
	}
	
	//이미 장착한 아이템이면 다시 장착하지 않음
	if (newItem.IsEquipped()) {
		return false;
	}

	Player& player = context.GetPlayer();

	//무기 장착
	if (newItem.getEquipmentType() == EquipmentType::Weapon) {

		//기존에 장착한 무기가 있으면 해제
		if (equippedWeaponIndex != -1) {
			Item& oldWeapon = items[equippedWeaponIndex];

			//기존 무기의 공격력 증가분 제거
			player.SetAtt(
				player.GetAtt() - oldWeapon.GetAttackBonus()
			);

			oldWeapon.SetEquipped(false);
		}

		//새 무기의 공격력 적용
		player.SetAtt(
			player.GetAtt() + newItem.GetAttackBonus()
		);

		newItem.SetEquipped(true);
		equippedWeaponIndex = index;

		return true;
	}


}
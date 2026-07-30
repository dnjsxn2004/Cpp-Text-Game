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

bool Inventory::UseItem(int index, GameContext& context)
{
	// 잘못된 번호를 선택했는지 검사
	if (index < 0 ||
		index >= static_cast<int>(items.size()))
	{
		return false;
	}

	Item& item = items[index];

	// 소비 아이템인지 검사
	if (item.GetType() != ItemType::Consumable)
	{
		return false;
	}

	// 수량이 있는지 검사
	if (item.GetQuantity() <= 0)
	{
		return false;
	}

	const StatBonus& bonus = item.GetStatBonus();

	// HP와 MP 효과가 모두 없으면 사용할 수 없음
	if (bonus.hp == 0 && bonus.mp == 0)
	{
		return false;
	}

	// GameContext에서 Player 가져오기
	Player& player = context.GetPlayer();

	// 실제 HP/MP 효과는 Player에서 적용
	player.DrinkPotion(item.GetStatBonus());

	// 수량 1 감소
	item.SetQuantity(item.GetQuantity() - 1);

	// 수량이 0이 되면 인벤토리에서 삭제
	if (item.GetQuantity() <= 0)
	{
		items.erase(items.begin() + index);

		// 삭제된 위치보다 뒤에 있는 장비 인덱스 조정
		if (equippedWeaponIndex > index)
		{
			equippedWeaponIndex--;
		}

		if (equippedArmorIndex > index)
		{
			equippedArmorIndex--;
		}
	}

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

	EquipmentType equipmentType = selectedItem.GetEquipmentType();

	//무기 장착
	if (equipmentType == EquipmentType::Weapon) {
		//기존 무기가 있으면 장착 상태 해제
		if (equippedWeaponIndex != -1) {
			items[equippedWeaponIndex].SetEquipped(false);
		}
		equippedWeaponIndex = index;
		selectedItem.SetEquipped(true);
	}
	//방어구 장착
	else if (equipmentType == EquipmentType::Armor) {
		//기존 방어구가 있으면 장착 상태 해제
		if (equippedArmorIndex != -1) {
			items[equippedArmorIndex].SetEquipped(false);
		}

		equippedArmorIndex = index;
		selecetItem.SetEquipped(true);
	}
	else {
		return false;
	}

	Player& player = context.GetPlayer();

	//정착 중인 장비 전체 보너스 계산
	StatBonus totalBonus;

	if (equippedWeaponIndex != -1) {
		const StatBonus& weaponBonus = items[equippedWeaponIndex].GetStatBonus();

		totalBonus.hp += weaponBonus.hp;
		totalBonus.mp += weaponBonus.mp;
		totalBonus.str += weaponBonus.str;
		totalBonus.att += weaponBonus.att;
		totalBonus.def += weaponBonus.def;
		totalBonus.dex += weaponBonus.dex;
		totalBonus.intel += weaponBonus.intel;
		totalBonus.luk += weaponBonus.luk;
	}
	if (equippedArmorIndex != -1) {
		const StatBonus& armorBonus = items[equippedArmorIndex].GetStatBonus();

		totalBonus.hp += armorBonus.hp;
		totalBonus.mp += armorBonus.mp;
		totalBonus.str += armorBonus.str;
		totalBonus.att += armorBonus.att;
		totalBonus.def += armorBonus.def;
		totalBonus.dex += armorBonus.dex;
		totalBonus.intel += armorBonus.intel;
		totalBonus.luk += armorBonus.luk;
	}

	//Player가 기존 장비 보너스를 새 보너스로 교체
	player.ApplyEquipBonus(true, totalBonus);

	return true;
}

//무기 해제
bool Inventory::UnequipWeapon(GameContext& context) {
	//장착된 무기가 없음
	if (equippedWeaponIndex == -1) {
		return false;
	}

	item[equippedWeaponIndex].SetEquipped(false);
	equippedWeaponIndex = -1;

	Player& player = context.GetPlayer();

	StatBonus totalBonus;

	// 방어구가 남아 있다면 방어구 보너스만 적용
	if (equippedArmorIndex != -1) {
		totalBonus = items[equippedArmorIndex].GetStatBonus();
	}

	player.ApplyEquipBonus(true, totalBonus);

	return true;
}
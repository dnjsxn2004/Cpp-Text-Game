#include "Inventory.h"
#include "GameContext.h"

Inventory::Inventory()
	: equippedWeaponIndex(-1),
	  equippedArmorIndex(-1) {

}


//인벤토리에 아이템을 추가
void Inventory::AddItem(const Item& item) {
	
	// 소비 아이템만 수량 합치기
	if (item.GetType() == ItemType::Consumable) {

		//같은 이름의 아이템이 있는지 확인
		for (Item& inventoryItem : items) {
			if (inventoryItem.GetType() == ItemType::Consumable && inventoryItem.GetName() == item.GetName()) {

				//같은 아이템이면 수량만 증가
				inventoryItem.SetQuantity(
					inventoryItem.GetQuantity() + item.GetQuantity()
				);
				return;
			}
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
	if (bonus.hp == 0 && bonus.mp == 0 && bonus.str ==0 && bonus.att ==0 &&
		bonus.def == 0 && bonus.dex == 0 &&  bonus.intel == 0 && bonus.luk ==0)
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

	EquipmentType equipmentType = newItem.GetEquipmentType();
	Player& player = context.GetPlayer();

	//무기 장착
	if (equipmentType == EquipmentType::Weapon) {
		//기존 무기가 있으면 장착 상태 해제
		if (equippedWeaponIndex != -1) {
			const StatBonus oldBonus = items[equippedWeaponIndex].GetStatBonus();
			
			player.ApplyEquipHpMpBonus(false, oldBonus);
			items[equippedWeaponIndex].SetEquipped(false);
		}
		equippedWeaponIndex = index;
		newItem.SetEquipped(true);

		//새 무기의 HP/MP 보너스 적용
		player.ApplyEquipHpMpBonus(
			true,
			newItem.GetStatBonus()
		);
	}

	//방어구 장착
	else if (equipmentType == EquipmentType::Armor) {
		//기존 방어구가 있으면 장착 상태 해제
		if (equippedArmorIndex != -1) {
			const StatBonus oldBonus = items[equippedArmorIndex].GetStatBonus();

			player.ApplyEquipHpMpBonus(false, oldBonus);
			items[equippedArmorIndex].SetEquipped(false);
		}
		equippedArmorIndex = index;
		newItem.SetEquipped(true);

		//새 방어구의 HP/MP 보너스 적용
		player.ApplyEquipHpMpBonus(
			true,
			newItem.GetStatBonus()
		);
	}

	else {
		return false;
	}

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

	Player& player = context.GetPlayer();

	//해제할 무기의 보너스를 먼저 저장
	const StatBonus removedBonus = items[equippedWeaponIndex].GetStatBonus();

	//무기의 HP/MP 보너스 제거
	player.ApplyEquipHpMpBonus(false, removedBonus);

	//장착 상태 해제
	items[equippedWeaponIndex].SetEquipped(false);
	equippedWeaponIndex = -1;

	StatBonus totalBonus;

	// 방어구가 남아 있다면 방어구 보너스만 적용
	if (equippedArmorIndex != -1) {
		totalBonus = items[equippedArmorIndex].GetStatBonus();

		player.ApplyEquipBonus(true, totalBonus);
	}
	else {
		//남은 장비가 없음
		player.ApplyEquipBonus(false, StatBonus());
	}

	return true;
}

//방어구 해제
bool Inventory::UnequipArmor(GameContext& context) {
	//장착된 방어구가 없음
	if (equippedArmorIndex == -1) {
		return false;
	}

	Player& player = context.GetPlayer();

	//해제할 방어구의 보너스를 먼저 저장
	const StatBonus removedBonus = items[equippedArmorIndex].GetStatBonus();

	//방어구의 HP/MP 보너스 제거
	player.ApplyEquipHpMpBonus(false, removedBonus);

	//장착 상태 해제
	items[equippedArmorIndex].SetEquipped(false);
	equippedArmorIndex = -1;

	StatBonus totalBonus;

	// 무기가 남아 있다면 무기 보너스만 적용
	if (equippedWeaponIndex != -1) {
		totalBonus = items[equippedWeaponIndex].GetStatBonus();

		player.ApplyEquipBonus(true, totalBonus);
	}
	else {
		// 남은 장비가 없음
		player.ApplyEquipBonus(false, StatBonus());
	}
	return true;
}

//장착 인덱스 Getter
int Inventory::GetEquippedWeaponIndex() const {
	return equippedWeaponIndex;
}

int Inventory::GetEquippedArmorIndex() const {
	return equippedArmorIndex;
}

bool Inventory::RemoveItem(int index, int quantity) {

	//잘못된 인덱스 검사
	if (index < 0 || index >= static_cast<int>(items.size())) {
		return false;
	}

	//잘못된 삭제 수량 검사
	if (quantity <= 0) {
		return false;
	}

	Item& item = items[index];

	//정착 중인 아이템은 삭제 불가
	if (item.IsEquipped()) {
		return false;
	}

	//가지고 있는 수량보다 많이 삭제하려는 경우
	if (quantity > item.GetQuantity()) {
		return false;
	}

	item.SetQuantity(item.GetQuantity() - quantity);

	//수량이 0이면 벡터에서 완전히 삭제
	if (item.GetQuantity() <= 0) {
		items.erase(items.begin() + index);

		//삭제 위치 뒤에 있는 장비 인덱스 조정
		if (equippedWeaponIndex > index) {
			equippedWeaponIndex--;
		}

		if (equippedArmorIndex > index) {
			equippedArmorIndex--;
		}
	}
	return true;
}
#include "Item.h"

//Item 생성자
Item::Item(const std::string& name, ItemType type, EquipmentType equipmentType, const StatBonus& statBonus, int quantity)
	:name(name), type(type), equipmentType(equipmentType), quantity(quantity),statBonus(statBonus), equipped(false){

}

//아이템 이름 반환
std::string Item::GetName() const {
	return name;
}
//아이템 타입 반환
ItemType Item::GetType() const {
	return type;
}
EquipmentType Item::GetEquipmentType() const {
	return equipmentType;
}
//아이템 수량 반환
int Item::GetQuantity() const {
	return quantity;
}
//아이템 수량 변경
void Item::SetQuantity(int quantity) {
	quantity = newQuantity;
}

bool Item::IsEquipped() const {
	return equipped;
}

void Item::SetEquipped(bool equipped) {
	this->equipped = equipped;
}

const StatBonus& Item::GetStatBonus() const {
	return statBonus;
}
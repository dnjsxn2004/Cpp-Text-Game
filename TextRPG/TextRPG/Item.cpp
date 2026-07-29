#include "Item.h"

//Item 생성자
Item::Item(const std::string& name, ItemType type, int hpRecovery, int mpRecovery, int attackBonus, int defenceBonus, int quantity)
	:name(name), type(type), hpRecovery(hpRecovery), mpRecovery(mpRecovery), attackBonus(attackBonus), defenceBonus(defenceBonus), quantity(quantity) {

}

//아이템 이름 반환
std::string Item::GetName() const {
	return name;
}
//아이템 타입 반환
ItemType Item::GetType() const {
	return type;
}
//아이템 수량 반환
int Item::GetQuantity() const {
	return quantity;
}
//아이템 수량 변경
void Item::SetQuantity(int quantity) {
	quantity = newQuantity;
}

int Item::GetHpRecovery() const {
	return hpRecovery;
}

int Item::GetMpRecovery() const {
	return mpRecovery;
}

int Item::GetAttackBonus() const {
	return attackBonus;
}

int Item::GetDefenceBonus() const {
	return defenceBonus;
}
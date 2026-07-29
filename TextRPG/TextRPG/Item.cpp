#include "Item.h"

//Item 생성자
Item::Item(const std::string& name, ItemType type, int effectAmount,int quantity)
	:name(name), type(type), effectAmount(effectAmount), quantity(quantity) {

}

//아이템 이름 반환
std::string Item::GetName() const {
	return name;
}
//아이템 타입 반환
ItemType Item::GetType() const {
	return type;
}
//아이템 효과량 반환
int Item::GetEffectAmount() const {
	return effectAmount;
}
//아이템 수량 반환
int Item::GetQuantity() const {
	return quantity;
}
//아이템 수량 변경
void Item::SetQuantity(int quantity) {

}
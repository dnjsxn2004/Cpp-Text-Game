#include "Item.h"

//Item 클래스 생성자
Item::Item(const std::string& name, ItemType type, int effectAmount)
	:name(name), type(type), effectAmount(effectAmount) {

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
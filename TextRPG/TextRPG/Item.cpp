#include "Item.h"

//Item 클래스 생성자
Item::Item(const std::string& name, ItemType type, int effectAmount)
	:name(name), type(type), effectAmount(effectAmount) {

}

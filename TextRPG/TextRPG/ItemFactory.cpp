#include "ItemFactory.h"

Item ItemFactory::CreateCigarette(int quantity) {
	return Item(
		"담배",
		ItemType::Consumable,
		20, // HP 회복
		0,  // MP 회복
		0,  // 공격력 증가
		0,  // 방어력 증가
		quantity
		);
}
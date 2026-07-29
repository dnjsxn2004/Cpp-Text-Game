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

Item ItemFactory::CreateAlcohol(int quantity) {
	return Item(
		"술",
		ItemType::Consumable,
		0, // HP 회복
		20,  // MP 회복
		0,  // 공격력 증가
		0,  // 방어력 증가
		quantity
	);
}

Item ItemFactory::CreateDrug(int quantity) {
	return Item(
		"마약",
		ItemType::Consumable,
		40, // HP 회복
		0,  // MP 회복
		0,  // 공격력 증가
		0,  // 방어력 증가
		quantity
	);
}

Item ItemFactory::CreateWhiskey(int quantity) {
	return Item(
		"위스키",
		ItemType::Consumable,
		EquipmentType::None,
		0, // HP 회복
		40,  // MP 회복
		0,  // 공격력 증가
		0,  // 방어력 증가
		quantity
	);
}

Item ItemFactory::CreateSyringe(int quantity) {
	return Item(
		"주사기",
		ItemType::Consumable,
		EquipmentType::None,
		0, // HP 회복
		0,  // MP 회복
		10,  // 공격력 증가
		0,  // 방어력 증가
		quantity
	);
}

Item ItemFactory::CreateCannabis(int quantity) {
	return Item(
		"대마초",
		ItemType::Consumable,
		EquipmentType::None,
		40, // HP 회복
		0,  // MP 회복
		0,  // 공격력 증가
		10,  // 방어력 증가
		quantity
	);
}

//장비 아이템(무기)
Item ItemFactory::CreateKnife() {
	return Item(
		"나이프",
		ItemType::Equipment,
		EquipmentType::Weapon,
		0, // HP 회복
		0, // MP 회복
		25, // 공격력 증가
		0,  // 방어력 증가
		1
	);
}

Item ItemFactory::CreateBat() {
	return Item(
		"야구배트",
		ItemType::Equipment,
		EquipmentType::Weapon,
		0, // HP 회복
		0, // MP 회복
		15, // 공격력 증가
		0,  // 방어력 증가
		1
	);
}

Item ItemFactory::CreateKnuckle() {
	return Item(
		"너클",
		ItemType::Equipment,
		EquipmentType::Weapon,
		0, // HP 회복
		0, // MP 회복
		20, // 공격력 증가
		0,  // 방어력 증가
		1
	);
}

Item ItemFactory::CreateKatana() {
	return Item(
		"카타나",
		ItemType::Equipment,
		EquipmentType::Weapon,
		0, // HP 회복
		0, // MP 회복
		30, // 공격력 증가
		0,  // 방어력 증가
		1
	);
}

//장비 아이템(아머)
Item ItemFactory::CreateThomBrowne() {
	return Item(
		"톰 브라운",
		ItemType::Equipment,
		EquipmentType::Armor,
		0, // HP 회복
		0, // MP 회복
		0, // 공격력 증가
		20,  // 방어력 증가
		1
	);
}

Item ItemFactory::CreateGucci() {
	return Item(
		"구찌",
		ItemType::Equipment,
		EquipmentType::Armor,
		0, // HP 회복
		0, // MP 회복
		0, // 공격력 증가
		20,  // 방어력 증가
		1
	);
}

//퀘스트 아이템(효과 없음)
Item ItemFactory::CreateQuestkey() {
	return Item(
		"퀘스트 키",
		ItemType::Quest,
		EquipmentType::None,
		0, // HP 회복
		0, // MP 회복
		0, // 공격력 증가
		0,  // 방어력 증가
		1
	);
}
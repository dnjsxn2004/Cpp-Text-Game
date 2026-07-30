#include "ItemFactory.h"

Item ItemFactory::CreateCigarette(int quantity) {
	return Item(
		"담배",
		ItemType::Consumable,
		EquipmentType::None,
		StatBonus(
			10,// hp
			0, // mp
			0, // str
			0, // att
			0, // def
			0, // dex
			0, // intel
			0 // luk 
		),
		quantity
	);
}

Item ItemFactory::CreateAlcohol(int quantity) {
	return Item(
		"술",
		ItemType::Consumable,
		EquipmentType::None,
		StatBonus(
			0,// hp
			10, // mp
			0, // str
			0, // att
			0, // def
			0, // dex
			0, // intel
			0 // luk 
		),
		quantity
	);
}

Item ItemFactory::CreateDrug(int quantity) {
	return Item(
		"마약",
		ItemType::Consumable,
		EquipmentType::None,
		StatBonus(
			0,// hp
			0, // mp
			0, // str
			10, // att
		   -10, // def
			0, // dex
			0, // intel
			0 // luk 
		),
		quantity
	);
}

Item ItemFactory::CreateWhiskey(int quantity) {
	return Item(
		"위스키",
		ItemType::Consumable,
		EquipmentType::None,
		StatBonus(
			0,// hp
			20, // mp
			0, // str
			0, // att
			0, // def
			0, // dex
			0, // intel
			0 // luk 
		),
		quantity
	);
}

Item ItemFactory::CreateSyringe(int quantity) {
	return Item(
		"주사기",
		ItemType::Consumable,
		EquipmentType::None,
		StatBonus(
			10,// hp
			0, // mp
			0, // str
			15, // att
		   -15, // def
			0, // dex
			0, // intel
			0 // luk 
		),
		quantity
	);
}

Item ItemFactory::CreateCannabis(int quantity) {
	return Item(
		"대마초",
		ItemType::Consumable,
		EquipmentType::None,
		StatBonus(
			20,// hp
			0, // mp
			0, // str
			0, // att
			0, // def
			0, // dex
			0, // intel
			0 // luk 
		),
		quantity
	);
}

//장비 아이템(무기)
Item ItemFactory::CreateKnife() {
	return Item(
		"나이프",
		ItemType::Equipment,
		EquipmentType::Weapon,
		StatBonus(
			0,// hp
			0, // mp
			0, // str
			20, // att
			0, // def
			0, // dex
			0, // intel
			0 // luk 
		),
		1
	);
}

Item ItemFactory::CreateBat() {
	return Item(
		"야구배트",
		ItemType::Equipment,
		EquipmentType::Weapon,
		StatBonus(
			0,// hp
			0, // mp
			0, // str
			15, // att
			0, // def
			0, // dex
			0, // intel
			0 // luk 
		),
		1
	);
}

Item ItemFactory::CreateKnuckle() {
	return Item(
		"너클",
		ItemType::Equipment,
		EquipmentType::Weapon,
		StatBonus(
			0,// hp
			0, // mp
			0, // str
			10, // att
			0, // def
			0, // dex
			0, // intel
			0 // luk 
		),
		1
	);
}

Item ItemFactory::CreateKatana() {
	return Item(
		"카타나",
		ItemType::Equipment,
		EquipmentType::Weapon,
		StatBonus(
			0,// hp
			0, // mp
			0, // str
			30, // att
			0, // def
			0, // dex
			0, // intel
			0 // luk 
		),
		1
	);
}

//장비 아이템(아머)
Item ItemFactory::CreateThomBrowne() {
	return Item(
		"톰 브라운",
		ItemType::Equipment,
		EquipmentType::Armor,
		StatBonus(
			0,// hp
			0, // mp
			0, // str
			0, // att
			20, // def
			0, // dex
			0, // intel
			0 // luk 
		),
		1
	);
}

Item ItemFactory::CreateGucci() {
	return Item(
		"구찌",
		ItemType::Equipment,
		EquipmentType::Armor,
		StatBonus(
			0,// hp
			0, // mp
			0, // str
			0, // att
			20, // def
			0, // dex
			0, // intel
			0 // luk 
		),
		1
	);
}

//퀘스트 아이템(효과 없음)
Item ItemFactory::CreateQuestKey() {
	return Item(
		"퀘스트 키",
		ItemType::Quest,
		EquipmentType::None,
		StatBonus(),
		1
	);
}
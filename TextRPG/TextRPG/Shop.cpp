#include "Shop.h"
#include "GameContext.h"
#include "ItemFactory.h"
#include "Player.h"
#include "Inventory.h"
#include "ConsolUI.h"

Shop::Shop() {
	
	//소비 아이템
	products.push_back(ItemFactory::CreateCigarette());
	products.push_back(ItemFactory::CreateAlcohol());
	products.push_back(ItemFactory::CreateDrug());
	products.push_back(ItemFactory::CreateWhiskey());
	products.push_back(ItemFactory::CreateSyringe());
	products.push_back(ItemFactory::CreateCannabis());

	//무기
	products.push_back(ItemFactory::CreateKnife());
	products.push_back(ItemFactory::CreateBat());
	products.push_back(ItemFactory::CreateKnuckle());
	products.push_back(ItemFactory::CreateKatana());

	//아머
	products.push_back(ItemFactory::CreateThomBrowne());
	products.push_back(ItemFactory::CreateGucci());
}

void Shop::AddProduct(const Item& item) {
	products.push_back(item);
}

const std::vector<Item>& Shop::GetProducts() const {
	return products;
}

//아이템 하나가 선택한 상점 카테고리에 속하는지 확인
bool Shop::IsMatchingCategory(const Item& item, ShopCategory category) const {
	switch (category) {
	case ShopCategory::Consumable:
		return item.GetType() == ItemType::Consumable;

	case ShopCategory::Weapon:
		return item.GetType() == ItemType::Equipment && item.GetEquipmentType() == EquipmentType::Weapon;

	case ShopCategory::Armor:
		return item.GetType() == ItemType::Equipment && item.GetEquipmentType() == EquipmentType::Armor;
	}

	return false;
}

//함수를 이용해서 카테고리에 맞는 상품들만 모아서 반환
std::vector<Item> Shop::GetProductsByCategory(ShopCategory category) const {
	std::vector<Item>result;

	for (const Item& item : products) {
		if (IsMatchingCategory(item, category)) {
			result.push_back(item);
		}
	}
	return result;
}

bool Shop::BuyItem(int productIndex, int quantity, GameContext& context) {
	
	//잘못된 상품 인덱스 검사
	if (productIndex < 0 || productIndex >= static_cast<int>(products.size())) {
		ConsoleUI::PrintMessage("유효하지 않습니다.");
		return false;
	}

	// 잘못된 구매 수량 검사
	if (quantity <= 0) {
		ConsoleUI::PrintMessage("잘못된 입력입니다.");
		return false;
	}

	const Item& product = products[productIndex];

	//퀘스트 아이템은 구매할 수 없음
	if (product.GetType() == ItemType::Quest) {
		return false;
	}

	//장비는 한 번에 1개만 구매
	if (product.GetType() == ItemType::Equipment && quantity != 1) {
		ConsoleUI::PrintMessage("장비 아이템은 한개만 구매 가능합니다.");
		return false;
	}

	int totalPrice = product.GetPrice() * quantity;

	Player& player = context.GetPlayer();

	//돈 부족 또는 잘못된 금액이면 구매 실패
	if (player.GetGold() < totalPrice) {
		ConsoleUI::PrintMessage("돈이 부족합니다");
		return false;
	}

	//상점 상품을 복사해서 구매 수량 설정
	Item purchasedItem = product;
	purchasedItem.SetQuantity(quantity);
	purchasedItem.SetEquipped(false);

	//구매후 현재 소지금
	player.SetGold(player.GetGold() - totalPrice);

	//플레이어 인벤토리에 추가
	context.GetInventory().AddItem(purchasedItem);

	return true;
}

//구매 함수
bool Shop::BuyItemByCategory(ShopCategory category, int categoryIndex, int quantity, GameContext& context) {
	//인덱스 확인
	if (categoryIndex < 0) {
		return false;
	}

	//현재 카테고리 안에서 몇 번째 상품인지 세는 변수
	int currentCategoryIndex = 0;

	for (int productIndex = 0;
		productIndex < static_cast<int>(products.size()); productIndex++) {

		//products안의 실제 상품
		const Item& product = products[productIndex];

		//선택한 카테고리에 속하지 않는 상품이면 건너뜀
		if (!IsMatchingCategory(product, category)) {
			continue;
		}
		   
		//선택한 번호가 같으면 상품 구매
		if (currentCategoryIndex == categoryIndex) {

			return BuyItem(productIndex, quantity, context);
		}

		//같은 카테고리 상품을 하나 찾았으니 번호 증가
		currentCategoryIndex++;
	}

	return false;
}

//판매 가격 계산(구매 가격의 60%)
int Shop::GetSellPrice(const Item& item) const {
	return item.GetPrice() * 60 / 100;
}

//판매 함수
bool Shop::SellItem(int inventoryIndex, int quantity, GameContext& context) {
	Inventory& inventory = context.GetInventory();

	const std::vector<Item>& items = inventory.GetItems();

	//잘못된 인덱스
	if (inventoryIndex < 0 || inventoryIndex >= static_cast<int>(items.size())) {
		ConsoleUI::PrintMessage("잘못된 아이템입니다.");
		return false;
	}

	//잘못된 수량
	if (quantity <= 0) {
		ConsoleUI::PrintMessage("잘못된 수량입니다.");
		return false;
	}

	const Item& item = items[inventoryIndex];

	//퀘스트 아이템 판매 불가
	if (item.GetType() == ItemType::Quest) {
		ConsoleUI::PrintMessage("퀘스트 아이템은 판매할 수 없습니다.");
		return false;
	}

	//장착 중인 장비는 판매 불가
	if (item.IsEquipped()) {
		ConsoleUI::PrintMessage("장착 중인 장비는 판매할 수 없습니다.");
		return false;
	}

	//수량 부족
	if (quantity > item.GetQuantity()) {
		ConsoleUI::PrintMessage("수량이 부족합니다.");
		return false;
	}

	//장비는 1개만 판매 가능
	if (item.GetType() == ItemType::Equipment && quantity != 1) {
		ConsoleUI::PrintMessage("장비는 한 개씩만 판매 가능합니다.");
		return false;
	}

	//판매 금액 계산
	int sellGold = GetSellPrice(item) * quantity;

	//인벤토리에서 삭제
	if (!inventory.RemoveItem(inventoryIndex, quantity)) {
		return false;
	}

	//골드 지급
	Player& player = context.GetPlayer();

	player.SetGold(player.GetGold() + sellGold);

	ConsoleUI::PrintMessage("판매가 완료되었습니다.");

	return true;
}
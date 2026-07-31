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
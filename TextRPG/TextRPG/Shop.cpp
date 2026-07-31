#include "Shop.h"
#include "GameContext.h"
#include "ItemFactory.h"
#include "Player.h"
#include "Inventory.h"

Shop::Shop() {
	//상점 기본 상품 등록
	products.push_back(ItemFactory::CreateCigarette());
	products.push_back(ItemFactory::CreateAlcohol());
	products.push_back(ItemFactory::CreateDrug());
	products.push_back(ItemFactory::CreateWhiskey());
	products.push_back(ItemFactory::CreateSyringe());
	products.push_back(ItemFactory::CreateCannabis());

	products.push_back(ItemFactory::CreateKnife());
	products.push_back(ItemFactory::CreateBat());
	products.push_back(ItemFactory::CreateKnuckle());
	products.push_back(ItemFactory::CreateKatana());

	products.push_back(ItemFactory::CreateThomBrowne());
	products.push_back(ItemFactory::CreateGucci());
}

void Shop::AddProduct(const Item& item) {
	products.push_back(item);
}

const std::vector<Item>& Shop::GetProducts() const {
	return products;
}

bool Shop::BuyItem(int productIndex, int quantity, GameContext& context) {
	
	//잘못된 상품 번호 검사
	if (productIndex < 0 || productIndex >= static_cast<int>(products.size())) {
		return false;
	}

	// 잘못된 구매 수량 검사
	if (quantity <= 0) {
		return false;
	}

	const Item& product = products[productIndex];

	//퀘스트 아이템은 구매할 수 없음
	if (product.GetType() == ItemType::Quest) {
		return false;
	}

	//장비는 한 번에 1개만 구매
	if (product.GetType() == ItemType::Equipment && quantity != 1) {
		return false;
	}

	int totalPrice = product.GetPrice() * quantity;

	Player& player = context.GetPlayer();

	//돈 부족 또는 잘못된 금액이면 구매 실패
	if (player.GetGold() < totalPrice) {
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
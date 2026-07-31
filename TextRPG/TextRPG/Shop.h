#pragma once

#include <vector>
#include "Item.h"

class GameContext;

//상점 상품 카테고리
enum class ShopCategory {
	Consumable,//소비 아이템
	Weapon, // 무기
	Armor // 방어구
};

class Shop {
private:
	//상점에서 판매하는 상품 목록
	std::vector<Item> products;

	//상품이 해당 카테고리에 포함되는지 검사
	bool IsMatchingCategory(const Item& item, ShopCategory category) const;

public:
	Shop();

	//판매 상품 추가
	void AddProduct(const Item& item);

	//전체 상품 목록
	const std::vector<Item>& GetProducts() const;

	//카테고리별 상품 목록
	std::vector<Item> GetProductsByCategory(ShopCategory category) const;

	//전체 상품 번호로 구매
	bool BuyItem(int productIndex, int quantity, GameContext& context);

	//카테고리 안의 상품 번호로 구매
	bool BuyItemByCategory(ShopCategory category, int categoryInedex, int quantity, GameContext& context);
};

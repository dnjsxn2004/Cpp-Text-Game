#pragma once

#include <vector>
#include "Item.h"

class GameContext;

class Shop {
private:
	//상점에서 판매하는 상품 목록
	std::vector<Item> products;

public:
	Shop();

	//판매 상품 추가
	void AddProduct(const Item& item);

	//전체 상품 목록 반환
	const std::vector<Item>& GetProducts() const;

	//상품 구매
	bool BuyItem(
		int productIndex,
		int quantity,
		GameContext& context
	);
};

#pragma once

#include "Player.h"
#include "Monster.h"
#include "Inventory.h"
#include "Item.h"


class GameContext
{
public:
    GameContext();

    
    ~GameContext();

   
    GameContext(const GameContext&) = delete;
    GameContext& operator=(const GameContext&) = delete;

    // [게임 실행 / 종료 상태]
    bool IsGameRunning() const;
    void SetGameRunning(bool isRunning);

    bool IsGameOver() const;
    void SetGameOver(bool isGameOver);

    // [Player 접근]
    Player& GetPlayer();
    const Player& GetPlayer() const;


    void SetPlayer(Player* newPlayer);

  
    bool HasPlayer() const;

    // [Monster 접근]
    Monster& GetMonster();
    const Monster& GetMonster() const;

    void SetMonster(const Monster& newMonster);

    // [Inventory 접근]
    Inventory& GetInventory();
    const Inventory& GetInventory() const;

    // [Item 접근]
    Item& GetItem();
    const Item& GetItem() const;

private:
    bool isRunning;
    bool isGameOver;

  
    Player* player;

    Monster monster;
    Inventory inventory;
    Item item;
};

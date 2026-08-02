#include "GameContext.h"

#include <stdexcept>


GameContext::GameContext()
    : isRunning(true),
    isGameOver(false),
    player(nullptr),
    monster(),
    inventory(),
    item()
{
}


GameContext::~GameContext()
{
    delete player;
    player = nullptr;
}

bool GameContext::IsGameRunning() const
{
    return isRunning;
}

void GameContext::SetGameRunning(bool isRunning)
{
    this->isRunning = isRunning;
}

bool GameContext::IsGameOver() const
{
    return isGameOver;
}

void GameContext::SetGameOver(bool isGameOver)
{
    this->isGameOver = isGameOver;
}

Player& GameContext::GetPlayer()
{

    return *player;
}

const Player& GameContext::GetPlayer() const
{
    return *player;
}

void GameContext::SetPlayer(Player* newPlayer)
{
    
    if (player != newPlayer)
    {
        delete player;
        player = newPlayer;
    }
}

bool GameContext::HasPlayer() const
{
    return player != nullptr;
}

Monster& GameContext::GetMonster()
{
    return monster;
}

const Monster& GameContext::GetMonster() const
{
    return monster;
}

void GameContext::SetMonster(const Monster& newMonster)
{
    monster = newMonster;
}

Inventory& GameContext::GetInventory()
{
    return inventory;
}

const Inventory& GameContext::GetInventory() const
{
    return inventory;
}

Item& GameContext::GetItem()
{
    return item;
}

const Item& GameContext::GetItem() const
{
    return item;
}

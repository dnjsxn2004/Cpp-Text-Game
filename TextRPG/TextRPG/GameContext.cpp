#include "GameContext.h"

GameContext::GameContext()
    : isRunning(true),
    isGameOver(false),
    player(new Player()),
    monster(),
    inventory()
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

void GameContext::SetGameRunning(bool value)
{
    isRunning = value;
}

bool GameContext::IsGameOver() const
{
    return isGameOver;
}

void GameContext::SetGameOver(bool value)
{
    isGameOver = value;
}

Player& GameContext::GetPlayer()
{
    return *player;
}

const Player& GameContext::GetPlayer() const
{
    return *player;
}

Player* GameContext::GetPlayerPtr()
{
    return player;
}

const Player* GameContext::GetPlayerPtr() const
{
    return player;
}

void GameContext::SetPlayer(Player* newPlayer)
{
    if (newPlayer == nullptr)
    {
        return;
    }

    if (player != nullptr)
    {
        delete player;
    }

    player = newPlayer;
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

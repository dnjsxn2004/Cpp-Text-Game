#include "GameContext.h"

bool GameContext::IsGameRunning()
{
    return isRunning;
}

void GameContext::SetGameRunning(bool isRunning)
{
    this->isRunning = isRunning;
}

bool GameContext::IsGameOver()
{
    return isGameOver;
}

void GameContext::SetGameOver(bool isGameOver)
{
    this->isGameOver = isGameOver;
}

Player& GameContext::GetPlayer()
{
    return player;
}

Monster& GameContext::GetMonster()
{
    return monster;
}

Inventory& GameContext::GetInventory()
{
    return inventory;
}

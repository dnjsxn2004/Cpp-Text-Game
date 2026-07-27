#include "GameManager.h"
#include <iostream>

void GameManager::Run()
{
	Intialize();
	MainLoop();
	ExitGame();
}

void GameManager::
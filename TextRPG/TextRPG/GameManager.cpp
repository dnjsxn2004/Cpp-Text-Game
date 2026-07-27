#include "GameManager.h"
#include <iostream>

void GameManager::Run()
{
	Intialize();
	MainLoop();
	ExitGame();
}

// 게임시작 준비 (구현 필요 항목 Init, Character 생성, 초기값 설정 - Player 파트에서 초기 값 만들면 넣을것)
void GameManager::Intialize()
{

}

// MainMenu 루프 필요 ( 메인메뉴 - 전투, 인벤토리 등 분기별 루프 반복)
void GameManager::MainLoop()
{

}

// 게임 종료 로직 구현 필요 ( 종료 or 저장기능 구현 시 저장)
void GameManager::ExitGame()
{

}
#pragma once

class GameManager
{
public:
	void Run();

private:
	// 초기화 함수
	void Intialize();
	// 메인 루프 함수
	void MainLoop();
	// 게임 종료 함수
	void ExitGame();
};
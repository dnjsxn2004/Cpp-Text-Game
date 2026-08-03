#include "GameManager.h"
#include "Monster.h"
#include <ctime>
#include <cstdlib>
#include "ConsolUI.h"
#include "ScreenBuffer.h"
#include <locale>

int main()
{
    srand(static_cast<unsigned int>(time(nullptr)));

    system("mode con cols=280 lines=80");

    std::locale::global(std::locale(""));

    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    system("mode con cols=220 lines=60");

    HWND console = GetConsoleWindow();
    ShowWindow(console, SW_MAXIMIZE);

    GameManager gameManager;
    gameManager.Run();

    return 0;
}

// 함수 이름 규칙

// 1. 모든 함수의 이름은 파스칼 케이스를 기반으로 만든다.
// 2. bool 함수는 Is 로 시작한다.
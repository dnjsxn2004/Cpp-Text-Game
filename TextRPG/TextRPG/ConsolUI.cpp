#include <iostream>
#include <string>
#include "ConsolUI.h"

using namespace std;

static void PrintLine()
{
	cout << "===============================================================" << endl;
}

static void PrintTitle(const std::string& title)
{
	cout << "                      [ " << title << " ]                     " << endl;
}

static void PrintMessage(const std::string& message)
{
	cout << message << endl;
}

static void PrintMessageValue(const std::string& message, int value)
{
	cout << message << ": " << value << endl;
}

static void PrintError(const std::string& message)
{
	cout  << message << endl;
}

static void PrintSuccess(const std::string& message)
{
	cout  << message << endl;
}

static void PrintMainMenu()
{
	PrintLine();
	PrintTitle("메인 메뉴");
	PrintLine();
	cout << "1. 일반 전투" << endl;
	cout << "2. 상점" << endl;
	cout << "3. 메인 스토리" << endl;
	PrintLine();
}

static void PrintJobSelectMenu()
{
	PrintLine();
	PrintTitle("캐릭터 선택");
	PrintLine();
	cout << "1. 진태식 유도" << endl;
	cout << "2. 강사라 태권도" << endl;
	cout << "3. 류노스케 가라데" << endl;
	PrintLine();
}

static void PrintGameOver()
{
	PrintLine();
	PrintTitle("게임 패배");
	PrintLine();
	cout << "캐릭터가 사망했습니다." << endl;
	PrintLine();
}
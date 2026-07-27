#include "InputManager.h"

#include <iostream>
#include <limits>
#include <string>

// 숫자 1개만 입력 ex) int choice = InputManager::InputInt(3)
int InputManager::InputInt()
{
	int input;

	while (true)
	{
		std::cin >> input;

		if (!std::cin.fail())
		{
			std::cin.ignore();
			return input;
		}

		std::cin.clear();
		std::cin.ignore();

		std::cout << "숫자를 입력해주세요: ";
	}
}

// 안내문구 출력 숫자 입력받기 ex) int count = InputManager::InputMessageToIn("구매할 개수를 입력하세요") / 플레이어 입력값 3 -> 3숫자 반환
int InputManager::InputMessageToInt(const std::string& message)
{
	std::cout << message;

	return InputInt();
}

// 범위안의 숫자 입력 받기 ex) int choice = InputManager::InputInRange(0,5) -> 0~5 범위까지 입력 받음
int InputManager::InputInRange(int min, int max)
{
	int input;

	while (true)
	{
		input = InputInt();

		if (input >= min && input <= max)
		{
			return input;
		}

		std::cout << min << "부터" << max << " 사이의 숫자를 입력해주세요: ";
	}
}

// 메세지 출력 및 입력 값 범위 지정(메뉴선택 등 선택지에 사용) ex) int choice = InputManager::InputInMassegeToRange("메뉴선택", 0, 5)
int InputManager::InputInMassegeToRange(const std::string& message, int min, int max)
{
	std::cout << message;
	
	return InputInRange(min, max);
}

// 문자열 입력
std::string InputManager::InputLine()
{
	std::string input;
	std::getline(std::cin, input);

	return input;
}

// 문자열 출력
std::string InputManager::InputMessageToLine(const std::string& message)
{
	std::cout << message;

	return InputLine();
}

// 화면 정지
void InputManager::Wait()
{
	std::cout << std::endl;
	std::cout << "계속하려면 Enter를 누르세요....";
	std::cin.get();
}
#include "InputManager.h"

#include <iostream>
#include <limits>
#include <string>


// InputManager 사용 규칙

// 1. 팀원들은 cin을 직접 사용하지 말 것.
// 2. 모든 입력은 InputManager 함수를 통해 받을 것.
// 3. 메뉴 선택은 InputInMassegeToRange() 사용 권장.
// 4. 이름, 검색어 입력은 InputMessageToLine() 사용.
// 5. 결과 확인 후 대기는 Wait() 사용.



// 숫자 하나를 입력받습니다.
// 사용 예시:
// int number = InputManager::InputInt();
// 입력: 3
// 반환: 3
int InputManager::InputInt()
{
	int input;

	while (true)
	{
		std::cin >> input;

		if (!std::cin.fail())
		{
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			return input;
		}

		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		std::cout << "숫자를 입력해주세요: ";
	}
}

// 안내 문구를 출력한 뒤 숫자 하나를 입력받습니다.
// 사용 예시:
// int count = InputManager::InputMessageToInt("구매할 개수를 입력하세요: ");
// 입력: 3
// 반환: 3
int InputManager::InputMessageToInt(const std::string& message)
{
	std::cout << message;

	return InputInt();
}


// 지정한 범위 안의 숫자만 입력받습니다.
// 사용 예시:
// int choice = InputManager::InputInRange(0, 5);
// 입력 가능 범위: 0 ~ 5
// 반환: 0부터 5 사이의 숫자
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

		std::cout << min << "부터 " << max << " 사이의 숫자를 입력해주세요: ";
	}
}


// 안내 문구를 출력한 뒤 지정한 범위 안의 숫자를 입력받습니다.
// 메뉴 선택에 가장 많이 사용합니다.
// 사용 예시:
// int choice = InputManager::InputInMassegeToRange("메뉴 선택: ", 0, 5);
// 입력 가능 범위: 0 ~ 5
// 반환: 선택한 메뉴 번호
int InputManager::InputInMassegeToRange(const std::string& message, int min, int max)
{
	std::cout << message;

	return InputInRange(min, max);
}


// 문자열 한 줄을 입력받습니다.
// 사용 예시:
// std::string name = InputManager::InputLine();
// 입력: 홍길동
// 반환: "홍길동"
std::string InputManager::InputLine()
{
	std::string input;
	std::getline(std::cin, input);

	return input;
}


// 안내 문구를 출력한 뒤 문자열 한 줄을 입력받습니다.
// 이름, 검색어, 아이템명 입력에 사용합니다.
// 사용 예시:
// std::string name = InputManager::InputMessageToLine("이름을 입력하세요: ");
// 입력: 홍길동
// 반환: "홍길동"
std::string InputManager::InputMessageToLine(const std::string& message)
{
	std::cout << message;

	return InputLine();
}


// 사용자가 Enter를 누를 때까지 화면을 멈춥니다.
// 결과 확인 후 대기할 때 사용합니다.
// 사용 예시:
// InputManager::Wait();
void InputManager::Wait()
{
	std::cout << std::endl;
	std::cout << "계속하려면 Enter를 누르세요....";
	std::cin.get();
}

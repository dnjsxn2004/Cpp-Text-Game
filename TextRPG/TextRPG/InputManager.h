#ifndef INPUTMANAGER_H_
#define INPUTMANAGER_H_

#include <string>

class InputManager
{
public:

	// 숫자 1개만 입력 ex) int choice = InputManager::InputInt(3)
	int InputInt();

	// 안내문구 출력 숫자 입력받기 ex) int count = InputManager::InputMessageToIn("구매할 개수를 입력하세요") / 플레이어 입력값 3 -> 3숫자 반환
	int InputMessageToInt(const std::string& message);

	// 범위안의 숫자 입력 받기 ex) int choice = InputManager::InputInRange(0,5) -> 0~5 범위까지 입력 받음
	int InputInRange(int min, int max);

	// 메세지 출력 및 입력 값 범위 지정(메뉴선택 등 선택지에 사용) ex) int choice = InputManager::InputInMassegeToRange("메뉴선택", 0, 5)
	int InputInMassegeToRange(const std::string& message, int min, int max);

	// 문자열 입력
	std::string InputLine();

	// 문자열 출력 ex) std::string name = InputManager::InputLine("플레이어 이름을 입력하세요: ");
	std::string InputMessageToLine(const std::string& message);

	// 화면 정지
	void Wait();

};



#endif // !INPUTMANAGER_H_

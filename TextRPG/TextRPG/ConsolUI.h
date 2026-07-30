// ConsoleUI 구현 규칙
// 1. ConsoleUI는 출력만 담당합니다.
// 2. ConsoleUI 안에서 입력을 받지 않습니다.
//    cin 사용 금지.
// 3. ConsoleUI 안에서 게임 로직을 처리하지 않습니다.
//    예: 골드 차감, 아이템 추가, 전투 계산 금지.
// 4. 메뉴 번호는 변경 가능하나 각 파트를 맡은 팀원과 미리 상담 부탁드립니다.
// 5. 각 팀원들에게 출력 함수 이름 혼동을 주지 않기 위해 아래의 함수 이름과 각 역할 만 지정해 두었습니다.
//	  함수 추가 시 아래의 규칙을 따라 주시길 바랍니다.	
// 6. 시스템 담당자는 메뉴 출력 시 이 함수를 호출해서 사용합니다.
// 
// 사용 예시:
// ConsoleUI::PrintMainMenu();
// ConsoleUI::PrintError("잘못된 입력입니다.");
// ConsoleUI::PrintSuccess("구매가 완료되었습니다.");

//ConsoleUI 함수 이름 생성 규칙
//1. 메뉴 출력은 ConsoleUI::PrintOOOMenu() 형식으로 만든다.
//2. 단순 메시지는 ConsoleUI::PrintMessage()를 사용한다.
//3. 오류 메시지는 ConsoleUI::PrintError()를 사용한다.
//4. 성공 메시지는 ConsoleUI::PrintSuccess()를 사용한다.
///

#pragma once

#include <iostream>
#include <string>
#include <windows.h> // Windows API 헤더 추가

class ConsoleUI
{
public:
    // 구분선 출력 함수
    static void PrintLine();

    // 타이틀 출력 함수
    // 예: ConsoleUI::PrintTitle("상점");
    static void PrintTitle(const std::string& title);

    // 안내 메세지 함수 (*한줄짜리 문자열)
    // 예: ConsoleUI::PrintMessage("상점에 입장했습니다.");
    static void PrintMessage(const std::string& message);

    // 문자열 + 숫자 함수
    // 예: ConsoleUi::PrintMessage("플레이어 hp",플레이어 현재 체력-GetHp 등등)
    static void PrintMessageValue(const std::string& message, int value);

    // 오류 메시지 함수
    // 예: ConsoleUI::PrintError("골드가 부족합니다.");
    static void PrintError(const std::string& message);

    // 성공 메시지 함수
    // 예: ConsoleUI::PrintSuccess("아이템 구매에 성공했습니다.");
    static void PrintSuccess(const std::string& message);

    // 메인 메뉴 함수
    // 항목: 전투 / 상점 / 인벤토리 / 포션 제작 / 훈련장 / 상태 보기 / 게임 종료
    static void PrintMainMenu();

    // 직업 선택 메뉴 함수
    // 항목: 전사 / 궁수 / 마법사 / 도적
    static void PrintJobSelectMenu();

    // 게임종료 메세지 출력 함수
    static void PrintGameOver();

    //PrintStartScreen() 함수 안에서 사용
    // 콘솔 화면 전체를 공백으로 덮어서 지우고,
    // 커서 위치를 화면의 맨 왼쪽 위(0, 0)로 되돌리는 함수
    static void ClearScreen();

    //PrintStartScreen() 함수 안에서 사용
    // 콘솔 커서를 원하는 좌표(x, y)로 이동시키는 함수
    static void MoveCursor(int x, int y);

    // 시작 화면 출력 함수
    // 게임 로고, 타이틀, 시작 안내 문구 출력
    // 예: ConsoleUI::PrintStartScreen();
    static void PrintStartScreen();


    // 진태식 캐릭터 흑색 이미지 출력 함수
    static void PrintJinBlackImage();

    // 진태식 캐릭터 백색 이미지 출력 함수
    static void PrintJinWhiteImage();


    // 강사라 캐릭터 흑색 이미지 출력 함수
    static void PrintKangBlackImage();

    // 강사라 캐릭터 백색 이미지 출력 함수
    static void PrintKangWhiteImage();


    // 류노스케 캐릭터 흑색 이미지 출력 함수
    static void PrintRyuBlackImage();

    // 류노스케 캐릭터 백색 이미지 출력 함수
    static void PrintRyuWhiteImage();


    // 진태식 캐릭터 로고(간단한 이미지, 픽토그래픽) 출력 함수
    static void PrintJinLogo();

    // 강사라 캐릭터 로고(간단한 이미지, 픽토그래픽) 출력 함수
    static void PrintKangLogo();

    // 류노스케 캐릭터 로고(간단한 이미지, 픽토그래픽) 출력 함수
    static void PrintRyuLogo();


    // 진태식 캐릭터 등장 장면과 소개 문구 출력 함수
    static void ShowJinIntro();

    // 강사라 캐릭터 등장 장면과 소개 문구 출력 함수
    static void ShowKangIntro();

    // 류노스케 캐릭터 등장 장면과 소개 문구 출력 함수
    static void ShowRyuIntro();


    // 캐릭터의 등장 장면과 소개 문구를 출력하는 함수
    static void ShowCharacterIntro();
    
    // Cut 1: 어린 시절 진태식, 강사라, 류노스케가 만나 즐겁게 노는 장면 출력 함수
    static void ShowCutScene1();

    // Cut 2: 불법 시술을 하는 의사 강사라의 장면 출력 함수
    static void ShowCutScene2();

    // Cut 3: 의사가 된 강사라 앞에서 진태식과 류노스케가 치료를 받으러 왔다가 마주치는 장면 출력 함수
    static void ShowCutScene3();

    // Cut 4: 류노스케와 진태식의 도박 승부가 본격적으로 진행되는 장면 출력 함수
    static void ShowCutScene4();

    // Cut 5: 도박판이 뒤집히고 류노스케와 진태식의 싸움이 클라이맥스로 치닫는 장면 출력 함수
    static void ShowCutScene5();

    // Cut 6: 진태식이 류노스케에게 패배하고 결정적인 위기에 빠지는 장면 출력 함수
    static void ShowCutScene6();

    // Cut 7: 진태식이 치명상을 입고 고통 속에서 버티는 장면 출력 함수
    static void ShowCutScene7();

    // CutScene 이미지 출력 함수
    static void PrintCutScene1Image();
    static void PrintCutScene2Image();
    static void PrintCutScene3Image();
    static void PrintCutScene4Image();
    static void PrintCutScene5Image();
    static void PrintCutScene6Image();
    static void PrintCutScene7Image();

    // Cut 5: 도박판이 뒤집히고 싸움이 클라이맥스로 치닫는 애니메이션 출력 함수
    static void PlayCutScene5Animation();

    // Cut 6: 진태식이 패배하고 위기에 빠지는 애니메이션 출력 함수
    static void PlayCutScene6Animation();
};
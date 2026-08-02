#pragma once

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

#include <iostream>
#include <string>
#include <vector>
#include <windows.h>

// [수정] 순환 include 방지를 위해 Battle.h는 여기서 include하지 않습니다.
// #include "Battle.h"

#include "Monster.h"
#include "Inventory.h"
#include "Item.h"
#include "GameContext.h"
#include "StatBonus.h"
#include "Player.h"

// [추가] 전방 선언
class Battle;
class GameContext;
class Item;

class ConsoleUI
{
public:
    // 오류떠서 추가 플레이서 스테이터스 & 버전
    static void PrintPlayerStatus(Player& player);

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



    // 메인 메뉴 출력 함수
    // 항목: 전투 / 상점 / 인벤토리 / 포션 제작 / 훈련장 / 상태 보기 / 게임 종료
    static void PrintMainMenu();

    // 메인 메뉴를 실행하고 사용자 선택에 따라 각 메뉴로 이동하는 함수
    static void SwitchMainMenu();



    // 현재 플레이어의 상태를 콘솔에 출력하는 함수
    // 게임 진행 중 맨 아래 캐릭터 정보를 확인할 때 사용
    // 레벨, 경험치, HP, MP
    static void PrintPlayerStatusEveryTime(GameContext& context);

    // 세부 상태창 출력 함수
    // 캐릭 이름, 골드, 레벨, 경험치, HP, MP, 공격력, 방어력
    // 내가 장착하고 있는 장비 아이템
    // 몬스터 처치수
    static void PrintStatus(GameContext& context, Battle& battle, StatBonus& equipBonus, StatBonus& potionBonus);



    // 아이템 타입을 출력 가능한 문자열로 변환 함수
    static std::string ItemTypeToString(const Item& item);

    // 아이템 목록을 번호와 함께 출력하는 함수
    // EX) 1. 아이템
    static void PrintItemListWithIndex(const std::vector<Item>& items);

    // 인벤토리 메뉴 출력 함수
    // 항목: 내가 가진 전체 아이템 보기 / 장비 아이템 / 소비 아이템 / 퀘스트 아이템 / 뒤로가기
    static void PrintInventoryMenu();

    // 아이템 1개의 정보를 화면에 출력 함수
    static void PrintItem(const Item& item);

    // 아이템 이름만 출력하는 함수
    static void PrintItemName(const Item& item);

    // 인벤토리에 저장된 모든 아이템 목록을 출력 함수
    static void PrintAllItems(GameContext& context);

    // 인벤토리에서 장비 타입 아이템만 조회하여 출력 함수
    static void PrintEquipmentItems(GameContext& context);

    // 인벤토리에서 소비 타입 아이템만 조회하여 출력 함수
    static void PrintConsumableItems(GameContext& context);

    // 인벤토리 메뉴를 실행하고 사용자 선택에 따라 아이템 목록을 출력 함수
    static void SwitchInventory(GameContext& context);



    // 상점 메뉴 출력 함수
    static void PrintShopMenu();

    // 상점 메뉴를 실행하고 사용자 선택에 따라 아이템 구매, 판매, 뒤로가기 기능을 수행하는 함수
    static void SwitchShopMenu();

    // 상점에 판매 중인 아이템 목록을 출력하는 함수
    static void PrintShopItems(const std::vector<Item>& shopItems);

    // 아이템 구매 성공 메시지를 출력하는 함수
    static void PrintPurchaseSuccess(const Item& item);

    // 아이템 구매 실패 메시지를 출력문은 Shop.h 에서 처리



    // 직업 선택 메뉴 함수
    // 항목: 진태식 / 류
    static void PrintJobSelectMenu();



    // 플레이어 정보 출력, 몬스터 정보 출력, 전투 메뉴 출력 함수
    static void PrintNormalBattleMenu(const GameContext& context);

    // 플레이어 정보 출력
    static void PrintBattlePlayerInfo(GameContext& context);

    // 몬스터 정보 출력
    static void PrintBattleMonsterInfo(GameContext& context);

    // 전투 중 플레이어가 선택할 수 있는 행동 메뉴를 출력합니다.
    static void PrintBattleActionMenu();

    // 전투 승리 보상 출력 함수
    static void BattleReward(GameContext& context);


    // 일반 주사위를 굴린 결과 메세지 출력 함수. (주사위 결과: 1~6)
    void PrintNormalDiceResult(int diceValue) const;

    // 플레이어의 일반 공격 결과 메세지 출력 함수
    void PrintPlayerMeleeAttackResult(
        const std::string& playerName,
        const std::string& monsterName,
        int diceNumber,
        int damage,
        bool isStunSuccess,
        Battle& battle,
        GameContext& player,
        GameContext& monster
    ) const;

    // 플레이어의 스킬 공격 결과를 메시지로 출력합니다.
    void PrintPlayerSkillAttackResult(
        const std::string& playerName,
        const std::string& monsterName,
        const std::string& skillName,
        int diceNumber,
        int damage,
        bool isStunSuccess,
        Battle& battle,
        GameContext& player,
        GameContext& monster
    ) const;

    // 플레이어가 도주를 시도한 결과를 출력합니다.
    // [수정] ConsoleUI는 로직을 처리하지 않으므로 결과값만 받아 출력
    static void PrintPlayerRunawayResult(bool isSuccess);

    // 현재 플레이어 턴 번호를 출력합니다.
    // [수정] ConsoleUI는 Battle 내부 값을 직접 알 수 없으므로 턴 수만 받아 출력
    static void PrintPlayerTurnCount(int turnCount);

    // 전투 결과를 확인하고 승리 또는 패배 메시지를 출력합니다.
    static void PrintBattleResult(GameContext& player, GameContext& monster, Battle& battle);


    //[추가] 전투 시작 출력 함수
    static void PrintBattleStart(GameContext& context);


    //[추가] 주사위 결과 출력 함수
    static void PrintDiceResult(int diceValue);

    //[추가] 플레이어 일반 공격 결과 출력 함수
    static void PrintPlayerMeleeAttackResultMessage(
        const std::string& playerName,
        const std::string& monsterName,
        int damage
    );

    //[추가] 플레이어 스킬 공격 결과 출력 함수
    static void PrintPlayerSkillAttackResultMessage(
        const std::string& playerName,
        const std::string& monsterName,
        int damage
    );

    //[추가] 공격 실패 출력 함수
    static void PrintAttackMiss();

    //[추가] 스킬 실패 출력 함수
    static void PrintSkillMiss();

    //[추가] MP 부족 출력 함수
    static void PrintNotEnoughMp();

    //[추가] 스턴 성공 출력 함수
    static void PrintStunSuccess(const std::string& monsterName);

    //[추가] 몬스터 스턴 상태 출력 함수
    static void PrintMonsterStunned(const std::string& monsterName);

    //[추가] 몬스터 공격 결과 출력 함수
    static void PrintMonsterAttackResult(
        const std::string& monsterName,
        const std::string& playerName,
        int damage
    );

    //[추가] 도망 성공 출력 함수
    static void PrintRunawaySuccess();

    //[추가] 도망 실패 출력 함수
    static void PrintRunawayFail();

    //[추가] 전투 승리 출력 함수
    static void PrintBattleVictory(const std::string& monsterName);

    //[추가] 전투 패배 출력 함수
    static void PrintBattleDefeat(const std::string& playerName);

    //[추가] 전투 중단 출력 함수
    static void PrintBattleStopped();

    // [추가] 보상 출력 함수
    static void PrintReward(int exp, int gold);

    //[추가] 레벨업 출력 함수
    static void PrintLevelUp(const std::string& playerName, int level);






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



    // New Cut Scene 1: 주사위 게임_ 진(승) 류(패)
    static void ShowNewCutScene1();

    // New Cut Scene 2: 류 - 야쿠자
    static void ShowNewCutScene2();

    // New Cut Scene 3: 진 - 경찰
    static void ShowNewCutScene3();

    // New Cut Scene 4: 강사라 - 의대
    static void ShowNewCutScene4();

    // New Cut Scene 5: 류 - 후계자
    static void ShowNewCutScene5();

    // New Cut Scene 6: 진 경찰 - 언더커버 (마약 전담반)
    static void ShowNewCutScene6();

    // New Cut Scene 7: 조직원끼리 항쟁 컷신
    static void ShowNewCutScene7();

    // New Cut Scene 8: 강사라 진태식 류노스케 조우
    static void ShowNewCutScene8();

    // New Cut Scene 9: 류/진 상호 경계 컷신
    static void ShowNewCutScene9();

    // New Cut Scene 10: 강사라 제지
    static void ShowNewCutScene10();

    // New Cut Scene 11: 뒷짐을 지고 있는 아버지->류에게 압박
    static void ShowNewCutScene11();

    // New Cut Scene 12: 카지노에서 습격
    static void ShowNewCutScene12();

    // New Cut Scene 13: 진태식 중상 -> 진료소 이동
    static void ShowNewCutScene13();

    // New Cut Scene 14: 류 진료소 습격 / 문 박
    static void ShowNewCutScene14();

    // New Cut Scene 15: 태식 쓰러진 컷신
    static void ShowNewCutScene15();

    // New Cut Scene 16: 강사라 제지
    static void ShowNewCutScene16();

    // New Cut Scene 17: 류가 칼찌
    static void ShowNewCutScene17();

    // New Cut Scene 18: 강사라 사망
    static void ShowNewCutScene18();

    // New Cut Scene 19: 류 -> 승리 시 태식 사망
    static void ShowNewCutScene19();

    // New Cut Scene 20: 류 승리 의자에 앉아있는 고독한 느낌의 컷신
    static void ShowNewCutScene20();

    // New Cut Scene 21: 진이 서있고 류 무릎꿇은 컷신 
    static void ShowNewCutScene21();

    // New Cut Scene 22: 아래에서 바라보는 슬픈 표정의 류 컷신
    static void ShowNewCutScene22();

    // New Cut Scene 23: 통창으로 달려가는 류 컷신
    static void ShowNewCutScene23();

    // New Cut Scene 24: 류가 건물에서 떨어지는 컷신
    static void ShowNewCutScene24();

    // NewCutScene 이미지 출력 함수
    static void PrintNewCutScene1Image();
    static void PrintNewCutScene2Image();
    static void PrintNewCutScene3Image();
    static void PrintNewCutScene4Image();
    static void PrintNewCutScene5Image();
    static void PrintNewCutScene6Image();
    static void PrintNewCutScene7Image();
    static void PrintNewCutScene8Image();
    static void PrintNewCutScene9Image();
    static void PrintNewCutScene10Image();
    static void PrintNewCutScene11Image();
    static void PrintNewCutScene12Image();
    static void PrintNewCutScene13Image();
    static void PrintNewCutScene14Image();
    static void PrintNewCutScene15Image();
    static void PrintNewCutScene16Image();
    static void PrintNewCutScene17Image();
    static void PrintNewCutScene18Image();
    static void PrintNewCutScene19Image();
    static void PrintNewCutScene20Image();
    static void PrintNewCutScene21Image();
    static void PrintNewCutScene22Image();
    static void PrintNewCutScene23Image();
    static void PrintNewCutScene24Image();



    // 주사위 눈금별 아스키 이미지 출력 함수 선언
    static void PrintDice1();  // 주사위 눈금 1 출력
    static void PrintDice2();  // 주사위 눈금 2 출력
    static void PrintDice3();  // 주사위 눈금 3 출력
    static void PrintDice4();  // 주사위 눈금 4 출력
    static void PrintDice5();  // 주사위 눈금 5 출력
    static void PrintDice6();  // 주사위 눈금 6 출력

    //래퍼 함수 컷신 출력하는건데 게임매니저 더 건들 자신이없어서 여기다 추가함 // 기존의 showcutscene 별명 붙여주는 겁니다.
    static void PrintAct1Cutscene();
    static void PrintAct2Cutscene();
    static void PrintAct3Cutscene();
    static void PrintEnding();
    static void PrintPlayerStatus(GameContext& context);

    // 주사위 애니메이션 공통 실행 함수
    static void PrintDiceAnimationBySpeed(int delayMilliseconds);


    //컷신 화면 나누기
    static void DrawCutSceneScreen(
        const std::vector<std::string>& sceneLines,
        const std::vector<std::string>& dialogueLines
    );

    static void PrintFixedWidthText(const std::string& text, int width);
    
    //게임 화면 나누기
    static void DrawGameScreen(
        const std::vector<std::string>& cutSceneLines,
        const std::vector<std::string>& logLines,
        Player& player,
        const std::vector<std::string>& choiceLines
    );

    static void DrawGameScreen(
        const std::vector<std::string>& cutSceneLines,
        const std::vector<std::string>& logLines,
        const std::vector<std::string>& statusLines,
        const std::vector<std::string>& choiceLines
    );



};

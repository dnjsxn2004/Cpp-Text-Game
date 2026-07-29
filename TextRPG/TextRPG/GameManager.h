#pragma once
#include "InputManager.h"

class GameManager
{
public:
    void Run();

private:
    // 초기화
    void Initialize();

    // 게임 종료 처리
    void ExitGame();

    // 전체 상태 업데이트
    void UpdateInit();
    void UpdateMainMenu();
    void UpdateEnding();

    // 메인 메뉴 하위 처리 함수
    void HandleMainMenu();
    void HandleShop();
    void HandleStory();
    void HandleReward();
    void HandleLevelUp();
    void HandleInventory();
    void HandleBossBattle();

    // 전투 관련 처리 함수
    void HandleNormalBattle();
    void StartBattle();
    void UpdateBattle();
    void EndBattle();

    // 세이브 관련 함수
    bool CheckSaveSlot();
    void ShowSaveMenu();
    bool LoadSelectedSave();

    // 캐릭터/튜토리얼 관련 함수
    void ShowCharacterSelect();
    void RunPrologueTutorial();

private:
    // 전체 흐름 상태
    enum class Phase
    {
        InitialStage,   // 시작 단계
        MainLoop,       // 메인 진행 단계
        Ending,         // 엔딩 단계
        GameOver        // 게임 종료
    };

    // 시작 단계 상태
    enum class InitialState
    {
        CheckSavesSlot,     // 세이브 슬롯 존재 확인
        SelectSave,         // 세이브 선택
        CharacterSelect,    // 캐릭터 선택
        PrologueTutorial    // 튜토리얼 진행
    };

    // 메인 루프 상태
    enum class MainMenuState
    {
        MainMenu,       // 메인 메뉴
        NormalBattle,   // 일반 전투
        Shop,           // 상점
        Story,          // 스토리
        Reward,         // 보상
        LevelUp,        // 레벨업
        Inventory,      // 인벤토리
        BossBattle,     // 보스전
        ExitGame        // 게임 종료 선택
    };

    // 전투 내부 상태
    enum class BattleState
    {
        Start,              // 전투 시작 연출, 적 생성
        PlayerTurn,         // 플레이어 턴
        EnemyTurn,          // 적 턴
        CheckResult,        // 승패 판정
        Victory,            // 승리 처리
        Defeat              // 패배 처리
    };

private:
    // 현재 상태 저장 변수
    Phase phaseEnum;
    InitialState initialStateEnum;
    MainMenuState mainMenuStateEnum;
    BattleState battleStateEnum;

    // 입력 관리
    InputManager inputManager;

    //  게임 진행 데이터
    bool hasSave = false;       // 세이브 존재 여부
    bool loadSuccess = false;   // 세이브 로드 성공 여부
    bool isWin = false;         // 전투 승리 여부
    bool playerLevelUp = false; // 레벨업 여부
    int storyLevel = 0;         // 스토리 진행도


};

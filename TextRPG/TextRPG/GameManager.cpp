#include "GameManager.h"
#include <iostream>
#include "ConsolUI.h"

// 게임 시작
void GameManager::Run()
{
    Initialize();

    while (phaseEnum != Phase::GameOver)
    {
        switch (phaseEnum)
        {
        case Phase::InitialStage:
            UpdateInit();
            break;

        case Phase::MainLoop:
            UpdateMainMenu();
            break;

        case Phase::Ending:
            UpdateEnding();
            break;

        case Phase::GameOver:
            break;

        default:
            break;
        }
    }

    ExitGame();
}

// 초기값 세팅
void GameManager::Initialize()
{
    phaseEnum = Phase::InitialStage;
    initialStateEnum = InitialState::CheckSavesSlot;
    mainMenuStateEnum = MainMenuState::MainMenu;
    battleStateEnum = BattleState::Start;

    hasSave = false;
    loadSuccess = false;
    isWin = false;
    playerLevelUp = false;
    storyLevel = 0;

    playerHp = 100;
    enemyHp = 50;
}

// 게임 종료 처리
void GameManager::ExitGame()
{
    // TODO:
    // - 게임 종료 전 저장이 필요하면 저장 처리
    // - 종료 메시지 출력
    std::cout << "게임을 종료합니다.\n";
}

// 시작 단계 처리
void GameManager::UpdateInit()
{
    switch (initialStateEnum)
    {
    case InitialState::CheckSavesSlot:
    {
        hasSave = CheckSaveSlot();

        if (hasSave)
        {
            initialStateEnum = InitialState::SelectSave;
        }
        else
        {
            initialStateEnum = InitialState::CharacterSelect;
        }
        break;
    }

    case InitialState::SelectSave:
    {
        ShowSaveMenu();
        loadSuccess = LoadSelectedSave();

        if (loadSuccess)
        {
            phaseEnum = Phase::MainLoop;
            mainMenuStateEnum = MainMenuState::MainMenu;
        }
        else
        {
            initialStateEnum = InitialState::CharacterSelect;
        }
        break;
    }

    case InitialState::CharacterSelect:
    {
        ShowCharacterSelect();
        initialStateEnum = InitialState::PrologueTutorial;
        break;
    }

    case InitialState::PrologueTutorial:
    {
        RunPrologueTutorial();
        phaseEnum = Phase::MainLoop;
        mainMenuStateEnum = MainMenuState::MainMenu;
        break;
    }

    default:
        break;
    }
}

// 메인 루프 처리
void GameManager::UpdateMainMenu()
{
    switch (mainMenuStateEnum)
    {
    case MainMenuState::MainMenu:
        HandleMainMenu();
        break;

    case MainMenuState::NormalBattle:
        HandleNormalBattle();
        break;

    case MainMenuState::Shop:
        HandleShop();
        break;

    case MainMenuState::Story:
        HandleStory();
        break;

    case MainMenuState::Reward:
        HandleReward();
        break;

    case MainMenuState::LevelUp:
        HandleLevelUp();
        break;

    case MainMenuState::Inventory:
        HandleInventory();
        break;

    case MainMenuState::BossBattle:
        HandleBossBattle();
        break;

    case MainMenuState::ExitGame:
        phaseEnum = Phase::GameOver;
        break;

    default:
        break;
    }
}

// 메인 메뉴 화면
void GameManager::HandleMainMenu()
{
    std::cout << "\n=== 메인 메뉴 ===\n";
    std::cout << "1. 일반 전투\n";
    std::cout << "2. 상점\n";
    std::cout << "3. 스토리\n";
    std::cout << "4. 인벤토리\n";
    std::cout << "0. 게임 종료\n";

    if (playerLevelUp)
    {
        mainMenuStateEnum = MainMenuState::LevelUp;
        return;
    }

    int choice = inputManager.InputInMassegeToRange("번호를 입력해주세요: ", 0, 4);

    switch (choice)
    {
    case 1:
        mainMenuStateEnum = MainMenuState::NormalBattle;
        battleStateEnum = BattleState::Start;
        break;

    case 2:
        mainMenuStateEnum = MainMenuState::Shop;
        break;

    case 3:
        mainMenuStateEnum = MainMenuState::Story;
        break;

    case 4:
        mainMenuStateEnum = MainMenuState::Inventory;
        break;

    case 0:
        mainMenuStateEnum = MainMenuState::ExitGame;
        break;

    default:
        break;
    }
}

// 일반 전투 처리
void GameManager::HandleNormalBattle()
{
    switch (battleStateEnum)
    {
    case BattleState::Start:
        StartBattle();
        break;

    case BattleState::PlayerTurn:
        UpdateBattle();
        break;

    case BattleState::EnemyTurn:
    {
        battleStateEnum = BattleState::CheckResult;
        break;
    }

    case BattleState::CheckResult:
    {
        if (enemyHp <= 0)
        {
            battleStateEnum = BattleState::Victory;
        }
        else if (playerHp <= 0)
        {
            battleStateEnum = BattleState::Defeat;
        }
        else
        {
            battleStateEnum = BattleState::PlayerTurn;
        }
        break;
    }

    case BattleState::Victory:
        EndBattle();
        isWin = true;
        mainMenuStateEnum = MainMenuState::Reward;
        break;

    case BattleState::Defeat:
        EndBattle();
        isWin = false;
        phaseEnum = Phase::GameOver;
        break;

    default:
        break;
    }
}

// 전투 시작
void GameManager::StartBattle()
{
    battleStateEnum = BattleState::PlayerTurn;
}

// 플레이어 턴 진행
void GameManager::UpdateBattle()
{
    std::cout << "\n=== 플레이어 턴 ===\n";
    std::cout << "1. 물리 공격\n";
    std::cout << "2. 스킬 공격\n";
    std::cout << "0. 도망/취소(임시)\n";

    int battleChoice = inputManager.InputInMassegeToRange("번호를 입력해주세요: ", 0, 2);

    switch (battleChoice)
    {
    case 1:
        battleStateEnum = BattleState::CheckResult;
        break;

    case 2:
        battleStateEnum = BattleState::CheckResult;
        break;

    case 0:
        std::cout << "전투를 종료하고 메인 메뉴로 돌아갑니다. (임시)\n";
        mainMenuStateEnum = MainMenuState::MainMenu;
        break;

    default:
        break;
    }
}

// 전투 종료 처리
void GameManager::EndBattle()
{
    std::cout << "전투 종료\n";
}

void GameManager::HandleShop()
{
    std::cout << "\n=== 상점 ===\n";
    std::cout << "상점 기능 구현 예정\n";
    mainMenuStateEnum = MainMenuState::MainMenu;
}

void GameManager::HandleStory()
{
    std::cout << "\n=== 스토리 ===\n";

    switch (storyLevel)
    {
    case 0:
        storyLevel = 1;
        break;

    case 1:
        storyLevel = 2;
        break;

    default:
        break;
    }

    mainMenuStateEnum = MainMenuState::MainMenu;
}

void GameManager::HandleReward()
{
    std::cout << "\n=== 보상 화면 ===\n";

    if (isWin)
    {
        std::cout << "전투 승리 보상 지급\n";
        playerLevelUp = true;
    }

    mainMenuStateEnum = MainMenuState::MainMenu;
}

void GameManager::HandleLevelUp()
{
    playerLevelUp = false;
    mainMenuStateEnum = MainMenuState::MainMenu;
}

void GameManager::HandleInventory()
{
    std::cout << "\n=== 인벤토리 ===\n";
    std::cout << "인벤토리 기능 구현 예정\n";
    mainMenuStateEnum = MainMenuState::MainMenu;
}

void GameManager::HandleBossBattle()
{
    mainMenuStateEnum = MainMenuState::MainMenu;
}

// 엔딩 처리
void GameManager::UpdateEnding()
{
    phaseEnum = Phase::GameOver;
}

// 보조 함수
bool GameManager::CheckSaveSlot()
{
    return false;
}

void GameManager::ShowSaveMenu()
{
}

bool GameManager::LoadSelectedSave()
{
    int choice = inputManager.InputInMassegeToRange("번호를 입력해주세요: ", 1, 3);

    switch (choice)
    {
    case 1:
        std::cout << "슬롯 1 로드\n";
        return true;

    case 2:
        std::cout << "슬롯 2 로드\n";
        return true;

    case 3:
        return false;

    default:
        return false;
    }
}

void GameManager::ShowCharacterSelect()
{
}

void GameManager::RunPrologueTutorial()
{
}

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
        // TODO:
        // - 실제 세이브 파일/슬롯이 존재하는지 검사
        // - 파일 시스템, DB, 텍스트 파일 등 네 저장 방식에 맞춰 구현
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
        // TODO:
        // - 세이브 목록 출력
        // - 불러오기 / 처음부터 / 취소 같은 메뉴 제공
        ShowSaveMenu();

        // TODO:
        // - 선택한 세이브를 실제로 로드
        // - 로드 성공 시 true
        // - 취소 또는 실패 시 false
        loadSuccess = LoadSelectedSave();

        if (loadSuccess)
        {
            // 세이브 로드 성공 → 메인 루프로 이동
            phaseEnum = Phase::MainLoop;
            mainMenuStateEnum = MainMenuState::MainMenu;
        }
        else
        {
            // 불러오기 취소 또는 실패 → 새 게임 진행으로 이동
            initialStateEnum = InitialState::CharacterSelect;
        }
        break;
    }

    case InitialState::CharacterSelect:
    {
        // TODO:
        // - 캐릭터 직업/외형/이름 선택 화면 출력
        // - 선택 결과를 플레이어 데이터에 저장
        ShowCharacterSelect();

        // 캐릭터 선택 후 튜토리얼로 이동
        initialStateEnum = InitialState::PrologueTutorial;
        break;
    }

    case InitialState::PrologueTutorial:
    {
        // TODO:
        // - 튜토리얼 대사 출력
        // - 기본 조작 설명
        // - 첫 전투/기본 시스템 체험
        RunPrologueTutorial();

        // 튜토리얼 완료 후 메인 루프로 이동
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
    // TODO:
    // - 메인 메뉴 UI 출력
    // - 플레이어 상태(HP, 골드, 레벨, 스토리 진행도 등) 표시 가능
    std::cout << "\n=== 메인 메뉴 ===\n";
    std::cout << "1. 일반 전투\n";
    std::cout << "2. 상점\n";
    std::cout << "3. 스토리\n";
    std::cout << "4. 인벤토리\n";
    std::cout << "0. 게임 종료\n";

    // TODO:
    // - 경험치/레벨 조건 검사
    // - 레벨업 조건 만족 시 레벨업 상태로 먼저 보내기
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
        // TODO:
        // - 적 공격 함수
        // - 플레이어 HP 감소 함수

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
    // TODO:
    // - 몬스터 생성
    // - 플레이어/적 전투 시작 연출
    // - 초기 턴 설정

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
        // TODO:
        // - 플레이어 기본 공격 데미지 계산
        // - 적 HP 감소

        battleStateEnum = BattleState::CheckResult;
        break;

    case 2:
        // TODO:
        // - 스킬 목록 출력
        // - 마나 사용량 검사
        // - 스킬 데미지 계산 후 적용

        battleStateEnum = BattleState::CheckResult;
        break;

    case 0:
        // TODO:
        // - 도망 가능 여부 판정
        // - 도망 성공/실패 로직
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
    // TODO:
    // - 전투 종료 시 상태 정리
    // - 버프/디버프 제거
    // - 전투 보상 데이터 준비
    std::cout << "전투 종료\n";
}

// 나머지 메뉴 처리

void GameManager::HandleShop()
{
    // TODO:
    // - 상점 목록 출력
    // - 구매 / 판매 / 나가기 기능
    std::cout << "\n=== 상점 ===\n";
    std::cout << "상점 기능 구현 예정\n";

    mainMenuStateEnum = MainMenuState::MainMenu;
}

void GameManager::HandleStory()
{
    // TODO:
    // - 스토리 진행도에 따라 이벤트/대사/전투 분기
    std::cout << "\n=== 스토리 ===\n";

    switch (storyLevel)
    {
    case 0:
        // TODO:
        // - 첫 번째 스토리 대사/연출
        // - 필요 시 스토리 전투 진입

        storyLevel = 1;
        break;

    case 1:
        // TODO:
        // - 두 번째 스토리 대사/연출

        storyLevel = 2;

        break;

    default:
        break;
    }

    mainMenuStateEnum = MainMenuState::MainMenu;
}

void GameManager::HandleReward()
{
    // TODO:
    // - 전투 승리 보상 계산
    // - 경험치, 골드, 아이템 지급
    // - 레벨업 조건 만족 시 playerLevelUp = true
    std::cout << "\n=== 보상 화면 ===\n";

    if (isWin)
    {
        std::cout << "전투 승리 보상 지급\n";

        // 예시
        playerLevelUp = true;
    }

    mainMenuStateEnum = MainMenuState::MainMenu;
}

void GameManager::HandleLevelUp()
{
    // TODO:
    // - 레벨업 연출
    // - 능력치 상승

    playerLevelUp = false;
    mainMenuStateEnum = MainMenuState::MainMenu;
}

void GameManager::HandleInventory()
{
    // TODO:
    // - 보유 아이템 목록 출력
    // - 장착/해제/사용 기능
    std::cout << "\n=== 인벤토리 ===\n";
    std::cout << "인벤토리 기능 구현 예정\n";

    mainMenuStateEnum = MainMenuState::MainMenu;
}

void GameManager::HandleBossBattle()
{
    // TODO:
    // - 보스 전투 전용 초기화
    // - 일반 전투와 다른 패턴 적용


    mainMenuStateEnum = MainMenuState::MainMenu;
}


// 엔딩 처리

void GameManager::UpdateEnding()
{
    // TODO:
    // - 엔딩 연출
    // - 엔딩 연출 분기 변수, 함수 필요
    // - 변수 GameManager 에서 제작
    // - 함수 UI 에서 만들 것

    phaseEnum = Phase::GameOver;
}

// 보조 함수
bool GameManager::CheckSaveSlot()
{
    // TODO:
    // - 실제 세이브 파일 존재 여부 확인

    return false;
}

void GameManager::ShowSaveMenu()
{
    // TODO:
    // - 세이브 슬롯 목록 표시
    // - 예: 슬롯1 / 슬롯2 / 처음부터 / 취소

}

bool GameManager::LoadSelectedSave()
{
    // TODO:
    // - 실제로는 세이브 선택 입력을 받고
    // - 선택 슬롯 데이터 로드 성공/실패를 반환해야 함

    int choice = inputManager.InputInMassegeToRange("번호를 입력해주세요: ", 1, 3);

    switch (choice)
    {
    case 1:
        // TODO:
        // - 슬롯 1 데이터 로드
        std::cout << "슬롯 1 로드\n";
        return true;

    case 2:
        // TODO:
        // - 슬롯 2 데이터 로드
        std::cout << "슬롯 2 로드\n";
        return true;

    case 3:
        // 새 게임 선택
        return false;

    default:
        return false;
    }
}

void GameManager::ShowCharacterSelect()
{
    // TODO:
    // - 캐릭터 선택 메뉴 출력
    // - 직업, 이름, 시작 능력치 결정 등

}

void GameManager::RunPrologueTutorial()
{
    // TODO:
    // - 기본 이동/전투/메뉴 조작 설명
    // - 짧은 튜토리얼 전투 배치 
    // - 튜토리얼 아이템 사용 배치
 
}

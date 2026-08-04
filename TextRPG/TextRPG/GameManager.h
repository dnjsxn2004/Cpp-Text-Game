#pragma once

#include "GameContext.h"
#include "Shop.h"
#include "GameState.h"
#include "UIScreen.h"
#include "Inventory.h"
#include "ConsolUI.h"
#include "InputManager.h"


class GameManager
{
public:

    GameManager();
    ~GameManager();

    void Run();

private:

    // 상태
    GameState currentState;

    // 게임 데이터
    GameContext context;
    Shop shop;

    // 시스템 상태
    bool loadSuccess;
    bool isWin;
    bool playerLevelUp;

    // UI 데이터
    std::vector<std::string> logs;
    std::vector<std::string> playerStatus;
    std::vector<std::string> monsterStatus;

    std::vector<int> shopIndexMap;


    //캐릭터 선택 변수 0 :진, 1 : 류
    int selectedCharacterIndex = 0; 

private:

    // 초기화
    void Initialize();

    // 컷신
    void PlayOpeningCutscenes();

    void RenderCharacterSelect();

    void RenderMainMenu();

    void RenderShop();

    void RenderInventory();

    void RenderStatus();

    void RenderStory();

    void HandleCharacterSelectInput();

    void HandleMainMenuInput();

    void HandleShopInput();

    void HandleInventoryInput();

    void HandleStatusInput();

    void HandleStoryInput();

    void StartNormalBattle();

    void StartStoryBattleFlow();

    bool StartMiddleBossBattle();

    bool StartFinalBossBattle();

    bool ShowCharacterPreview(int choice);


    // 종료

    void Ending();

    void GameOver();

    // 로그

    void AddLog(const std::string& text);
};

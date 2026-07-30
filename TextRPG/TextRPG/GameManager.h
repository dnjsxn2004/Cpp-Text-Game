#pragma once

#include "GameContext.h"
#include "InputManager.h"

class GameManager
{
public:
    GameManager();
    ~GameManager();

    void Run();

private:
    enum class Phase
    {
        InitialStage,
        MainLoop,
        Ending,
        GameOver
    };

    enum class InitialState
    {
        Act1Cutscene,
        Act2Cutscene,
        Act3Cutscene,
        CharacterSelect,
        Act4Start
    };

    enum class MainMenuState
    {
        MainMenu,
        NormalBattle,
        Shop,
        Inventory,
        Story,
        BossBattle,
        ExitGame
    };

private:
    GameContext context;
    InputManager inputManager;

    Phase phaseEnum;
    InitialState initialStateEnum;
    MainMenuState mainMenuStateEnum;

    bool isBossDefeated;
    int storyLevel;

private:
    void Initialize();
    void ExitGame();

    void UpdateInitialStage();
    void UpdateMainLoop();
    void UpdateEnding();

    void RunAct1Cutscene();
    void RunAct2Cutscene();
    void RunAct3Cutscene();
    void ShowCharacterSelect();
    void RunAct4StartCutscene();

    void HandleMainMenu();
    void HandleNormalBattle();
    void HandleShop();
    void HandleInventory();
    void HandleStory();
    void HandleBossBattle();

    void RunEndingCutscene();

    void WaitForEnter();
};

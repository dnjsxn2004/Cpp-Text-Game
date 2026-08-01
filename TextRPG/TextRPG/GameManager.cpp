#include "GameManager.h"

#include <iostream>
#include <limits>

#include "ConsolUI.h"
#include "Jin.h"
#include "Ryu.h"

using namespace std;

GameManager::GameManager()
    : phaseEnum(Phase::InitialStage),
    initialStateEnum(InitialState::Act1Cutscene),
    mainMenuStateEnum(MainMenuState::MainMenu),
    isBossDefeated(false),
    storyLevel(0)
{
}

GameManager::~GameManager()
{
}

void GameManager::Run()
{
    Initialize();

    while (phaseEnum != Phase::GameOver)
    {
        switch (phaseEnum)
        {
        case Phase::InitialStage:
            UpdateInitialStage();
            break;

        case Phase::MainLoop:
            UpdateMainLoop();
            break;

        case Phase::Ending:
            UpdateEnding();
            break;

        case Phase::GameOver:
            break;

        default:
            phaseEnum = Phase::GameOver;
            break;
        }
    }

    ExitGame();
}

void GameManager::Initialize()
{
    context.SetGameRunning(true);
    context.SetGameOver(false);

    phaseEnum = Phase::InitialStage;
    initialStateEnum = InitialState::Act1Cutscene;
    mainMenuStateEnum = MainMenuState::MainMenu;

    isBossDefeated = false;
    storyLevel = 0;
}

void GameManager::ExitGame()
{
    ConsoleUI::ClearScreen();
    ConsoleUI::PrintLine();
    ConsoleUI::PrintTitle("Game Exit");
    ConsoleUI::PrintLine();
    ConsoleUI::PrintMessage("Game will be closed.");
    ConsoleUI::PrintLine();
}

void GameManager::UpdateInitialStage()
{
    switch (initialStateEnum)
    {
    case InitialState::Act1Cutscene:
        RunAct1Cutscene();
        initialStateEnum = InitialState::Act2Cutscene;
        break;

    case InitialState::Act2Cutscene:
        RunAct2Cutscene();
        initialStateEnum = InitialState::Act3Cutscene;
        break;

    case InitialState::Act3Cutscene:
        RunAct3Cutscene();
        initialStateEnum = InitialState::CharacterSelect;
        break;

    case InitialState::CharacterSelect:
        ShowCharacterSelect();
        initialStateEnum = InitialState::Act4Start;
        break;

    case InitialState::Act4Start:
        RunAct4StartCutscene();
        phaseEnum = Phase::MainLoop;
        mainMenuStateEnum = MainMenuState::MainMenu;
        break;

    default:
        phaseEnum = Phase::GameOver;
        break;
    }
}

void GameManager::UpdateMainLoop()
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

    case MainMenuState::Inventory:
        HandleInventory();
        break;

    case MainMenuState::Story:
        HandleStory();
        break;

    case MainMenuState::BossBattle:
        HandleBossBattle();
        break;

    case MainMenuState::ExitGame:
        phaseEnum = Phase::GameOver;
        break;

    default:
        mainMenuStateEnum = MainMenuState::MainMenu;
        break;
    }
}

void GameManager::UpdateEnding()
{
    RunEndingCutscene();
    phaseEnum = Phase::GameOver;
}

void GameManager::RunAct1Cutscene()
{
    ConsoleUI::ClearScreen();
    ConsoleUI::PrintLine();
    ConsoleUI::PrintTitle("Act 1");
    ConsoleUI::PrintLine();
    ConsoleUI::PrintMessage("Act 1 cutscene.");
    ConsoleUI::PrintLine();

    WaitForEnter();
}

void GameManager::RunAct2Cutscene()
{
    ConsoleUI::ClearScreen();
    ConsoleUI::PrintLine();
    ConsoleUI::PrintTitle("Act 2");
    ConsoleUI::PrintLine();
    ConsoleUI::PrintMessage("Act 2 cutscene.");
    ConsoleUI::PrintLine();

    WaitForEnter();
}

void GameManager::RunAct3Cutscene()
{
    ConsoleUI::ClearScreen();
    ConsoleUI::PrintLine();
    ConsoleUI::PrintTitle("Act 3");
    ConsoleUI::PrintLine();
    ConsoleUI::PrintMessage("Act 3 cutscene.");
    ConsoleUI::PrintLine();

    WaitForEnter();
}

void GameManager::ShowCharacterSelect()
{
    ConsoleUI::ClearScreen();

    ConsoleUI::PrintLine();
    ConsoleUI::PrintTitle("Character Select");
    ConsoleUI::PrintLine();
    ConsoleUI::PrintMessage("1. Ryu");
    ConsoleUI::PrintMessage("2. Jin");
    ConsoleUI::PrintLine();

    int choice = inputManager.InputInMassegeToRange("Select character: ",1,2);

    switch (choice)
    {
    case 1:
        context.SetPlayer(new Ryu());
        ConsoleUI::PrintMessage("Ryu selected.");
        ConsoleUI::PrintKangImage();
        break;

    case 2:
        context.SetPlayer(new Jin());
        ConsoleUI::PrintMessage("Jin selected.");
        break;

    default:
        context.SetPlayer(new Ryu());
        ConsoleUI::PrintMessage("Default character Ryu selected.");
        break;
    }

    ConsoleUI::PrintLine();
    WaitForEnter();
}

void GameManager::RunAct4StartCutscene()
{
    ConsoleUI::ClearScreen();

    ConsoleUI::PrintLine();
    ConsoleUI::PrintTitle("Act 4");
    ConsoleUI::PrintLine();
    ConsoleUI::PrintMessage("Act 4 starts.");
    ConsoleUI::PrintMessage("Move to main menu.");
    ConsoleUI::PrintLine();

    WaitForEnter();
}

void GameManager::HandleMainMenu()
{
    ConsoleUI::ClearScreen();
    ConsoleUI::PrintMainMenu();

    int choice = inputManager.InputInMassegeToRange(
        "Input number: ",
        0,
        4
    );

    switch (choice)
    {
    case 1:
        mainMenuStateEnum = MainMenuState::NormalBattle;
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
        mainMenuStateEnum = MainMenuState::MainMenu;
        break;
    }
}

void GameManager::HandleNormalBattle()
{
    ConsoleUI::ClearScreen();

    ConsoleUI::PrintLine();
    ConsoleUI::PrintTitle("Normal Battle");
    ConsoleUI::PrintLine();
    ConsoleUI::PrintMessage("Temporary normal battle.");
    ConsoleUI::PrintMessage("You win.");
    ConsoleUI::PrintLine();

    WaitForEnter();

    mainMenuStateEnum = MainMenuState::MainMenu;
}

void GameManager::HandleShop()
{
    ConsoleUI::ClearScreen();

    ConsoleUI::PrintLine();
    ConsoleUI::PrintTitle("Shop");
    ConsoleUI::PrintLine();
    ConsoleUI::PrintMessage("Shop is not connected yet.");
    ConsoleUI::PrintLine();

    WaitForEnter();

    mainMenuStateEnum = MainMenuState::MainMenu;
}

void GameManager::HandleInventory()
{
    ConsoleUI::ClearScreen();

    ConsoleUI::PrintLine();
    ConsoleUI::PrintTitle("Inventory");
    ConsoleUI::PrintLine();
    ConsoleUI::PrintMessage("Inventory is not connected yet.");
    ConsoleUI::PrintLine();

    WaitForEnter();

    mainMenuStateEnum = MainMenuState::MainMenu;
}

void GameManager::HandleStory()
{
    ConsoleUI::ClearScreen();

    ConsoleUI::PrintLine();
    ConsoleUI::PrintTitle("Story");
    ConsoleUI::PrintLine();
    ConsoleUI::PrintMessage("Move to boss battle.");
    ConsoleUI::PrintLine();

    WaitForEnter();

    mainMenuStateEnum = MainMenuState::BossBattle;
}

void GameManager::HandleBossBattle()
{
    ConsoleUI::ClearScreen();

    ConsoleUI::PrintLine();
    ConsoleUI::PrintTitle("Boss Battle");
    ConsoleUI::PrintLine();
    ConsoleUI::PrintMessage("Temporary boss battle.");
    ConsoleUI::PrintMessage("Boss defeated.");
    ConsoleUI::PrintLine();

    isBossDefeated = true;

    WaitForEnter();

    phaseEnum = Phase::Ending;
}

void GameManager::RunEndingCutscene()
{
    ConsoleUI::ClearScreen();

    ConsoleUI::PrintLine();
    ConsoleUI::PrintTitle("Ending");
    ConsoleUI::PrintLine();
    ConsoleUI::PrintMessage("Ending cutscene.");
    ConsoleUI::PrintLine();

    WaitForEnter();
}

void GameManager::WaitForEnter()
{
    cout << "Press Enter to continue...";

    cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
    cin.get();
}

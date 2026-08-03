#include "GameManager.h"

#include <iostream>
#include <vector>

#include "ConsolUI.h"
#include "InputManager.h"
#include "Battle.h"
#include "Jin.h"
#include "Ryu.h"
#include "Gang.h"
#include "Monster.h"
#include "Player.h"
#include "GameState.h"


using namespace std;


GameManager::GameManager()
    : context(),
    shop(),
    loadSuccess(false),
    isWin(false),
    playerLevelUp(false),
    selectedCharacterIndex(0)
{
}

GameManager::~GameManager()
{
}


void GameManager::Run()
{
    Initialize();

    while (context.IsGameRunning())
    {
        switch (currentState)
        {
        case GameState::Title:
            ConsoleUI::PrintStartScreen();
            InputManager::Wait();
            currentState = GameState::CutScene;
            break;

        case GameState::CutScene:
            PlayOpeningCutscenes();
            currentState = GameState::CharacterSelect;
            break;

        case GameState::CharacterSelect:
            RenderCharacterSelect();
            HandleCharacterSelectInput();
            break;

        case GameState::MainMenu:
            RenderMainMenu();
            HandleMainMenuInput();
            break;

        case GameState::Battle:

            StartNormalBattle();

            if (context.IsGameRunning())
            {
                currentState = GameState::MainMenu;
            }

            break;

        case GameState::Shop:
            RenderShop();
            HandleShopInput();
            break;

        case GameState::Inventory:
            RenderInventory();
            HandleInventoryInput();
            break;

        case GameState::Status:
            RenderStatus();
            HandleStatusInput();
            break;

        case GameState::Story:
            RenderStory();
            HandleStoryInput();
            break;

        case GameState::Exit:
            context.SetGameRunning(false);
            break;
        }
    }
}



void GameManager::Initialize()
{
    logs.clear();
    AddLog("게임 시작");

    context.SetGameRunning(true);
    context.SetGameOver(false);

    currentState = GameState::Title;

    loadSuccess = false;
    isWin = false;
    playerLevelUp = false;
}


void GameManager::PlayOpeningCutscenes()
{
    ConsoleUI::DrawCutSceneScreen(
        {
            "",
            "",
            "",
            "                                      ACT 1",
     
            "",
            "",
            "",
            "",
            "",
            ""
        },
        {
            "대사"
        }
        );

    InputManager::Wait();

    ConsoleUI::DrawCutSceneScreen(
        {
            "",
            "",
            "",
            "                                      ACT 2",
          
          
        },
        {
            "대사"
        }
        );

    InputManager::Wait();

    ConsoleUI::DrawCutSceneScreen(
        {
            "",
            "",
            "",
            "                                      ACT 3",
            
            "",
            "",
            "",
            "",
            "",
            ""
        },
        {
           "대사"
        }
        );

    InputManager::Wait();
}


void GameManager::RenderMainMenu()
{
    UIScreen screen;

    playerStatus.clear();

    if (context.HasPlayer())
    {
        Player& player = context.GetPlayer();

        playerStatus.push_back(
            "이름 : " + player.GetName()
        );

        playerStatus.push_back(
            "HP : " +
            std::to_string(player.GetHp())
        );

        playerStatus.push_back(
            "MP : " +
            std::to_string(player.GetMp())
        );
    }

    screen.a =
    {
        "",
        "   [ 거점 ]",
        "",
        "   메인 화면"
    };

    screen.b = logs;

    screen.c =
    {
        "1. 전투",
        "2. 상점",
        "3. 인벤토리",
        "4. 상태 보기",
        "5. 스토리 진행",
        "0. 게임 종료"
    };

    screen.d = playerStatus;

    ConsoleUI::DrawFullLayout(screen);
}


void GameManager::HandleMainMenuInput()
{

    int choice = InputManager::InputInMassegeToRange("선택: ", 0, 5);

    switch (choice)
    {
    case 1:
        currentState = GameState::Battle;
        break;

    case 2:
        currentState = GameState::Shop;
        break;

    case 3:
        currentState = GameState::Inventory;
        break;

    case 4:
        currentState = GameState::Status;
        break;

    case 5:
        currentState = GameState::Story;
        break;

    case 0:
        currentState = GameState::Exit;
        break;
    }
}


void GameManager::StartNormalBattle()
{
    ConsoleUI::ClearScreen();

    if (!context.HasPlayer())
    {
        AddLog("플레이어가 없습니다.");
        context.SetGameOver(true);
        return;
    }

    Monster monster = SpawnRandomMonster(context);

    context.SetMonster(monster);

    logs.clear();

    AddLog("전투 시작!");
    AddLog(monster.GetName() + " 등장!");

    Battle battle(context);

    battle.RunBattle(context);

    if (context.GetPlayer().GetHp() > 0)
    {
        AddLog("전투 종료");
    }
    else
    {
        AddLog("전투 패배...");
        context.SetGameOver(true);
        context.SetGameRunning(false);
    }

    InputManager::Wait();
    ConsoleUI::ClearScreen();
}

void GameManager::StartStoryBattleFlow()
{
    ConsoleUI::PrintMessage("스토리 진행을 시작합니다.");
    InputManager::Wait();

    bool middleBossWin = StartMiddleBossBattle();

    if (!middleBossWin)
    {
        context.SetGameOver(true);
        context.SetGameRunning(false);
        return;
    }

    bool finalBossWin = StartFinalBossBattle();

    if (!finalBossWin)
    {
        context.SetGameOver(true);
        context.SetGameRunning(false);
        return;
    }

    isWin = true;
    Ending();


    isWin = false;
    Initialize();
}


bool GameManager::StartMiddleBossBattle()
{
    ConsoleUI::PrintMessage("중간보스전이 시작됩니다.");
    InputManager::Wait();

    Monster middleBoss = SpawnMiddleBoss(context);
    context.SetMonster(middleBoss);

    Battle battle(context);

    battle.RunBattle(context);

    InputManager::Wait();

    return context.GetPlayer().GetHp() > 0;
}

bool GameManager::StartFinalBossBattle()
{
    ConsoleUI::PrintMessage("최종보스전이 시작됩니다.");
    InputManager::Wait();

    Monster finalBoss = SpawnFinalBoss(context);
    context.SetMonster(finalBoss);

    Battle battle(context);

    battle.RunBattle(context);

    InputManager::Wait();

    return context.GetPlayer().GetHp() > 0;
}

void GameManager::Ending()
{
    ConsoleUI::PrintEnding();
    InputManager::Wait();
}

void GameManager::GameOver()
{
    ConsoleUI::PrintGameOver();
    InputManager::Wait();
}

void GameManager::AddLog(const std::string& text)
{
    logs.push_back(text);

    if (logs.size() > 8)
    {
        logs.erase(logs.begin());
    }
}

void GameManager::HandleCharacterSelectInput()
{
    int choice =
        InputManager::InputInMassegeToRange(
            "선택: ",
            0,
            2
        );

    switch (choice)
    {
    case 1:
        selectedCharacterIndex = 0;
        break;

    case 2:
        selectedCharacterIndex = 1;
        break;

    case 0:
        currentState = GameState::Exit;
        return;
    }

    if (selectedCharacterIndex == 0)
    {
        context.SetPlayer(new Jin());
        AddLog("진태식을 선택했습니다.");
    }
    else
    {
        context.SetPlayer(new Ryu());
        AddLog("류노스케를 선택했습니다.");
    }

    currentState = GameState::MainMenu;
}


void GameManager::RenderCharacterSelect()
{
    UIScreen screen;

    Jin jin;
    Ryu ryu;

    if (selectedCharacterIndex == 0)
    {
        ConsoleUI::PrintJinBlackImage();
    }
    else
    {
        ConsoleUI::PrintRyuBlackImage();
    }

    Player* preview =
        (selectedCharacterIndex == 0)
        ? static_cast<Player*>(&jin)
        : static_cast<Player*>(&ryu);

    
    screen.b =
    {
        "[ 캐릭터 선택 ]",
        "",
        (selectedCharacterIndex == 0)
        ? jin.GetDescription()
        : ryu.GetDescription()
    };

    
    screen.c =
    {
        (selectedCharacterIndex == 0 ? "> 진태식" : "  진태식"),
        (selectedCharacterIndex == 1 ? "> 류노스케" : "  류노스케"),
        
    };

    screen.d =
    {
        "HP  : " + std::to_string(preview->GetHp()),
        "MP  : " + std::to_string(preview->GetMp()),
        "ATK : " + std::to_string(preview->GetAttack())
    };

    ConsoleUI::DrawFullLayout(screen);
}

void GameManager::RenderShop()
{
    UIScreen screen;

    Player& player = context.GetPlayer();

    std::vector<std::string> productLines;

    const std::vector<Item>& products = shop.GetProducts();

    for (int i = 0; i < static_cast<int>(products.size()); i++)
    {
        const Item& item = products[i];

        std::string line =
            std::to_string(i + 1) + ". " +
            item.GetName() +
            " - " +
            std::to_string(item.GetPrice()) + "G";

        productLines.push_back(line);
    }

    screen.a =
    {
        "      [ 암시장 ]",
        "",
        "   어둠 속 상인이 웃는다."
    };

    screen.b = productLines;

    screen.c =
    {
        "1. 아이템 구매",
        "2. 아이템 판매",
        "0. 뒤로가기"
    };

    screen.d =
    {
        "이름 : " + player.GetName(),
        "Gold : " + std::to_string(player.GetGold()),
        "",
        "소지품 수 : " +
        std::to_string(
            context.GetInventory().GetItems().size()
        )
    };

    ConsoleUI::DrawFullLayout(screen);
}


void GameManager::HandleShopInput()
{
    int choice =
        InputManager::InputInMassegeToRange(
            "선택: ",
            0,
            2
        );

    switch (choice)
    {
    case 1:
    {
        const std::vector<Item>& products =
            shop.GetProducts();

        int itemIndex =
            InputManager::InputInMassegeToRange(
                "구매할 상품 번호: ",
                1,
                products.size()
            ) - 1;

        int quantity =
            InputManager::InputInMassegeToRange(
                "수량: ",
                1,
                99
            );

        if (shop.BuyItem(itemIndex, quantity, context))
        {
            AddLog("구매 완료");
        }
        else
        {
            AddLog("구매 실패");
        }

        break;
    }

    case 2:
    {
        Inventory& inventory =
            context.GetInventory();

        std::vector<int> sellable =
            inventory.GetSellableItemIndices();

        if (sellable.empty())
        {
            AddLog("판매 가능한 아이템이 없습니다.");
            break;
        }

        int sellIndex =
            InputManager::InputInMassegeToRange(
                "판매할 아이템 번호: ",
                1,
                sellable.size()
            ) - 1;

        int realIndex = sellable[sellIndex];

        int quantity =
            InputManager::InputInMassegeToRange(
                "판매 수량: ",
                1,
                99
            );

        if (shop.SellItem(realIndex, quantity, context))
        {
            AddLog("판매 완료");
        }
        else
        {
            AddLog("판매 실패");
        }

        break;
    }

    case 0:
        currentState = GameState::MainMenu;
        break;
    }
}


void GameManager::RenderStatus()
{
    UIScreen screen;

    Player& player = context.GetPlayer();
    Inventory& inventory = context.GetInventory();

    screen.a =
    {
        "      [ 상태 ]",
        "",
        "   거울 속의 자신을 바라본다."
    };

    screen.b =
    {
        "이름 : " + player.GetName(),
        "",
        "HP  : " + std::to_string(player.GetHp()),
        "MP  : " + std::to_string(player.GetMp()),
        "",
        "ATK : " + std::to_string(player.GetAttack()),
        "",
        "Gold : " + std::to_string(player.GetGold())
    };

    screen.c =
    {
        "0. 뒤로가기"
    };

    screen.d =
    {
        "무기 : " + inventory.GetEquippedWeaponName(),
        "방어구 : " + inventory.GetEquippedArmorName()
    };

    ConsoleUI::DrawFullLayout(screen);
}


void GameManager::HandleStatusInput()
{
    InputManager::InputInMassegeToRange(
        "0. 뒤로가기: ",
        0,
        0
    );

    currentState = GameState::MainMenu;
}



void GameManager::RenderStory()
{
    UIScreen screen;

    Player& player = context.GetPlayer();

    screen.a =
    {
        "     [ 폐쇄된 진료소 ]",
        "",
        "   비가 창문을 두드린다."
    };

    screen.b =
    {
        "강사라가 죽은 뒤,",
        "진료소엔 무거운 침묵만 남아있다.",
        "",
        "희미한 담배 냄새가 공기 속에 남아 있다.",
        "",
        "아직 끝난 건 아니다."
    };

    screen.c =
    {
        "ENTER : 메인 메뉴로"
    };

    screen.d =
    {
        player.GetName(),
        "HP : " + std::to_string(player.GetHp()),
        "MP : " + std::to_string(player.GetMp())
    };

    ConsoleUI::DrawFullLayout(screen);
}


void GameManager::HandleStoryInput()
{
    InputManager::Wait();

    currentState = GameState::MainMenu;
}

void GameManager::RenderInventory()
{
    Inventory& inventory = context.GetInventory();
    Player& player = context.GetPlayer();

    std::vector<std::string> leftTop;
    std::vector<std::string> rightTop;
    std::vector<std::string> leftBottom;
    std::vector<std::string> rightBottom;

    leftTop.push_back("=== 인벤토리 ===");
    leftTop.push_back("");

    const auto& items = inventory.GetItems();

    if (items.empty())
    {
        leftTop.push_back("아이템이 없습니다.");
    }
    else
    {
        for (int i = 0; i < items.size(); i++)
        {
            leftTop.push_back(
                std::to_string(i + 1) +
                ". " +
                items[i].GetName()
            );
        }
    }

    rightTop.push_back("=== 플레이어 정보 ===");
    rightTop.push_back("");
    rightTop.push_back("이름 : " + player.GetName());

    rightTop.push_back(
        "HP : " +
        std::to_string(player.GetHp()) +
        "/" +
        std::to_string(player.GetMaxHp())
    );

    rightTop.push_back(
        "MP : " +
        std::to_string(player.GetMp()) +
        "/" +
        std::to_string(player.GetMaxMp())
    );

    leftBottom.push_back("1 ~ N : 아이템 선택");
    leftBottom.push_back("0 : 뒤로가기");

    rightBottom.push_back("인벤토리 메뉴");

    UIScreen screen;

    screen.a = leftTop;
    screen.b = rightTop;
    screen.c = leftBottom;
    screen.d = rightBottom;

    ConsoleUI::DrawFullLayout(screen);
}


void GameManager::HandleInventoryInput()
{
    Inventory& inventory = context.GetInventory();

    int itemCount =
        static_cast<int>(
            inventory.GetItems().size()
            );

    int choice =
        InputManager::InputInMassegeToRange(
            "선택 : ",
            0,
            itemCount
        );

    // 뒤로가기
    if (choice == 0)
    {
        currentState = GameState::MainMenu;
        return;
    }

    int index = choice - 1;

    auto& items = inventory.GetItems();

    if (index >= 0 && index < items.size())
    {
        ConsoleUI::PrintMessage(
            items[index].GetName() +
            " 선택됨"
        );
    }
}



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
#include "AnsiPlayer.h"



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

    std::vector<std::string> playerStatus;

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
        ConsoleUI::Redtest();
   

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
    ConsoleUI::ClearScreen();

    ConsoleUI::DrawCutSceneScreen(
        {

            "중간 보스 사진",


        },
        {
            "중간 보스 왈"
        }
        );

    InputManager::Wait();

    InputManager::Wait();

    bool middleBossWin = StartMiddleBossBattle();

    if (!middleBossWin)
    {
        GameOver();
        context.SetGameRunning(false);
        return;
    }

    ConsoleUI::DrawCutSceneScreen(
        {

            "보스 사진",


        },
        {
            "보스 왈"
        }
        );

    InputManager::Wait();


    bool finalBossWin = StartFinalBossBattle();

    if (!finalBossWin)
    {
        GameOver();
        context.SetGameRunning(false);
        return;
    }

    Ending();

    currentState = GameState::MainMenu;
}


void GameManager::HandleStoryInput()
{
    InputManager::Wait();

    StartStoryBattleFlow();

    if (context.IsGameRunning())
    {
        currentState = GameState::MainMenu;
    }
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
    int choice = InputManager::InputInMassegeToRange("선택: ", 0, 2);

    if (choice == 0)
    {
        currentState = GameState::Exit;
        return;
    }

    bool confirm = ShowCharacterPreview(choice);

    if (!confirm)
    {
        return; // 다시 선택 화면으로
    }

    if (choice == 1)
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

bool GameManager::ShowCharacterPreview(int choice)
{
    UIScreen screen;

    if (choice == 1)
    {
        screen.a = ConsoleUI::PrintJinWhiteImage();

        screen.b =
        {
            "[ 진태식 ]",
            "",
            "무술: 유도",
            "",
            "마약유통을 잡기위해 두식이파에 잠입한 비밀경찰",
            "의리와 책임을 중시한다.",
            "",
 
        };
    }
    else
    {
        screen.a = ConsoleUI::PrintRyuWhiteImage();

        screen.b =
        {
            "[ 류노스케 ]",
            "",
            "무술: 가라데",
            "",
            "냉철한 야쿠자 후계자.",
            "",
   
        };
    }

    screen.c =
    {
        "",
        "이 캐릭터를 선택하시겠습니까?",
        "",
        "1. 예",
        "2. 아니오"
    };

    screen.d =
    {
        "선택: "
    };

    ConsoleUI::DrawFullLayout(screen);

    int confirm = InputManager::InputInMassegeToRange("", 1, 2);

    return confirm == 1;
}




void GameManager::RenderCharacterSelect()
{
    UIScreen screen;

    Jin jin;
    Ryu ryu;

    if (selectedCharacterIndex == 0)
    {
        screen.a = ConsoleUI::PrintJinBlackImage();
    }
    else
    {
        screen.a = ConsoleUI::PrintRyuBlackImage();
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
    std::vector<int> displayToRealIndex;

    int displayIndex = 1;

    const auto& all = shop.GetProducts();

    // ===== 무기 =====
    productLines.push_back("[ 무기 ]");

    auto weapons = shop.GetProductsByCategory(ShopCategory::Weapon);

    for (const Item& item : weapons)
    {
        const StatBonus& b = item.GetStatBonus();

        std::string line =
            std::to_string(displayIndex) + ". " +
            item.GetName() + " | " +
            std::to_string(item.GetPrice()) + "G | " +
            "ATK+" + std::to_string(b.att);

        productLines.push_back(line);

        for (int i = 0; i < all.size(); i++)
        {
            if (all[i].GetName() == item.GetName())
            {
                displayToRealIndex.push_back(i);
                break;
            }
        }

        displayIndex++;
    }

    productLines.push_back("");

    // ===== 방어구 =====
    productLines.push_back("[ 방어구 ]");

    auto armors = shop.GetProductsByCategory(ShopCategory::Armor);

    for (const Item& item : armors)
    {
        const StatBonus& b = item.GetStatBonus();

        std::string line =
            std::to_string(displayIndex) + ". " +
            item.GetName() + " | " +
            std::to_string(item.GetPrice()) + "G | " +
            "DEF+" + std::to_string(b.def);

        productLines.push_back(line);

        for (int i = 0; i < all.size(); i++)
        {
            if (all[i].GetName() == item.GetName())
            {
                displayToRealIndex.push_back(i);
                break;
            }
        }

        displayIndex++;
    }

    productLines.push_back("");

    // ===== 소비 아이템 =====
    productLines.push_back("[ 소비아이템 ]");

    auto consumables = shop.GetProductsByCategory(ShopCategory::Consumable);

    for (const Item& item : consumables)
    {
        const StatBonus& b = item.GetStatBonus();

        std::string line =
            std::to_string(displayIndex) + ". " +
            item.GetName() + " | " +
            std::to_string(item.GetPrice()) + "G | " +
            "HP+" + std::to_string(b.hp) +
            " MP+" + std::to_string(b.mp);

        productLines.push_back(line);

        for (int i = 0; i < all.size(); i++)
        {
            if (all[i].GetName() == item.GetName())
            {
                displayToRealIndex.push_back(i);
                break;
            }
        }

        displayIndex++;
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

    shopIndexMap = displayToRealIndex; 
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
        if (shopIndexMap.empty())
        {
            AddLog("상품이 없습니다.");
            break;
        }

        int index = InputManager::InputInMassegeToRange(
            "구매할 상품 번호: ",
            1,
            shopIndexMap.size()
        ) - 1;

        int realIndex = shopIndexMap[index];

        int quantity =
            InputManager::InputInMassegeToRange(
                "수량: ",
                1,
                99
            );

        if (shop.BuyItem(realIndex, quantity, context))
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
        Inventory& inventory = context.GetInventory();

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
        "레벨 : " + std::to_string(player.GetLevel()),
        "",

        "HP   : " +
            std::to_string(player.GetHp()) + " / " +
            std::to_string(player.GetMaxHp()),

        "MP   : " +
            std::to_string(player.GetMp()) + " / " +
            std::to_string(player.GetMaxMp()),

        "EXP  : " +
            std::to_string(player.GetExp()) + " / " +
            std::to_string(player.GetMaxExp()),

        "",
        "ATK  : " + std::to_string(player.GetAttack()),
        "DEF  : " + std::to_string(player.GetDefense()),
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





void GameManager::RenderInventory()
{
    UIScreen screen;

    Player& player = context.GetPlayer();
    Inventory& inventory = context.GetInventory();

    const auto& items = inventory.GetItems();

    std::vector<std::string> itemLines;

    for (int i = 0; i < items.size(); i++)
    {
        const Item& item = items[i];
        const StatBonus& b = item.GetStatBonus();

        int sellPrice = shop.GetSellPrice(item);

        std::string line =

            std::to_string(i + 1) + ". " +
            item.GetName() + " | " +
            std::to_string(sellPrice) + "G | ";

        if (item.GetType() == ItemType::Equipment)
        {
            if (item.GetEquipmentType() == EquipmentType::Weapon)
            {
                line += "ATK+" + std::to_string(b.att);
            }
            else
            {
                line += "DEF+" + std::to_string(b.def);
            }
        }
        else
        {
            line +=
                "HP+" + std::to_string(b.hp) +
                " MP+" + std::to_string(b.mp);
        }

        if (item.IsEquipped())
        {
            line += " [장착중]";
        }

        itemLines.push_back(line);
    }

    screen.a = AnsiPlayer::LoadLines(
        R"(C:\asd\testred\ascii_output.txt)"
    );

    screen.b = itemLines;

    screen.c =
    {
        "1 ~ N : 사용 / 장착",
        "0 : 뒤로가기"
    };

    screen.d =
    {
        "이름 : " + player.GetName(),
        "Gold : " + std::to_string(player.GetGold()),
        "",
        "아이템 수 : " +
        std::to_string(items.size())
    };

    ConsoleUI::DrawFullLayout(screen);
}



void GameManager::HandleInventoryInput()
{
    Inventory& inventory = context.GetInventory();

    auto& items = inventory.GetItems();

    if (items.empty())
    {
        AddLog("인벤토리가 비어 있습니다.");

        InputManager::Wait();

        currentState = GameState::MainMenu;

        return;
    }

    int choice =
        InputManager::InputInMassegeToRange(
            "선택: ",
            0,
            items.size()
        );

    if (choice == 0)
    {
        currentState = GameState::MainMenu;
        return;
    }

    int index = choice - 1;

    std::string itemName = items[index].GetName();
    ItemType type = items[index].GetType();

    if (type == ItemType::Equipment)
    {
        inventory.EquipItem(index, context);

        AddLog(itemName + " 장착 완료");
    }
    else
    {
        inventory.UseItem(index, context);

        AddLog(itemName + " 사용 완료");
    }
}




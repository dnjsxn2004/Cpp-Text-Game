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

using namespace std;


GameManager::GameManager()
    : context(),
    shop(),
    loadSuccess(false),
    isWin(false),
    playerLevelUp(false)
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
        ConsoleUI::PrintStartScreen();
        TitleFlow();

        if (context.IsGameOver())
        {
            GameOver();


            Initialize();
        }
    }
}


void GameManager::Initialize()
{
    context.SetGameRunning(true);
    context.SetGameOver(false);

    loadSuccess = false;
    isWin = false;
    playerLevelUp = false;
}


void GameManager::TitleFlow()
{
    PlayOpeningCutscenes();

    SelectCharacter();

    if (!context.IsGameRunning())
    {
        return;
    }

    if (!context.HasPlayer())
    {
        ConsoleUI::PrintMessage("플레이어 생성에 실패했습니다.");
        context.SetGameOver(true);
        return;
    }

    MainLoop();
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


void GameManager::SelectCharacter()
{
    ConsoleUI::ClearScreen();

    ConsoleUI::ShowJinRyuIntroAnimation();

    while (context.IsGameRunning())
    {
        ConsoleUI::ClearScreen();

        // 캐릭터 선택 화면은 반복 출력
        ConsoleUI::ShowCharacterIntro();

        int choice = InputManager::InputInMassegeToRange("선택: ", 0, 2);

        switch (choice)
        {
        case 1:
            context.SetPlayer(new Jin());
            ConsoleUI::PrintMessage("진태식을 선택했습니다.");
            InputManager::Wait();
            return;

        case 2:
            context.SetPlayer(new Ryu());
            ConsoleUI::PrintMessage("류노스케를 선택했습니다.");
            InputManager::Wait();
            return;

        case 0:
            context.SetGameRunning(false);
            return;

        default:
            ConsoleUI::PrintMessage("잘못된 입력입니다.");
            break;
        }
    }
}



void GameManager::MainLoop()
{
    while (context.IsGameRunning() && !context.IsGameOver())
    {
        std::vector<std::string> cutSceneLines = {
            "",
            "",
            "                 [ 거점 ]",
            "",
            "        아직 렌더링 이미지가 없습니다.",
            "",
            "        이후 이 영역에는",
            "        아스키 렌더링 컷신이 들어갑니다."
        };

        std::vector<std::string> logLines = {
            "메인 메뉴에 진입했습니다.",
            "행동을 선택하세요."
        };

        std::vector<std::string> choiceLines = {
            "1. 전투",
            "2. 상점",
            "3. 인벤토리",
            "4. 상태 보기",
            "5. 스토리 진행",
            "0. 게임 종료"
        };

        ConsoleUI::DrawGameScreen(
            cutSceneLines,
            logLines,
            context.GetPlayer(),
            choiceLines
        );

        int choice = InputManager::InputInMassegeToRange("선택: ", 0, 5);

        ProcessMainMenu(choice);

        if (isWin)
        {
            return;
        }
    }
}


void GameManager::ProcessMainMenu(int choice)
{
    switch (choice)
    {
    case 1:
        StartNormalBattle();
        break;

    case 2:
        OpenShop();
        break;

    case 3:
        OpenInventory();
        break;

    case 4:
        ShowPlayerStatus();
        break;

    case 5:
        StartStoryBattleFlow();
        break;

    case 0:
        context.SetGameRunning(false);
        break;

    default:
        ConsoleUI::PrintMessage("잘못된 입력입니다.");
        break;
    }
}



void GameManager::StartNormalBattle()
{
    if (!context.HasPlayer())
    {
        ConsoleUI::PrintMessage("플레이어가 없습니다. 전투를 시작할 수 없습니다.");
        context.SetGameOver(true);
        return;
    }

    Monster monster = SpawnRandomMonster(context);
    context.SetMonster(monster);

    Battle battle(context);
    bool battleResult = battle.RunBattle();

    if (!battleResult)
    {
        context.SetGameOver(true);
        context.SetGameRunning(false);
    }
    InputManager::Wait();
}

void GameManager::OpenShop()
{
    while (context.IsGameRunning() && !context.IsGameOver())
    {
        ConsoleUI::PrintLine();
        cout << "상점" << endl;
        ConsoleUI::PrintLine();

        cout << "1. 구매" << endl;
        cout << "2. 판매" << endl;
        cout << "0. 나가기" << endl;

        ConsoleUI::PrintLine();

        int choice = InputManager::InputInMassegeToRange("선택: ", 0, 2);

        if (choice == 0)
        {
            return;
        }

        if (choice == 1)
        {
            const vector<Item>& products = shop.GetProducts();

            if (products.empty())
            {
                ConsoleUI::PrintMessage("상점에 상품이 없습니다.");
                InputManager::Wait();
                continue;
            }

            ConsoleUI::PrintShopItems(products);
            std::cout << "0. 취소" << endl;

            int itemChoice = InputManager::InputInMassegeToRange(
                "구매할 상품 번호: ",
                0,
                static_cast<int>(products.size())
            );

            if (itemChoice == 0)
            {
                continue;
            }

            int quantity = InputManager::InputInMassegeToRange("구매 수량: ", 1, 99);

            bool success = shop.BuyItem(itemChoice - 1, quantity, context);

            if (success)
            {
                ConsoleUI::PrintPurchaseSuccess(products[itemChoice - 1]);
            }
            else
            {
                ConsoleUI::PrintMessage("구매에 실패했습니다. 골드가 부족하거나 잘못된 상품입니다.");
            }

            InputManager::Wait();
        }
        else if (choice == 2)
        {
            vector<int> sellableIndices = context.GetInventory().GetSellableItemIndices();

            if (sellableIndices.empty())
            {
                ConsoleUI::PrintMessage("판매 가능한 아이템이 없습니다.");
                InputManager::Wait();
                continue;
            }

            const vector<Item>& items = context.GetInventory().GetItems();

            ConsoleUI::PrintLine();
            cout << "판매 가능 아이템" << endl;
            ConsoleUI::PrintLine();

            for (int i = 0; i < static_cast<int>(sellableIndices.size()); ++i)
            {
                int realIndex = sellableIndices[i];
                const Item& item = items[realIndex];

                cout << i + 1 << ". "
                    << item.GetName()
                    << " x" << item.GetQuantity()
                    << " / 판매가: " << shop.GetSellPrice(item)
                    << endl;
            }

            cout << "0. 취소" << endl;

            int itemChoice = InputManager::InputInMassegeToRange(
                "판매할 아이템 번호: ",
                0,
                static_cast<int>(sellableIndices.size())
            );

            if (itemChoice == 0)
            {
                continue;
            }

            int realIndex = sellableIndices[itemChoice - 1];
            int maxQuantity = items[realIndex].GetQuantity();

            int quantity = InputManager::InputInMassegeToRange("판매 수량: ", 1, maxQuantity);

            bool success = shop.SellItem(realIndex, quantity, context);

            if (success)
            {
                ConsoleUI::PrintMessage("아이템을 판매했습니다.");
            }
            else
            {
                ConsoleUI::PrintMessage("판매에 실패했습니다.");
            }

            InputManager::Wait();
        }
    }
}

void GameManager::OpenInventory()
{
    while (context.IsGameRunning() && !context.IsGameOver())
    {
        const vector<Item>& items = context.GetInventory().GetItems();

        ConsoleUI::PrintLine();
        cout << "인벤토리" << endl;
        ConsoleUI::PrintLine();

        if (items.empty())
        {
            cout << "아이템이 없습니다." << endl;
            ConsoleUI::PrintLine();
            InputManager::Wait();
            return;
        }

        ConsoleUI::PrintItemListWithIndex(items);
        cout << "0. 나가기" << endl;

        int itemChoice = InputManager::InputInMassegeToRange(
            "아이템 선택: ",
            0,
            static_cast<int>(items.size())
        );

        if (itemChoice == 0)
        {
            return;
        }

        int itemIndex = itemChoice - 1;
        const Item& selectedItem = items[itemIndex];

        if (selectedItem.GetType() == ItemType::Consumable)
        {
            bool success = context.GetInventory().UseItem(itemIndex, context);

            if (success)
            {
                ConsoleUI::PrintMessage("아이템을 사용했습니다.");
            }
            else
            {
                ConsoleUI::PrintMessage("아이템 사용에 실패했습니다.");
            }
        }
        else if (selectedItem.GetType() == ItemType::Equipment)
        {
            bool success = context.GetInventory().EquipItem(itemIndex, context);

            if (success)
            {
                ConsoleUI::PrintMessage("장비를 장착했습니다.");
            }
            else
            {
                ConsoleUI::PrintMessage("장비 장착에 실패했습니다.");
            }
        }
        else
        {
            ConsoleUI::PrintMessage("퀘스트 아이템은 여기서 사용할 수 없습니다.");
        }

        InputManager::Wait();
    }
}


void GameManager::ShowPlayerStatus()
{
    if (!context.HasPlayer())
    {
        ConsoleUI::PrintMessage("플레이어 정보가 없습니다.");
        InputManager::Wait();
        return;
    }

    ConsoleUI::PrintPlayerStatus(context.GetPlayer());
    InputManager::Wait();
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
    bool result = battle.RunBattle();

    InputManager::Wait();
    return result;
}

bool GameManager::StartFinalBossBattle()
{
    ConsoleUI::PrintMessage("최종보스전이 시작됩니다.");
    InputManager::Wait();

    Monster finalBoss = SpawnFinalBoss(context);
    context.SetMonster(finalBoss);

    Battle battle(context);
    bool result = battle.RunBattle();


    InputManager::Wait();
    return result;
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

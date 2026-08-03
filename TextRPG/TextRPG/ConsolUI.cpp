#include <iostream>
#include <string>
#include <thread>    // sleep_for처럼 실행 흐름을 잠시 멈추는 기능을 사용하기 위한 헤더
#include <chrono>    // milliseconds, seconds처럼 시간 단위를 사용하기 위한 헤더
#include <conio.h> // _kbhit() 및 _getch() 사용 (Windows 콘솔 입력 감지용)
#include <windows.h> // Windows API 헤더 추가
#include <cstdlib> // system("cls") 사용
#include <stdlib.h>
#include <vector>
#include <iomanip>
#include <sstream>

#include "Jin.h"
#include "Ryu.h"
#include "Gang.h"
#include "StatBonus.h"
#include "GameContext.h"
#include "Player.h"
#include "Monster.h"
#include "ConsolUI.h"
#include "Inventory.h"
#include "Item.h"
#include "Shop.h"
#include "Battle.h"
#include "GameContext.h"
#include "InputManager.h"



using namespace std;

ConsoleUI::ConsoleUI()
{
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);

    cursorInfo.bVisible = FALSE;

    SetConsoleCursorInfo(hConsole, &cursorInfo);
}

// ANSI 색상 이스케이프 코드 정의
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"
#define BOLD    "\033[1m"



void ConsoleUI::PrintTitleLine()
{
    char lineChar = '=';

    // TODO: 콘솔 너비 또는 원하는 출력 길이 값
    int lineLength = 178;

    // '=' 문자를 lineLength개 가진 문자열
    string line(lineLength, lineChar);

    // TODO: cout.write에 문자열 데이터와 길이 전달
    cout.write(line.c_str(), lineLength);

    // TODO: 줄바꿈 출력
    cout << endl;

    /*cout.flush();*/
}
std::vector<std::string>
ConsoleUI::SplitLines(const std::string& text)
{
    std::vector<std::string> lines;

    std::stringstream ss(text);

    std::string line;

    while (std::getline(ss, line))
    {
        lines.push_back(line);
    }

    return lines;

}

void ConsoleUI::PrintLine()
{
    cout << "========================================================================================================" << endl;
}

void ConsoleUI::PrintTitle(const std::string& title)
{
	cout << "                            [ " << title << " ]                     " << endl;
}

void ConsoleUI::PrintMessage(const std::string& message)
{
	cout << message << endl;
}

void ConsoleUI::PrintMessageValue(const std::string& message, int value)
{
	cout << message << ": " << value << endl;
}

void ConsoleUI::PrintError(const std::string& message)
{
	cout  << message << endl;
}

void ConsoleUI::PrintSuccess(const std::string& message)
{
	cout  << message << endl;
}



// 메인 메뉴
void ConsoleUI::PrintMainMenu()
{
	PrintLine();
	PrintTitle("메인 메뉴");
	PrintLine();

    cout << endl;
    PrintMessage("1. 일반 전투");
    PrintMessage("2. 메인 스토리");
    PrintMessage("3. 상태창");
    PrintMessage("4. 인벤토리");
    PrintMessage("5. 상점");
    PrintMessage("0. 게임 종료");
    cout << endl;

	PrintLine();
}

void ConsoleUI::PrintPlayerStatus(Player& player)
{
    PrintLine();
    PrintTitle("플레이어 상태");
    PrintLine();

    PrintMessage("이름 : " + player.GetName());
    PrintMessage("HP : " + std::to_string(player.GetHp()));
    PrintMessage("MP : " + std::to_string(player.GetMp()));

    PrintLine();
}

void ConsoleUI::SwitchMainMenu()
{
    PrintMainMenu();
    int choice = InputManager::InputInMassegeToRange("메인 메뉴에서 선택하세요: ", 0, 5);
    switch (choice)
    {
    case 1:
        // 일반 전투
        break;
    case 2:
        // 메인 스토리
        break;
    case 3:
        // 상태창
        break;
    case 4:
        // 인벤토리
        break;
    case 5:
        // 상점
        break;
    case 0:
        // 게임 종료
        break;
    default:
        PrintError("잘못된 입력입니다. 다시 선택해주세요.");
        break;
    }
}



// 상태창
void ConsoleUI::PrintPlayerStatusEveryTime(GameContext& context)
{
    Player& player = context.GetPlayer();
    cout << "레벨 : " << player.GetLevel() << " ( " << player.GetExp() << " / " << player.GetMaxExp() << " ) " <<
        "  HP : " << player.GetHp() << " / " << player.GetMaxHp() <<
        "  MP : " << player.GetMp() << " / " << player.GetMaxMp() <<
        endl;
}

void ConsoleUI::PrintStatus(GameContext& context, Battle& battle, StatBonus& equipBonus, StatBonus& potionBonus)
{
    Player& player = context.GetPlayer();
    Inventory& inventory = context.GetInventory();
    Item& item = context.GetItem();
    
    string weaponName = context.GetInventory().GetEquippedWeaponName();
    string armorName = context.GetInventory().GetEquippedArmorName();


    PrintLine();
    PrintTitle("플레이어 상태");
    PrintLine();

    cout << endl;
    cout << player.GetName() << endl;
    PrintLine();
    cout << "골드 : " << player.GetGold() << endl;
    cout << "레벨 : " << player.GetLevel() << endl;
    cout << "경험치 : " << player.GetExp() << " / " << player.GetMaxExp() << endl;
    cout << "HP : " << player.GetHp() << " / " << player.GetMaxHp() << endl;
    cout << "MP : " << player.GetMp() << " / " << player.GetMaxMp() << endl;
    cout << "공격력 : " << player.GetMeleeDamage(equipBonus, potionBonus) << endl;
    cout << "방어력 : " << player.GetTrueDefense(equipBonus, potionBonus) << endl;
    PrintLine();

    cout << endl;
    PrintMessage("내가 장착하고 있는 장비 아이템");
    PrintLine();

    cout << "장착 중인 무기: " << weaponName << endl;
    cout << "장착 중인 방어구: " << armorName << endl;
    PrintLine();

    cout << endl;
    PrintMessage("전투 기록");
    PrintLine();

    cout << "전투에서 이긴 횟수 : "<< battle.GetMonsterKillCount() << endl;

    //캐릭 이름, 골드, 레벨, 경험치, HP, MP, 공격력, 방어력
    // 내가 장착하고 있는 (장비) 아이템
    // 몬스터 처치 수

    PrintLine();
}



// 아이템, 인벤토리
string ConsoleUI::ItemTypeToString(const Item& item)
{
    switch (item.GetType())
    {
    case ItemType::Equipment:
        return "장비";  // 무기& 방어구 장비 타입

    case ItemType::Consumable:
        return "소비";

    default:
        return "알 수 없음";
    
    }
}

void ConsoleUI::PrintItemListWithIndex(const vector<Item>& items)
{
    for (int i = 0; i < items.size(); i++)
    {
        cout << i + 1 << ". " << items[i].GetName() << endl;
    }
}

void ConsoleUI::PrintInventoryMenu()
{
    PrintLine();
    PrintTitle("인벤토리 확인");
    PrintLine();

    PrintMessage("1. 내가 가진 전체 아이템 보기");
    PrintMessage("2. 장비 아이템");
    PrintMessage("3. 소비 아이템");
    //PrintMessage("4. 퀘스트 아이템");
    PrintMessage("0. 뒤로가기");

    PrintLine();
};

void ConsoleUI::PrintItem(const Item& item)
{
    PrintLine();
    cout << item.GetName() << endl;
    PrintLine();
    cout << "가격 : " << item.GetPrice() << endl;
    cout << "타입 : " << ItemTypeToString(item) << endl;
    PrintLine();
}

void ConsoleUI::PrintItemName(const Item& item)
{
    cout << item.GetName() << endl;
}

void ConsoleUI::PrintAllItems(GameContext& context)
{
    Inventory& inventory = context.GetInventory();
    const vector<Item>& items = inventory.GetItems();

    if (items.empty())
    {
        PrintMessage("인벤토리가 비어 있습니다.");
        return;
    }

    PrintLine();
    PrintTitle("내가 가진 전체 아이템");
    PrintLine();

    PrintItemListWithIndex(items);

    PrintLine();
}

void ConsoleUI::PrintEquipmentItems(GameContext& context)
{
    Inventory& inventory = context.GetInventory();
    vector<Item> equipmentItems = inventory.GetItemsByType(ItemType::Equipment);

    if (equipmentItems.empty())
    {
        PrintMessage("장비 아이템이 없습니다.");
        return;
    }


    PrintLine();
    PrintTitle("장비 아이템 목록");
    PrintLine();

    PrintItemListWithIndex(equipmentItems);

}

void ConsoleUI::PrintConsumableItems(GameContext& context)
{
    Inventory& inventory = context.GetInventory();
    vector<Item> consumableItems = inventory.GetItemsByType(ItemType::Consumable);

    if (consumableItems.empty())
    {
        PrintMessage("소비 아이템이 없습니다.");
        return;
    }

    PrintLine();
    PrintTitle("소비 아이템 목록");
    PrintLine();

    PrintItemListWithIndex(consumableItems);
}

void ConsoleUI::SwitchInventory(GameContext& context)
{
    while (true)
    {
        PrintInventoryMenu();

        int choice = InputManager::InputInMassegeToRange("인벤토리에서 선택하세요: ",0, 3);
        
        switch (choice)
        {
        case 1:
            PrintAllItems(context);
            break;

        case 2:
            PrintEquipmentItems(context);
            break;

        case 3:
            PrintConsumableItems(context);
            break;

        case 0:
            return;
        }
    }
}



// 상점
void ConsoleUI::PrintShopMenu()
{
    PrintLine();
    PrintTitle("상점");
    PrintLine();

    PrintMessage("1. 아이템 구매");
    PrintMessage("2. 아이템 판매");
    PrintMessage("0. 뒤로가기");
    PrintLine();
}

void ConsoleUI::SwitchShopMenu(GameContext& context, Shop& shop)
{
    while (true)
    {
        PrintShopMenu();

        PrintMessage("현재 골드 : " + to_string(context.GetPlayer().GetGold()) + "G");
        int choice = InputManager::InputInMassegeToRange("상점에서 선택하세요: ", 0, 2);
        switch (choice)
        {
        case 1:
            // 구매 카테고리 메뉴로 이동
            SwitchPurchaseCategoryMenu(context, shop);
            break;
        case 2:
            // 판매 메뉴로 이동
            SwitchSellMenu(context, shop);
            break;
        case 0:
            return;
        }
    }
}

void ConsoleUI::PrintShopItems(const vector<Item>& shopItems)
{
    if (shopItems.empty())
    {
        PrintMessage("상점에 판매 중인 아이템이 없습니다.");
        return;
    }
    
    PrintLine();
    PrintTitle("상점");
    PrintLine();

	PrintItemListWithIndex(shopItems);
}

void ConsoleUI::PrintPurchaseSuccess(const Item& item)
{
	PrintItem(item);

    PrintMessage("상점에서 아이템 구매 했습니다.");
}

void ConsoleUI::SwitchPurchaseCategoryMenu(GameContext& context, Shop& shop)
{
    while (true)
    {
        PrintLine();
        PrintTitle("아이템 구매");
        PrintLine();

        PrintMessage("1. 소비 아이템");
        PrintMessage("2. 무기");
        PrintMessage("3. 방어구");
        PrintMessage("0. 뒤로가기");

        PrintLine();

        int choice =
            InputManager::InputInMassegeToRange("구매할 종류를 선택하세요: ", 0, 3);

        switch (choice)
        {
        case 1:
            PurchaseByCategory(context, ShopCategory::Consumable);
            break;

        case 2:
            PurchaseByCategory(context, ShopCategory::Weapon);
            break;

        case 3:
            PurchaseByCategory(context, ShopCategory::Armor);
            break;

        case 0:
            return;
        }
    }
}

void ConsoleUI::PurchaseByCategory(GameContext& context, Shop& shop, ShopCategory category) {

    //선택한 카테고리의 상품만 가져오기
    std::vector<Item> shopItems = shop.GetProductsByCategory(category);

    //카테고리 제목 출력
    PrintLine();

    switch (category) {
    case ShopCategory::Consumable:
        PrintTitle("소비 아이템 상점");
        break;

    case ShopCategory::Weapon:
        PrintTitle("무기 상점");
        break;

    case ShopCategory::Armor:
        PrintTitle("방어구 상점");
        break;
    }

    PrintLine();

    //상품이 없는 경우
    if (shopItems.empty()) {
        PrintMessage(
            "상점에 판매 중인 아이템이 없습니다."
        );
        return;
    }

    //상품 목록 출력
    for (int i = 0; i < static_cast<int>(shopItems.size()); i++) {
        const Item& item = shopItems[i];
        const StatBonus& bonus = item.GetStatBonus();

        string message = to_string(i + 1) + ". " + item.GetName() + "/ 가격: " + to_string(item.GetPrice()) + "G";

        if (bonus.hp != 0) {
            message += " / HP " + to_string(bonus.hp);
        }

        if (bonus.mp != 0) {
            message += " / MP " + to_string(bonus.mp);
        }

        if (bonus.att != 0) {
            message += " / 공격력 " + to_string(bonus.att);
        }

        if (bonus.def != 0) {
            message += " / 방어력 " + to_string(bonus.def);
        }

        if (bonus.str != 0) {
            message += " / 힘 " + to_string(bonus.str);
        }

        if (bonus.dex != 0) {
            message += " / 민첩 " + to_string(bonus.dex);
        }

        if (bonus.intel != 0) {
            message += " / 지능 " + to_string(bonus.intel);
        }

        if (bonus.luk != 0) {
            message += " / 행운 " + to_string(bonus.luk);
        }

        PrintMessage(message);
    }

    PrintMessage("0. 뒤로가기");
    PrintLine();

    int selectedNumber = InputManager::InputInMassegeToRange("구매할 아이템 번호를 선택하세요: ", 0, static_cast<int>(shopItems.size()));

    if (selectedNumber == 0) {
        return;
    }
    //UI번호는 1부터시작 벡터 인덱스는 0부터 시작
    int categoryIndex = selectedNumber - 1;

    int quantity = 1;

    //소비 아이템은 여러 개 구매 가능
    if (category == ShopCategory::Consumable) {
        quantity = InputManager::InputInMassegeToRange("구매 수량을 입력하세요.", 1, 99);
    }

    bool success = shop.BuyItemByCategory(category, categoryIndex, quantity, context);

    if (success) {
        PrintPurchaseSuccess(shopItems[categoryIndex]);

        PrintMessage("구매 수량: " + to_string(quantity));

        PrintMessage("남은 골드: " + to_string(context.GetPlayer().GetGold()) + "G");
    }

    else {
        PrintMessage("아이템 구매에 실패했습니다.");
    }
}

void ConsoleUI::SwitchSellMenu(GameContext& context, Shop& shop) {

    Inventory& inventory = context.GetInventory();

    //전체 인벤토리 원본
    const std::vector<Item>& allItems = inventory.GetItems();

    //판매 가능한 아이템들의 실제 인덱스
    std::vector<int> sellableIndices = inventory.GetSellableItemIndices();

    PrintLine();
    PrintTitle("아이템 판매");
    PrintLine();

    //현재 골드 출력
    PrintMessage("현재 골드 : " + std::to_string(context.GetPlayer().GetGold()) + "G");

    PrintLine();

    if (sellableIndices.empty()) {
        PrintMessage("판매할 수 있는 아이템이 없습니다.");
        InputManager::Wait();
        return;
    }

    //판매 가능한 아이템 출력
    for (int i = 0; i < static_cast<int>(sellableIndices.size()); i++) {
        int realIndex = sellableIndices[i];

        const Item& item = allItems[realIndex];

        string message = to_string(i + 1) + ". " + item.GetName() + " / 보유 수량: " + to_string(item.GetQuantity()) + " / 판매가: " + to_string(shop.GetSellPrice(item)) + "G";

        PrintMessage(message);
    }

    PrintMessage("0. 뒤로가기");
    PrintLine();

    int selectedNumber = InputManager::InputInMassegeToRange("판매할 아이템 번호를 선택하세요: ", 0, static_cast<int>(sellableIndices.size()));

    if (selectedNumber == 0) {
        return;
    }

    //화면 번호를 실제 인벤토리 인덱스로 변환
    int realIndex = sellableIndices[selectedNumber - 1];

    const Item& selectedItem = allItems[realIndex];

    int quantity = 1;

    //소비 아이템은 수량 선택 가능
    if (selectedItem.GetType() == ItemType::Consumable) {
        quantity = InputManager::InputInMassegeToRange("판매 수량을 입력하세요: ", 1, selectedItem.GetQuantity());
    }

    //SellItem에서 벡터 아이템이 삭제될 수 있으므로 판매 전에 출력할 정보 저장
    std::string itemName = selectedItem.GetName();

    int totalSellPrice = shop.GetSellPrice(selectedItem) * quantity;

    bool success = shop.SellItem(realIndex, quantity, context);

    if (success) {
        PrintMessage(itemName + "을(를) 판매했습니다.");

        PrintMessage("판매 수량: " + to_string(quantity));

        PrintMessage("획득 골드: " + to_string(totalSellPrice) + "G");

        PrintMessage("현재 골드: " + to_string(context.GetPlayer().GetGold()) + "G");
    }

    else {
        PrintMessage(
            "아이템 판매에 실패했습니다"
        );
    }
    InputManager::Wait();
}



// 일반 전투
void ConsoleUI::PrintNormalBattleMenu(const GameContext& context)
{
    PrintLine();
    PrintTitle("일반 전투");
    PrintLine();

    PrintLine();
    PrintTitle("플레이어 정보");
    PrintLine();

    // TODO: 플레이어 이름 출력 코드
    // TODO: 플레이어 레벨 출력 코드
    // TODO: 플레이어 현재체력 / 최대체력 출력 코드

    PrintLine();
    PrintTitle("몬스터 정보");
    PrintLine();

    // TODO: 몬스터 이름 출력 코드
    // TODO: 몬스터 레벨 출력 코드
    // TODO: 몬스터 현재체력 / 최대체력 출력 코드
    // 
    //메인메뉴에서 출력해서 주석처리 하겠습니다.
    //PrintLine();
    //PrintMessage("1. 일반 공격");
    //PrintMessage("2. 스킬 사용");
   // PrintMessage("3. 아이템 사용");
   // PrintMessage("4. 도망 가기");
   // PrintMessage("0. 뒤로가기");
	//PrintLine();
}

void ConsoleUI::PrintBattlePlayerInfo(GameContext& context)
{
    Player& player = context.GetPlayer();

    PrintLine();
    PrintTitle("플레이어 정보");
    PrintLine();

    PrintMessage("이름 : " + player.GetName());
    PrintMessage("레벨 : " + std::to_string(player.GetLevel()));
    PrintMessage(
        "HP : " +
        std::to_string(player.GetHp()) +
        " / " +
        std::to_string(player.GetMaxHp())
    );
}

void ConsoleUI::PrintBattleMonsterInfo(GameContext& context)
{
    const Monster& monster = context.GetMonster();

    PrintLine();
    PrintTitle("몬스터 정보");
    PrintLine();

    PrintMessage("이름 : " + monster.GetName());
   // PrintMessage("레벨 : " + std::to_string(monster.GetLevel()));
    PrintMessage(
        "HP : " +
        std::to_string(monster.GetHp()) +
        " / " +
        std::to_string(monster.GetMaxHp())
    );
}

void ConsoleUI::PrintBattleActionMenu()
{
    PrintLine();
    PrintMessage("1. 일반 공격");
    PrintMessage("2. 스킬 사용");
    PrintMessage("3. 아이템 사용");
    PrintMessage("4. 도망 가기");
    PrintLine();
}

void ConsoleUI::BattleReward(GameContext& context)
{
    Player& player = context.GetPlayer();
    Monster& monster = context.GetMonster();

    PrintLine();
    PrintTitle("전투 보상");
    PrintLine();

    PrintMessage(
        "획득 경험치: " +
        std::to_string(monster.GetExpReward())
    );

    PrintMessage(
        "획득 골드: " +
        std::to_string(monster.GetGoldReward())
    );

    PrintMessage(
        "현재 경험치: " +
        std::to_string(player.GetExp())
    );

    PrintMessage(
        "현재 골드: " +
        std::to_string(player.GetGold())
    );

    PrintLine();
}



void ConsoleUI::PrintNormalDiceResult(int diceValue) const
{
    cout << "주사위를 굴렸습니다." << endl;
    cout << "주사위 결과: " << diceValue << endl;
}

void ConsoleUI::PrintPlayerMeleeAttackResult(const std::string& playerName, const std::string& monsterName, int diceNumber, int damage, bool isStunSuccess, Battle& battle, GameContext& player, GameContext& monster) const
{
    Player& p = player.GetPlayer();
    Monster& m = monster.GetMonster();
    Battle& b = battle;
    cout << p.GetName() << "(이) 가 " << m.GetName() << "에게 일반 공격을 시도했습니다." << endl;
    cout << "주사위 결과: " << b.GetLastDiceValue() << endl;
    cout << m.GetName() << "에게 " << damage << "의 피해를 입혔습니다." << endl;
    if (isStunSuccess)
    {
        cout << m.GetName() << "이 기절 상태가 되었습니다!" << endl;
    }
}

void ConsoleUI::PrintPlayerSkillAttackResult(const std::string& playerName, const std::string& monsterName, const std::string& skillName, int diceNumber, int damage, bool isStunSuccess, Battle& battle, GameContext& player, GameContext& monster) const
{
    Player& p = player.GetPlayer();
    Monster& m = monster.GetMonster();
    Battle& b = battle;
    cout << p.GetName() << "(이) 가 " << m.GetName() << "에게 스킬 공격을 시도했습니다." << endl;
    cout << "주사위 결과: " << b.GetLastDiceValue() << endl;
    cout << m.GetName() << "에게 " << damage << "의 피해를 입혔습니다." << endl;

    if (isStunSuccess)
    {
        cout << m.GetName() << "이 기절 상태가 되었습니다!" << endl;
    }
}

void ConsoleUI::PrintPlayerRunawayResult(bool IsSuccess)
{
    PrintMessage("도주를 시도했습니다. ");
    if (IsSuccess)
    {
        PrintMessage("도주를 성공했습니다. ");
    }
    else
    {
        PrintMessage("도주를 실패했습니다. ");
        PrintMessage("전투가 계속 진행됩니다. ");
    }
}

void ConsoleUI::PrintPlayerTurnCount(int TurnCount)
{ 
    PrintLine();
    PrintTitle("플레이어 턴");
    PrintLine();

	cout << TurnCount << "턴째 입니다." << endl;
    PrintLine();
}

void ConsoleUI::PrintBattleResult(GameContext& player, GameContext& monster, Battle& battle)
{
    Player& p = player.GetPlayer();
    Monster& m = monster.GetMonster();
    Battle& b = battle;

    if (b.CheckBattleResult(player, monster))
    {
        cout << m.GetName() << "을(를) 처치했습니다." << endl;
        cout << "전투에서 승리했습니다." << endl;
    }
    else
    {
        cout << p.GetName() << "체력이 모두 소진되었습니다." << endl;
        cout << "전투에서 패배했습니다." << endl;
    }
}

void ConsoleUI::PrintJobSelectMenu()
{
	PrintLine();
	PrintTitle("캐릭터 선택");
	PrintLine();
	cout << "1. 진태식 유도" << endl;
	cout << "2. 류노스케 가라데" << endl;
	PrintLine();
}



void ConsoleUI::PrintGameOver()
{
	PrintLine();
	PrintTitle("게임 패배");
	PrintLine();
	cout << "캐릭터가 사망했습니다." << endl;
	PrintLine();
}

void ConsoleUI::ClearScreen()
{
	// 콘솔 핸들 가져오기
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	// 화면을 지우고 커서를 (0, 0)으로 이동
	COORD coord = { 0, 0 };
	DWORD written;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	DWORD size = csbi.dwSize.X * csbi.dwSize.Y;
	FillConsoleOutputCharacter(hConsole, ' ', size, coord, &written);
	FillConsoleOutputAttribute(hConsole, csbi.wAttributes, size, coord, &written);
	SetConsoleCursorPosition(hConsole, coord);
}

void ConsoleUI::MoveCursor(int x, int y)
{
	// 콘솔 핸들 가져오기
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	// 커서 위치 설정
	COORD coord = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
	SetConsoleCursorPosition(hConsole, coord);
}

// 입력 버퍼에 남아 있는 키 입력을 모두 제거하는 함수
void ConsoleUI::ClearInputBuffer()
{
    while (_kbhit())
    {
        _getch();
    }
}

// 시작 화면 출력 함수
void ConsoleUI::PrintStartScreen()
{
    int frame = 0;

    while (!_kbhit())
    {
        system("cls");

        // TODO: 현재 프레임 번호 변수 선언
        int currentFrame = frame % 5;

        // 상단 구분선
        
        PrintTitleLine();
        

        // TODO: 현재 프레임에 사용할 색상 문자열 변수 선언
        const char* waveColor = WHITE;

        // TODO: 프레임 번호에 따른 색상 선택 분기
        switch (currentFrame)
        {
        case 0:
            waveColor = WHITE;
            break;

        case 1:
            waveColor = MAGENTA;
            break;

        case 2:
            waveColor = BLUE;
            break;

        case 3:
            waveColor = GREEN;
            break;

        case 4:
            waveColor = RED;
            break;
        }

       
        cout << waveColor << BOLD;

        // TODO: 프레임별 파도 ASCII ART 출력 분기
        switch (currentFrame)
        {
        case 0:
            cout << R"(
                                                                                                    
                                                                                                    
                                                                          .--..                     
                                                                         :#**++=-::.                
                                                                        :#*=-=++++=-:..             
                                                                       -#*-...+++++++=-::.          
                                                                      -#*+=::=+++++++++==--:.       
                                                                     :#*++++++++++=-:.:=====--:.    
                                                                    :#**++++=-:-===:..:====------:  
                                                                   :**+==++=: ..====--====:.:-----  
                                                                  .**=...=+==::==+++++===-.:-----   
                                                                  +*+=..:=+++====++++===--------.   
                                                                  =++++=+++++==-:-=====---:.---.    
                                                                   .:-========: ..====---:.:--.     
                                                                      .:-=====-::====--------.      
                                                                          .:-=======-----:.:.       
                                                                             ..-==-------.:.        
                                                                                 ..::-----.         
                                                                                      ...                                                                                                               
                                                                                                    
                                                                                                    

            )" << endl;
            break;

        case 1:
            cout << R"(
                                                     
                                               
                                                                           .:---::.                 
                                                                         -*#=:-######*+=-:.         
                                                                      .=#%##***###########*=.       
                                                                    .=%%#####+:.+########**+=:      
                                                                   =%%########**########*+=--=      
                                                                  *@%##########=::*###*+==-..=.     
                                                                 :%#****########****++====-.-=:     
                                                                 -#*+++++++++****++========-==-     
                                                                 .#+++=======--=======-=---====     
                                                                  **++=======. .-=====-=- .====.    
                                                                  =*++===--===--========-.-====.    
                                                                  :*++===: .-===========--====-     
                                                                   *+=:-==--=================:      
                                                                   :*-  :==================-.       
                                                                    .==-=================-:         
                                                                      .::--=========----:           
                                                                             ..::---::.             
                                                                                                    
                                                                                                    

            )" << endl;
            break;

        case 2:
            cout << R"(                                                                     
                                                                                                    
                                                                                                    
                                                                          -===-:.                   
                                                                        +%%@@@@%%%#+-.              
                                                                      .#*-#@@@@%%%*++==-.           
                                                                     :%%*%@@@%%%%*+=---===:.        
                                                                    :%@%%*#%@@%%*+=-.  -=====:      
                                                                   -%@%%=-#@@@%*+==-...--======-.   
                                                                  -%@%%%%%%%@%*+==-----------:-==.  
                                                                 :%%%@%%%++%%*+==-----------  .-=:  
                                                                .%%%%%%%+-#%*+=------.  :---..:-=.  
                                                                :%%%%%%%%%#*==-. .---:..:-------.   
                                                                 -****###*+=--:. .-------------.    
                                                                  .:::----==------------------.     
                                                                     .:--:::----------:  .---.      
                                                                        .::::---------:..:--.       
                                                                           ..::-::---------.        
                                                                              ...:.::----:          
                                                                                                    
                                                                                   
               
                                                                                                    
            )" << endl;
            break;

        case 3:
            cout << R"(
                                                                                                                                                                                                        
                                 
                                                                      .+**+++===---::...            
                                                                      #%%#**##############+=:       
                                                                     -@%=   +#######+--*##*++=:     
                                                                     #%#=..=*######=  :=#**+-=+=.   
                                                                    -@%#######**###*=-+##**= :=++:  
                                                                    #%%#####*:  -########*+-.-====  
                                                                   .@%######+  :=#######**+=-=====  
                                                                   +%%#+=*###*+*########*+===:===:  
                                                                   %%#: ..*######+-:-*#**+==- -==.  
                                                                  -%%#=.:+######*: .:+#**===:.==-   
                                                                  =%%############+--*#**+====-==:   
                                                                  :***++***************+=====-:=.   
                                                                    :==:.::-----=============:.-    
                                                                      :==----::..::-:::---===:::    
                                                                        :==----:::::::::::--=--     
                                                                               ..........:::      
                                                                                                    
                                                                                  
                  
                                                                                                    
            )" << endl;
            break;

        case 4:
            cout << R"(
                                                                                                    
                                                                                                    
                                                                              .=**=+##*++=-:.       
                                                                            :+%##+=*##########*=.   
                                                                          :*%%####*=-*########*+=:  
                                                                        :*%#######*=+#######**+===. 
                                                                       -%%##########+-=####*+==: -: 
                                                                      .%############==*#**+====..-- 
                                                                      :#*++++++*******+++======--== 
                                                                      .#*++=========+======-=---===.
                                                                       **++=======  .=====---: -===:
                                                                       =*++====-==-:-=======-..-===:
                                                                       .*++===. .-===========--===-.
                                                                        ++=-===:-================-. 
                                                                        :*-  -==================:.  
                                                                         :+---================-.    
                                                                           .:--==========-=--.      
                                                                                ..::------:.        
                                                                                                    
                                                                                  
                  

            )" << endl;
            break;
        }

        cout << RESET; // 파도 색상 초기화

        // 3. 타이틀 로고 ASCII ART : 파도 (중앙 정렬)
        cout << RED << BOLD;

        cout << R"(
                                                                                                                        
                                                ~?]}{11[<.            .|xtx              <(uXXu(i           [rrrxrrrx                    
                                                [//|frvcXY{           'YUJ1            <YOmwZwbbp}          nkhkbkkkc                    
                                                }/f(  `-vYJj          `zYU{           +LQL{`    :]:         rkk                       
                                                [|/f    ?vcUl         ,vzz[           vJLt                  jdpZCLLx                     
                                                ?1)|    -rnv,         .xuv?           tYUu                  jppLuuux                     
                                                -}{<    /tj-          .jxxx           ;vXU>     x(+         rmZ               
                                                _->]1)))(}l            ffj+            :|zYUJCCJU}          )LLLLLLQt                    
                                                :I!!iiiI`              ><~I              ,~]1{]<'           !--------                    
                                                                                                                        
         )" << endl;

        cout << RESET;

        // 구분선
        
        PrintTitleLine();
        

        // 4. 게임 서사 문구
        cout << "\n           \"우리는 서로의 천국이자, 가장 잔인한 지옥이었다.\"\n\n";

        // 구분선
        
        PrintTitleLine();
        

        // 5. 시작 안내 문구
        cout << "                   >> 아무 키나 누르면 시작됩니다 <<\n";

        // 하단 구분선
        
        PrintTitleLine();
        

        // 프레임 증가 및 대기 (300ms 간격으로 파도가 출렁거림)
        frame++;
        this_thread::sleep_for(chrono::milliseconds(300));
    }

    ClearInputBuffer();
    system("cls");
}
/*
// 시스템 담당자 사용예시
int main()
{
    // 시작 화면 출력만 담당
    ConsoleUI::PrintStartScreen();

    // 입력 및 실행 로직 처리
    system("pause"); // 또는 _getch(); / cin.get();

    return 0;
}
*/




void ConsoleUI::PrintJinBlackImage()
{
    cout << R"( 
                  .                                         
                .:.            ..          .                
               .-:.            .......      .               
              .:.       ....  ..:::-:::::..  .              
              :.    ..:--=-:::=+***#*++++=-. ..             
             ..   ....:-==++++*######**++++:...             
             ..    ...::-==+**####******++=-:::             
             :-.  ...::--=+##%@%%%###***++=-:-=             
             :+:.  ..::-=++*%%#######***++==-=+             
              +==:..::----=+**+=+******++++**+=             
             .=+*+.   .....:---:---:...:::=#%+::.           
            : .*#:   .      ..-:..   ..::::*%++-:           
            . .*=       ..   =#*-:....::.:-=%+--.           
            .  *-......::::..=**++-::--=++*+#+:=.           
             . +=.::------:..=******++*****+#*+=            
             ..:-..:--==-:..:=*#**+****+++++*++.            
              ..-...:--=-:.::=*#**++***++===+=-             
                =.  .:---:...:-=-=++++++=-:-+.              
                -.   .:::.     .::***++=-::-=               
                :    ..::....::=+++++++=-----               
                .   .........-----=--==+=---.               
                 .  .. ..  ..::---:-::-+=-::                
                .:  .. .... .....:----:--:--:               
               . .   .    ..::-------::-::-:::              
             ... .      ...:---=====-::.::-..:-.            
         ......            ...:::::::..::-:.:::-:::..       
     ....   ..                     ..::--::.::::....:::..   
 ......                           ..:::::::.:..........::::.
 ....                            ..:::::::.:................
  .                            ....::::::..:.........=: ....
                               ....:::::..............    . 
                   .     .........::::::......... ....      
                          ...... ..::::..... ...            

)" << endl;
}

void ConsoleUI::PrintJinWhiteImage()
{
    cout << R"( 
@@@@@@@@@@@@@@@@#-.                        .+@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@%+:..           ......         :%@@@@@@@@@@@@@
@@@@@@@@@@@@@%=:.              ............   :#@@@@@@@@@@@@
@@@@@@@@@@@@@-..      ..:::....:-===+=-----:.  :@@@@@@@@@@@@
@@@@@@@@@@@@*..   ...:--===--=+*######**+++=:...*@@@@@@@@@@@
@@@@@@@@@@@@-.   ....::-=+++++*#######****++=:..=@@@@@@@@@@@
@@@@@@@@@@@@-.   ...:::--=++*##%%####*****++=:::=@@@@@@@@@@@
@@@@@@@@@@@@+-.  ...::--=+*##%@%%%####****++=:-=+@@@@@@@@@@@
@@@@@@@@@@@@*+:.....::--=+*#%%########***+++=--+#@@@@@@@@@@@
@@@@@@@@@@@@#+==:..::-----=+***++********++++*+*#@@@@@@@@@@@
@@@@@@@@@@@%%+***........::-===---=--:::::-=#%#+%%@@@@@@@@@@
@@@@@@@@@@%: -*#=   ..      ..::...   .::--:+%#++-#@@@@@@@@@
@@@@@@@@@@#  :*+        .    :+*-....  ....:-*%=-:#@@@@@@@@@
@@@@@@@@@@%. .#-..  ...:::...=*#+=-:::---=+++*%--=%@@@@@@@@@
@@@@@@@@@@@- .#-.::::::---::.-*#****+=++******%+++@@@@@@@@@@
@@@@@@@@@@@# .==.::-------:..-*#************+*#++#@@@@@@@@@@
@@@@@@@@@@@@=.:-..::-===-:..:=*#**++*****+++=++=*@@@@@@@@@@@
@@@@@@@@@@@@@=:=. .::----::::=+****+++**++=--=++%@@@@@@@@@@@
@@@@@@@@@@@@@@@=.  ..:---.   .::::-+++++==-:-+%@@@@@@@@@@@@@
@@@@@@@@@@@@@@@=.   ..:::.    ..--+#**++=--:-+%@@@@@@@@@@@@@
@@@@@@@@@@@@@@@=.  ....::....---++++++++==---=@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@#.  ..........:--:-----==++=--+@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@%:  .. ... ..:::-=----::-+=-::#@@@@@@@@@@@@@@
@@@@@@@@@@@@@@%::. ..  .... ......:----:--::=:#@@@@@@@@@@@@@
@@@@@@@@@@@@@%: ..  .    ...::--------::-::--.-#@@@@@@@@@@@@
@@@@@@@@@@@%*:  ..     ...::---==+===--:.:---.:-*%@@@@@@@@@@
@@@@@@@%#=:...           ....::::--:-:..::--:.::---=*%@@@@@@
@@@@#+-.   ..                 ........::---::.:::::..::=+#%@
#+-:..                             ..:::---:.::..:......:::-
.....                            ...::----::.:.............:
..                              ....:::::::.::.........::...
  .                            ....:::::::..:............  .
                 .       ...  .....::::::...............    
                  .      ..........:::--:...............    

)" << endl;
}



void ConsoleUI::PrintKangBlackImage()
{
    cout << R"( 
                                                            
                              ..:.                          
                             ...:.                          
                                                            
                              .                             
                           ...........                      
                        .......... .......                  
                         ..:::-==-.   .::.                  
                        .-=+++*###+:..::::.                 
                       .:=++**###%%*-..:...                 
                      .:--+*##%%#%%#*=:...                  
                  .   :-==+*######%%%*=..                   
                      ..:::-++*+=---==+-.                   
                     . ..:-:.=*+=-:-=-+=:  ....             
                     ...:-++:=%#+--=**#*-   ....            
                    ..-=+++=:-%#%***###*:      ..           
            .        .:-++=:.+%##******=       .            
             .       ...-=-..:+=#*****+:       .            
             ..       ...::..=+####***=  .......            
             ..        ......:-==++*+-   .:..::.            
             .....      .....:==+++=-    ..:.:...           
             ......       ..-=+**+++.    . . ......         
             .  ....        ..::=+*=.    . .. .:..          
                 ...      ...:-++**-:     . ....:..         
                         ..::-=++*+=.      ....  ...        
         .              .-:=+===+**:        ..    .:.       
      .:.        ...    .=+*##*=+*+..             .+-*-     
     :...     .. ..      :+##**++*:..       ..    .=:%%#.   
   .-:-::  .....     ..  .=******:.....     ....  .:-%%%%:  
  .-+:-:*.......   ..:    .*****-.....::      ..:...+%%%%%- 
 .:=#:::=..  .:.....-*     -***-.....:*-    . . ..:.-%%#%%%:
 .-=#+...    .. ...-=#=     +*-......*%+.   ......-=.=##%%%=
.::-=-.         ..=*+*#.    .-. . ..+%#*-. ....  ..::--*%#*.

)" << endl;
}

void ConsoleUI::PrintKangWhiteImage()
{
    cout << R"( 
*@@@@@@@@@@@@@@@@@@@@@@@%.    .::. =%@@@@@@@@@@@@@@@@@@@@@# 
@@@@@@@@@@@@@@@@@@@@@@@@-    ..::.  =@@@@@@@@@@@@@@@@@@@@@@:
@@@@@@@@@@@@@@@@@@@@@@%*:           :*%@@@@@@@@@@@@@@@@@@@@:
@@@@@@@@@@@@@@@@@@@@#-        .       .+@@@@@@@@@@@@@@@@@@@:
@@@@@@@@@@@@@@@@@@@#.      ...........  -%@@@@@@@@@@@@@@@@@:
@@@@@@@@@@@@@@@@@@+     .......... ......:%@@@@@@@@@@@@@@@@:
@@@@@@@@@@@@@@@@@%.      .::::-+=-.  ..::.*@@@@@@@@@@@@@@@@:
@@@@@@@@@@@@@@@@@=      :=++***#%#+:..:::.-@@@@@@@@@@@@@@@@:
@@@@@@@@@@@@@@@@#     .:-=+**###%%%*-..:.. +@@@@@@@@@@@@@@@:
@@@@@@@@@@@@@@@%: .   ::-=+#%%%%%%%#*=: .  .%@@@@@@@@@@@@@@:
@@@@@@@@@@@@@@@=  .  .:-=++*#%%##%%%#*=..   -@@@@@@@@@@@@@@:
@@@@@@@@@@@@@@-       ..:::-+**+=--=+++:.    -%@@@@@@@@@@@@:
@@@@@@@@@@@@@+         ..:-::+*+=:.---+=. ....-%@@@@@@@@@@@:
@@@@@@@@@@@@#.      ....:=++:+%#*==+*##*:   ...:#@@@@@@@@@@:
@@@@@@@@@@@#:       .:=++++=:+%#%#**###*.      .:@@@@@@@@@@:
@@@@@@@@@@@#:        .:=++=::*%##*#****-       :+@@@@@@@@@@:
@@@@@@@@@@@@=.       ..:-=:..:++##*****.       =@@@@@@@@@@@:
@@@@@@@@@@@@%.        ...::.:++#####**-  ......*@@@@@@@@@@@:
@@@@@@@@@@@@#..        .... .-===+**+:   .::::.-%@@@@@@@@@@:
@@@@@@@@@@@%: ....      ....:-=+**+=:    ..:.:..=%@@@@@@@@@:
@@@@@@@@@@#- ......       ..-=+*+++=.    . . ....*#%@@@@@@@:
@@@@@@@@@%+. .  ....       ...:-=**-.    . .. .:.:%#@@@@@@@:
@@@@@@@@@*:      ..       ...:=+**+-.     . ....:.=%@@@@@@@:
@@@@@@@@*=.             ...-:-++**+=.      ....  ..#@@@@@@@:
@@@@@@@#-:              :-:=*+++*#*.        ..   .::*@@@@@@:
@@@@@%=:.        ..     .++*##*+*#+..             :+=%@@@@@:
@@@@*::..     .. .       -+###*+*+...       ..    :==%%%@@@:
@@@+---::  .....     ..  .+*****+......     ....  ..*%%%%@@:
@@==+:-:*... ...  ...:    :*****:.....-.       :....*@%%%%@:
@=:=#-::-.. ..:.....-*     =***:.....-*:    . ...::.=%%#%%%.
*.-+#+...    .  ..:=+%-    .+*:  ...:%%=.   .:....-=:+#%%%%.
.::--:.         ..=*=**     ::     .+#**:. ....   .::--*#*= 

)" << endl;
}



void ConsoleUI::PrintRyuBlackImage()
{
    cout << R"( 
                          .. ...:.   ...                    
                   ..    .     ....::. ..                   
                  ..                 ... ..                 
                ..                     ..  :                
               .       .::::::-+===-.  ... ..               
               .    .:=+*#####%%%%%%#*=.   ..               
              ..   :==++*##%%%%%%%@%%%%#+.  .               
                  .:==++*#%%%%%%%%%%%%%%#=. .               
               . .::-=+*##%%%%%%%%%%%%%%#+...               
               ..++--=+++*##%%##%%%%%###%%=..               
               .:%*. .   .:=+**==:..:-==+@*.                
             ...-%=..:::..  :+#+::::-=+++%*:-:              
             ...=#.  .::=--.:#%#*=-::+==*%#*+:              
              : +*-=--=++*+--#%%%%***##%%%@=#-              
              . =%-=****#*-:-#@%%%%%%%%%%%%*#.              
              ...+::=****+::+#@%%%%%%%%#####+               
               :.--.:=+++=.:-*%###%%%##*+*#*.               
                 .=...-++:   .---%%%%##++=.                 
                  =:..:===-:-**%%%%%%%#*#:                  
                  :::-.:---::=+=+*###%##*                   
                   ::=:.-:.:-=+*++++###+.                   
                    --:.::...::-+*****+:                    
                    -.::.:-=+*######*+*-                    
                 .. -  ..:-=+**###*++##- .                  
                .-  :      ...:::-=*###= ::                 
             ..:::           .:-=+*####+ .--:.              
          .:.  . .           .:=+*####*-....: .::..         
    .....-.             ....:-=+*#####+.. .   . .-.....     
.:::.  .:. .          ...-:.:--=+##**+.. ..    . .:.=:..::. 
:.      . .          .-:.-+=--==+##*+:...... .  . . .... .. 
       . .           .++--##*+==+###=.:..:::.::.:. : .:::.  
  .    . .            :++=+***+-=**+:. .....:::...  :.::..  

)" << endl;
}

void ConsoleUI::PrintRyuWhiteImage()
{
    cout << R"( 
%%%%%%%%%%%%%%%%%%%+::    ..  ...::......-%%%%%%%%%%%%%%%%%%
@@@@@@@@@@@@@@@@@@*..           .. ..::....-*@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@#=.                   ... .:+@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@+:                        ..  :+@@@@@@@@@@@@@
@@@@@@@@@@@@@%-.       ..::::::-====-:.  ... ..#@@@@@@@@@@@@
@@@@@@@@@@@@@#.     .:-+**#***#%%%%%%##=:.   .:*@@@@@@@@@@@@
@@@@@@@@@@@@@%:    :-==+*###%%%%%%%@@%%%#*-.   =@@@@@@@@@@@@
@@@@@@@@@@@@@@:.  .:==++*##%%%%%%%%%%%%%%%#=. .*@@@@@@@@@@@@
@@@@@@@@@@@@@%.   ::-=+*###%%%@%%%%%%%%%%%#+. .#@@@@@@@@@@@@
@@@@@@@@@@@@@@-..-=--=+**##%%%%%#%%@%%%%%%%#-..%@@@@@@@@@@@@
@@@@@@@@@@@@@@+.-#*:::::-=++####*#**++++++#%#.=@@@@@@@@@@@@@
@@@@@@@@@@@@@@%:+%+ .:::.  .:=+*=-:..-=++=+%%.*@@@@@@@@@@@@@
@@@@@@@@@@@@@+--+%:........  :*%*-::..:--=+%%:%#@@@@@@@@@@@@
@@@@@@@@@@@@%...**.. .::-+==.-#%%#*=--=+=+*#@+#-%@@@@@@@@@@@
@@@@@@@@@@@@@-..%+-====++**+--#@%%%#**##%%%%@+*#@@@@@@@@@@@@
@@@@@@@@@@@@@* .##-+****#*+-:-#@%%%%%%%%%%%%@#*%@@@@@@@@@@@@
@@@@@@@@@@@@@@:.:*:-=*****=.:+#@%%%%%%%%%######%@@@@@@@@@@@@
@@@@@@@@@@@@@@#- =:.:=+**+-::+#%%%%#%%%%#*++##%@@@@@@@@@@@@@
@@@@@@@@@@@@@@@%+*-..:-++=.   :--:*%%%%#*++##%@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@+...:=+=:..:-+##%%%%%##**%@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@*::-.-=====+%*#%%%%%%%###@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@%-:-:.:......:---==*###*#@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@#---.:-::-=+***###**#**@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@%=:-...:..:::-=+****++#@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@+ = .-.:-=+*#%%%###*+*#::%@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@*  =   ..::=+**###*+=*##: -%@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@+:  :       ...:::--+####= .=%@@@@@@@@@@@@@@
@@@@@@@@@@@@%#+=:.            ..:-=*#####= .:-+*#@@@@@@@@@@@
@@@@@@@@#*+:. :...            .-=+**####*-....-..:=+*%@@@@@@
@@@%#+-.-:.             ... ..:-+**#####+.. ... ...-:.:=*#%@
#+-:...-...             .::..:-=++*####*..  ..   .  ::.::.:=
:.    .. .           .::.:==::--=+*##**:.:.....   .  . ::.  
      ...            .==::+#+====+*##*- :..::..::..:  . ....
.     . .             -*+=+%%#*+=+#%%*:.....::.:-: :. .:.::-

)" << endl;
}

//캐릭터 소개 애니메이션
void ConsoleUI::ShowJinRyuIntroAnimation()
{
    PrintJinBlackImage();
    this_thread::sleep_for(chrono::milliseconds(1000));
    ClearScreen();
    PrintJinWhiteImage();
    this_thread::sleep_for(chrono::milliseconds(1000));
    ClearScreen();
    PrintRyuBlackImage();
    this_thread::sleep_for(chrono::milliseconds(1000));
    ClearScreen();
    PrintRyuWhiteImage();
    this_thread::sleep_for(chrono::milliseconds(1000));
	ClearScreen();
}



void ConsoleUI::PrintJinLogo()
{
    cout << R"( 
                                  .@@@@@@@@@@%                                  
                                 .@@@@@@@@@@@@%..                               
                                .@@@@@@@@@@@@@@@                                
                               .@@+@@@@@@@@@@:@@@ .                             
                                @@@@@@@@@@@@@@@@  .                             
                                @@@@@@@@@@@@@@@@. .                             
                               .@@@@@@@@@@@@@@@@@               .               
                                 .@@@@@@@@@@@@*.                                
                                  .@@@@@@@@@@+                    .             
                              .:@@@@@.... .@@@@@*...                            
                       ..%@@@@@+.  .@@@@@@@@..  .*@@@@@+....                    
                     .@#       .@  .@      .@. .@.     ..@@.                    
            . .     .@.         .@   @     @. .@          @@                    
                  .=@.          ..-   =   - . -   .        @@:.                 
                  @@      .        .. .@ -   .       .      :@#                 
              -@% .      .% .         =   +  .        @  .     .@@. .           
            :@@*. .     .*..         @   #          .#--  .     .@@@            
            -@@  .@.  .@. :.      .@. .@  ..        .@  ++   .#   @@  .         
            :@@ .    ..   :.          .              @.  ...... . @@.           
           . @@        *.   -@.  @. .@           .@@   .@.       .@:  .         
             .@%        %:  =. .@  .@            ..@  .@. .     .@@             
              %@. .      :*.-:.@   @.              @  @.   .    @@. .           
              .@@      + ...-@. %%##%%%#######%%# *@.   ..     .@#              
               .@+ .@%.. .@                .         -*. ..@#..@@               
               .@...+.#       .@    @.     *%   .@       .@+...=.  .            
                      .@        @.+.         @..-       .@..                    
                    ..@@@.      .#             @      .++@+. .                  
                    .@@. .@@@@@@@ =@@@@@@@@@@@. @@@@@@#  .@=     .              
                   .@@    .                               .@@                   
                  .@@.                #. @. .              .@@  .               
                .=@*                .*. . %.                .@@.                
               ..@@          .@@@@.@%#     +@@-%@@@.         .@@ .              
                 .@@            .*@..      . .@.   .        .@@                 
                  .@@.         .@#.           .@+          :@#                  
                    -:::::::::::.  .            ::::::::::::. .                 
)" << endl;
}

void ConsoleUI::PrintKangLogo()
{
    cout << R"( 
                                 . .@. ..       .@%.  .                         
                              .@-  %.: ..:*= .     -@. .                        
                           .*@  =%#@+.-        :.    .#.  .                     
                           @.       .=.@..--@    ..   .@                        
                         .#.   .:= .+*%. ...#@@    .    @ .                     
                         *#   .. .%.          .=    .   :@.                     
                        .@   .  =#             @      .  #.                     
                        *.  -   @ .            .@      #  @                     
                      .@  .   -@ ...@@@. . .@@@..-%   .   @.=  .                
                      =. +   .#@ .@*@%-     =%@.@ .@.  .    @* .                
                    .@==    @@ @.                  @.@.   %.  @..               
                    @.    @:- @.:                 ..@%..%@=.   -@..             
                  *@  :@.   =   @      .@.@.     .@ .# -     .@ .-..            
               ..-. %   -   . . -@       .       @-  : #       :.@              
               ..@ @   @   @  *  @@     . .     @.          #   =@              
               ..@#   @   =   *   %@@         @@@  ...  @    =  @  ..           
                 @*.+    @    .   @@ :@*. .#@. @.  . .   @    @@.               
               . .@*   @     @    @+           @  .  @    #.   .@  .            
                 @   --     @. @  @..          @  .   ..    +    @. ..          
                =%  @.     +. #   @@.         .@       =     @    @.            
               .#. @     @.  @   +. @%#.   .#@@=#  .  ...     @  ..+            
               ..@@.   -.  ..   *+   @.     :@  @. .. . .      @@  @            
              .@  @  %      @.    ...   @@-   .@.   %.     @    @..@.           
              *%= .@ @   . -..     :*.. @+    @ .    .#    ..  #-.*@.           
             .@   @.@...   @     .  .=.@.    #        **   .  .%@   @.          
            ..*     #@%.   =..       .@.    @          @   @.%@.    @.          
             @...    .@.#%  @.       @.    @         .-#  :*@       .@          
             @        @   .@.@  .   @.    @          -+=@%  @       .@          
            :+    .   #.    +%     @.   .@  .      .       .*  .    .=- .       
            @.         @    :     @    .+                  @.        .@    .    
            @     -.   @:      ..@     *              .   :@          @.        
           *%      %   .@      .@.   .%                   @  .        ## .      
          .@.. ..   =  @*@.   *@    ..  . .              @+@.         .@.       
         . @        .. @.@@@@@@%#+:@.%@@@-@@@...-+#%@@@@@@ @.          @        
          .+          .@ @@@@@@@@@@=+@@.@-@@@.+@@@@@@@@@@@ @           =.       
         .#.          %. @@@@@@@@-@@@@@.@=@@@.@@@*@@@@@@@@ .#         ..%.      
)" << endl;
}

void ConsoleUI::PrintRyuLogo()
{
     cout << R"( 
                                 *@@-@@@.@@:%@:@@.                              
                               .%@@@@@@@@@@@@@@@@@- .                           
                                @@@.            @@@.                            
                               .@@@            .@@=.                            
                                .@ @@@.    .:@@* @  .                           
                              .@*@ ..@+    .@@+ .@.%.                           
                               %.@.             :#:. .                          
                                @.-             @.=                             
                                  @             @                               
                                   @    ..    .@                                
                                  .@#*       @.@.                               
                                .@ @  .@@@@@   @ @                              
                              .**..@          :=**@:.    .                      
                         .:@#   . . @        .-.:.*   %@.  ..                   
               .     .@@        . . .@.+   -.*-....       .@#                   
                   -@.           -.  .@    .@.....           .@                 
                 .@.     # .      .  ..*  ......         -     -=               
                 .. ...   ..       . . =*@.%...         =    :. *               
                .@  . .:  @ .       .  -@ #%..          - ..    .@              
                =        . #          .# .**.          @..  .    #...           
               .:    .  .  #..       @....*.         @+ #+ .@.    @             
               : ..     .  .        @ .:-@         .*+. #...%     ...           
               @         .  ...... @ ..+@        .@...% .= @       =.           
               @       .#@                .+@@@@   ..     .@       %            
               @       :#...:@=                 +.  .        .     :            
               ..            +    #@.   .       =.   .            *             
               .@           ..   @    .@*..  .   @    @           @             
                ::        ..    @ .        :@=    =              @              
                .@             =         %@%   :@@@    .       ...              
                  .@..   @    @-%@@@-           .@@  ...-=*%@@@.                
                        *@:  @@%=-                      .%                      
                          @@.# ...      ..    .   .   .@@                       
               .          @@@@@@@@@@@.@@@@@@@@@@@@@@@@@@@          .            
                          @@@@@@@@:@@@@@-@@@@@@@#@@@@@@@@          .            
)" << endl;
}

void ConsoleUI::ShowJinIntro()
{
    PrintLine();
    PrintTitle("진태식");
    PrintLine();
    
    PrintJinWhiteImage();

    PrintLine();
    PrintMessage("무술: 유도");
    PrintLine();
    PrintMessage("조직의 행동대장으로, 의리와 책임을 무엇보다 중요하게 여기는 인물.");
    PrintMessage("친구와 연인 사이에서 끝내 손을 놓지 못한 비극의 남자.");
    PrintMessage("플레이 스타일: 스킬 공격 특화형으로, 강력한 유도 기술을 활용해 높은 폭발 피해를 입힌다.");
    PrintLine();
}

void ConsoleUI::ShowKangIntro()
{
    PrintLine();
    PrintTitle("강사라");
    PrintLine();

    PrintKangWhiteImage();

    PrintLine();
    PrintMessage("무술: 태권도");
    PrintLine();
    PrintMessage("불법 지하 의원을 운영하는 의사이자, 생존을 위해 스스로 악역을 선택한 여자.");
    PrintMessage("냉혹한 현실 속에서도 두 친구를 살리려는 마음을 버리지 않는다.");
    PrintMessage("플레이 스타일: 기본 공격 특화형으로, 빠르고 연속적인 태권도 공격을 통해 안정적으로 높은 피해를 준다.");
    PrintLine();
}

void ConsoleUI::ShowRyuIntro()
{
    PrintLine();
    PrintTitle("류노스케");
    PrintLine();

    PrintRyuWhiteImage();

    PrintLine();
    PrintMessage("무술: 가라데");
    PrintLine();
    PrintMessage("야쿠자 후계자로서 조직과 우정 사이에서 갈등하는 냉철한 파이터.");
    PrintMessage("누구보다 친구를 아끼지만, 운명은 그를 적으로 만들었다.");
    PrintMessage("플레이 스타일: 밸런스형으로, 기본 공격과 스킬 모두 안정적인 성능을 갖춘 올라운드 캐릭터이다.");
    PrintLine();
}

// 캐릭터 소개 화면
void ConsoleUI::ShowCharacterIntro()
{
    PrintLine();
    PrintTitle("캐릭터 선택");
    PrintLine();
    cout << "1. 진태식: 유도 선수 출신, 강력한 근접 공격과 방어 능력을 가진 캐릭터." << endl;
    cout << "2. 류노스케: 가라데 선수 출신, 균형 잡힌 능력과 특수 기술을 가진 캐릭터." << endl;
    cout << "0. 게임 종료" << endl;
    PrintLine();
}



// Cut Scene
void ConsoleUI::ShowCutScene1()
{
    // TODO: 컷씬 제목 출력 코드

    // TODO: 어린 시절 배경 설명 문구 출력 코드

    // TODO: 진태식, 강사라, 류노스케 등장 문구 출력 코드

    // TODO: 세 인물이 함께 노는 장면 묘사 문구 출력 코드

    // TODO: 다음 장면으로 넘어가기 위한 안내 문구 출력 코드
}

void ConsoleUI::ShowCutScene2()
{
    // TODO: 컷씬 제목 출력 코드

    // TODO: 어두운 시술실 배경 설명 문구 출력 코드

    // TODO: 의사 강사라 등장 이미지 또는 로고 출력 코드

    // TODO: 강사라가 불법 시술을 진행하는 상황 설명 문구 출력 코드

    // TODO: 긴장감 있는 대사 또는 내레이션 출력 코드

    // TODO: 다음 장면으로 넘어가기 위한 안내 문구 출력 코드
}

void ConsoleUI::ShowCutScene3()
{
    // TODO: 컷씬 제목 출력 코드

    // TODO: 병원 또는 시술실 배경 설명 문구 출력 코드

    // TODO: 의사가 된 강사라 등장 이미지 또는 로고 출력 코드

    // TODO: 진태식이 치료를 받으러 온 상황 설명 문구 출력 코드

    // TODO: 류노스케가 치료를 받으러 온 상황 설명 문구 출력 코드

    // TODO: 진태식과 류노스케가 서로 마주치는 장면 설명 문구 출력 코드

    // TODO: 강사라가 두 사람을 알아보거나 반응하는 대사 출력 코드

    // TODO: 다음 장면으로 넘어가기 위한 안내 문구 출력 코드
}

void ConsoleUI::ShowCutScene4()
{
    // TODO: 컷씬 제목 출력 코드

    // TODO: 도박장 분위기 설명 문구 출력 코드

    // TODO: 류노스케의 긴장감 있는 대사 출력 코드

    // TODO: 진태식의 도발 또는 반응 대사 출력 코드

    // TODO: 승부가 본격적으로 진행되는 상황 설명 문구 출력 코드

    // TODO: 승패가 갈릴 듯한 긴장감 연출 문구 출력 코드

    // TODO: 다음 장면으로 넘어가기 위한 안내 문구 출력 코드
}

void ConsoleUI::ShowCutScene5()
{
    // TODO: 컷씬 제목 출력 코드

    // TODO: 도박판이 뒤집히는 상황 설명 문구 출력 코드

    // TODO: 주변 인물들이 동요하는 분위기 설명 문구 출력 코드

    // TODO: 류노스케의 분노 또는 도발 대사 출력 코드

    // TODO: 진태식의 반격 또는 결심 대사 출력 코드

    // TODO: 류노스케와 진태식의 큰 싸움이 시작되는 장면 설명 문구 출력 코드

    // TODO: 클라이맥스 긴장감을 강조하는 연출 문구 출력 코드

    // TODO: 다음 장면으로 넘어가기 위한 안내 문구 출력 코드
}

void ConsoleUI::ShowCutScene6()
{
    // TODO: 컷씬 제목 출력 코드

    // TODO: 싸움이 끝난 뒤의 어두운 분위기 설명 문구 출력 코드

    // TODO: 류노스케가 승리한 상황 설명 문구 출력 코드

    // TODO: 진태식이 패배하고 쓰러진 상태 설명 문구 출력 코드

    // TODO: 류노스케의 차가운 대사 출력 코드

    // TODO: 진태식의 마지막 반응 또는 독백 출력 코드

    // TODO: 진태식이 결정적인 위기에 빠지는 장면 설명 문구 출력 코드

    // TODO: 다음 장면으로 넘어가기 위한 안내 문구 출력 코드
}

void ConsoleUI::ShowCutScene7()
{
    // TODO: 컷씬 제목 출력 코드

    // TODO: 싸움 이후의 정적 분위기 설명 문구 출력 코드

    // TODO: 진태식이 치명상을 입은 상황 설명 문구 출력 코드

    // TODO: 진태식의 고통스러운 반응 대사 출력 코드

    // TODO: 류노스케 또는 주변 인물의 반응 대사 출력 코드

    // TODO: 진태식이 쓰러지거나 버티는 장면 설명 문구 출력 코드

    // TODO: 다음 장면으로 넘어가기 위한 안내 문구 출력 코드
}

void ConsoleUI::PrintCutScene1Image()
{
    cout << R"(
                                                                
         .....                                              
      .::     ...                                           
      :          .:           ...                           
     ..  .   .  .-:        .:.   ....              .:...... 
      : .:-.:-:.:          -....    ..            -=.       
      - ::---::::          .=-:...  ..            ==:.      
:::-=-.--:::::.:           :=-==-:::.             --=-.  .  
--::+=.::::..:-.         .:-+---::::.             .--=-..   
-:-:**..... ---=-:    :+**#**-:.::=++*=:         .:=-:....  
-::=**:..:..===++==.-****+*+#-...=******=      =***+..:::.  
:-:+**-...:.===*=+++**+===+***::-*****+**=   .-#***=: :::.  
.:-+*+=...::=+-+-++=+**+===+**+.+**+*+=*+*. :*##+**+- .:: ..
.:++**+ ...-==::=++*=*==:-=-=++=+*+-+==+++=.****=++*=. .  -.
.-=++++:   -=-.:***#=-=++:-----=+++-=-==++=+**+*-=*++-   :-.
 ..::--- .:--:.=****+=**++::::--=++----====*#+*=--=++=. .=- 
.:::----:-:::::=+***+=++*+=:..::-:-:::----****=-.::-==..=--.
--. ...::....::+**++=--++*+---. ....:.:::+****=. .:::----==.
........ ...:...:=+==-.==*+=::=..-=+****++++**+.:=-...-====.
 ....:==+=-::....:--=**+=++=:.-- .+**++**++---:--:..:-::-==.
.:.....-=-.....:=+*****++===-..:  =+++++++++---:::::::-====.
::......:.....-+++++++==-----::: .--==++++++:-:.:::::=====-.
 ..     .----===-------:::  .....:----====++:.......----::. 
    .:::----:::-----:......... ...... .:---. ......... .... 
     ....:..:::::.        ....           ...        .-.     
       . ........                                           

    )" << endl;
}

void ConsoleUI::PrintCutScene2Image()
{
    cout << R"(
                      ....    .     ....:..                     
                .......   .  ....:::..:--.                  
                   .:-:..  ..   .:..::::-=:                 
                    ........  :-=++=-....:::                
                    ......:...-====++-:.  :::               
                   ....  ... .::+::-=+=-. .::.              
                  ...::  .   ..=#*++**==:-: ::              
                 .:-=-:. .   ::-=*+***==++- .:.             
                  -----. .   .:.:=+***+=:.  ..:             
                .---=:-. .    ..:+***===...  .:             
                .-+=-=+. .     .:---:-+=... . .:            
                 :=*+=- .. .      .-=++=... ...::           
                 :-==. ..  .      .:-=--+-:. .:.::          
                .-==. ..    .    .:...=#%#*++++=::.         
                 ::.  .   ...   .-. .+#**#*###%%%+:.        
            .:    .. .:.        :. -###*#*#*#####%=:        
           .:----==:--.      .....=######*****###%*:        
           ::==+++++-... ....   .+**####+#*+**###%*:        
          ::-==++**-..   ...    =***#*++**+**####%+:        
         :::-==+++-.. .   .    :***+*-:+#***###*##*:.       
         -:-==+**+-::   . .    +**+**-:*+=+##%%###-.:.      
         :--==+*+=---  .      :*#*+*+=**++*****##*. ..      
          ..::----+-.         +#*++****=+**#####*-.. .      
               .--=:         .##*++***-==+++*#*++.. .       
              :-:-.   .      :##*+***=+=+**==+##: ...       
             :--:.           -##++**+**#*+**+==-  ...       
            :--.             =***#*####++++*++-   .   .     
          .--:              .....-*##***==--:.    .   -:    
       ..:-:.            .-=:....  =**++=-.                 
   .:--:..             .-=+++-     .+=:.:=                  
   ::.                 ::::::.     ..  ..:                  

    )" << endl;
}

void ConsoleUI::PrintCutScene3Image()
{
    cout << R"(
                                                .:::.           
            .::::::.                     .::... :::.        
          .::......::-.                 ::.    ....::       
         :-:........  .-               .-:..........-.      
         -..... .. .. .-     ::::::.    =--::...:. .::      
         -. .:.   .. .:-    ::...:.::   -.:::::.:....-.     
 ::...  :-  .::. ..:..-    ::  .:::.:.  .=-::::.:..:-::-::::
 ....:::.:::::::....::-    -   .::.: -   --:::........ :..:.
     .   :::.........-.   .:  .::::. -    .-:..:.....  ...  
    .    :..........-.    -.  .::::  -     .::..::-..  ..   
        .:... .=::...    .-. . ..:...:-           -   ...   
   .    ...   ..-.     :+=:.   .:-:+++++=.        .:  ...   
   .    ....    .:    .+=-.  ...-:.*+*+++=        .:  .     
   .    ... .   :.    ====.  .:...:***+++*.        - ....   
        .. .   .:    .+===. .:-...:+*+++=+-        -  ..    
        .      -     =+=-=::.==:..:*++++=++        .: .     
              .:    .+==-+----=...:+=====++.        :..     
              -.    :+==-=+====...:==+===+*:         -.     
 .           -      -===-++====.. :===+===+-         -.     
 ...   .    :.      ====-====+: . :===+===+-         :.     
 :.:.       -      .+========+. . .===+=+=+=          :.    
 .::.      :.      .+===++====  .. ====+=++=           -.   
           -       -========== ... -===+=+==          .-.   
 .        :.       -=====+===-  .  -==-+==+=          -.    
         .:        :=-:-===-=:     :==----=:          -..   
         :.         -..--=---:     :==--..-          .=-.   
        .:          .::------:     .---::-.           . ::  
       .-            .==-----. :   .---:-:               :  
      -:             .-::::::. -    :::::-               :  

    )" << endl;
}

void ConsoleUI::PrintCutScene4Image()
{
    cout << R"(
                ..                                              
        .::::-:--: .                      .:. .... .        
       .:. .  ::.:--.                   ::.:+=:-:-.  .      
      .   .. :.::.::=-                 ::--:...--.:   .     
      .     ...  .  .=.      +=        :--:.+#%%#+.         
      .    =*+*+--+-.-     .==-=       .=@@@@@%%*+.  .:.    
     .=. .-*+*#%%@%#.     -=+@@==:      :@%@%%+==-== .-:    
     .-=.-#+-=.-====    -=-*@%@%+-=:     ---+-:+=*%=.:=.    
   .. .: .:#%%#*#+*.  :=--+*%#@%*=--=.   :#*#*#%@%-.--:     
 .:.   : .-+%#-=*%-  =-:.-=*#*%*+=:.:=-   =%#+-*%#+-:.:=.   
.--:...  ..:-=-:==  +:. .:-=+=*=-::. :--   =#+=#*#+= .-+ .. 
.::==:..   .==-+:  .=:   ..:-:=::..   :+    -#++#*.  -#:    
 .--++=:    ..::    +:      . ..     .:+  ::::==-. .=%+  .. 
 ::-:::-.  :. ==.   :=:....:=.:-:....-+-::.:-:-=#=:#@%: ... 
 .---:. -=... :-+.    ------*-:+-----::.-*#####%%%###* .... 
 .:-... -== : .--:         =-.:=:     -#%*+***#@@@@@@@-.... 
  .++-:. .=.:  :+-       :*==-=-++. .*%+**%##@@@*+@@@%....  
  .-+*+-   ... .-:.                  -*###@%%@%.  +@@=..    
   .=+=+-   .   .::                  :.*####%%@#=+#%%.  --- 
    . ::-----::---=::.     .=--==---.. :**#**+#%%##*+*#%-   
      .....::=----:=##+=-: .:......:::*#*#+*+----+*+**##=.  
            .       .:-:: :::.:--:.:.. ....::.::::==+*##::* 
    ...     .:..... ..::-=--:-=++=::------=--:-:::-: .-:..+ 
.::.   ....  .-::...:==--=...+****+-:-==-----:: :.-:... .:: 
   .....      ......-=+=.-:..+####*-.-++-:::.....-----::.   
  .               ..:+-=--+======-=++**:.........      ::   
                     :+=*=---:+=---=+**+....            :   
                      ..... ........ .              .:      
                                                    :-.     

    )" << endl;
}

void ConsoleUI::PrintCutScene5Image()
{
    cout << R"(
                                                                
                               =-:.                         
                   .:-++      -====+.                       
                  :=----=    :=-----                        
                  .---=---  .=:---=               .==-:     
               .-=*+=::-:-: :---:=.              .=--=.     
               ++=-=+=--::.    .:.  .            -===.      
                ==-=++:            :*#+         .-:..       
                 =*=-:   .....    .#+*.       :====+.       
    -:.           .      .:-=-.    .:.       =+====::=+.    
   .***+            :...::---:                :+=: =*++:    
    .-=-       ---=*=+==-:::::.                    .-:      
              .:::--=-===--.-=++-::-:.             :--.     
          -=+*.    .-:=-==::-:-===-=---=++==:      ==-.     
          +#+**    -::-==-::.  .:-:......:-::   ::..        
          .#=-#-  .--=-==-:  . :=-. .          -*=:...      
           -***=  ..::---: .:- . :+=:     .::.--::-:..      
  . .:::.   :.   ...........=-=.-=-=.   :++*++::..::.       
 .::::::::::.    ............-..=== ...-++=-==.....         
  .........     ...... ......  :.  :.:+++==-=-:::-::        
          .    ... ..   .. ...   .+-.===----=-:--:==-       
        ..:...... .       .....    ...-+=+==-::.-+=-:.      
      ..:... ... .         ............=++---:.::.--::      
       ......  ..          .............++=:::....:---      
        ....              ......   ...:.-=-:...   :-=-:     
          .. .          . . ..............:.     .==--.     
          . .          :..::..............   .:-:-=:..      
         ....              . ......          .....          
                                                            

    )" << endl;
}

void ConsoleUI::PrintCutScene6Image()
{
    cout << R"(
                                                                
                                   .:::::-.                 
               ::::.           .:--:......:--               
           .:::.::--=--       -=..----:.....:-              
         .-:  :::...::-=:    .+::=####=-:.---::             
        :-.  .... ..  .:--    :=-*++==*#=-+:=:-             
       :-..: ...  :#+-  .=    .=-. .:++*#**+=--             
:::    = :-:.... .-%%@*..:     ::#+-*+---:==-:.-::::::::.   
  .:: -. =--+..=*#*#*+=::       ==-=--#*:.:......  .....:-: 
.  ..:.-=:=*#--#%+=+=+=:         -.::.==-:. .. +*+:  ......:
...  . =+-*%%%*+*#=.. .-          :.:-:.:..... ...==**-.....
....:...#=::=+=..-::+::            -.-:. ... :: -..-: ::....
   ..:::-=..:-+#+::-+:             ::.. ........:: .*  .  ..
 .....: . . ...::::-.              :  :.... ....=- .:  -. ..
   . .. .  . .......::::.           : -.-***+*+#*. .   +*=..
          .    ...  ......-=:       : -.::-:...*+.     -*+:.
       ..      .          -%#*-.    : -    . .::.      =#==:
               .. ...     ::+#*--:  . .         .::.::. :-==
         :. :..    ..... :. -**+---:. .      .       -...:-.
         -. +#.     :... ... :-:-.:*-.. .             .     
        .-. ==      :  ....: .-.:.+-+*=-..     ..    .      
         :  .=      :.      ::.:.:::=#%%%%+-:..       ....  
        :-  :-        ..        .... .:-==--.  ...          
        :=. :          :.          .      .......           
      .:-.. .            .:               . .....           
      .=: ..               ...           .....   .. ..      
      -=. .      :           ...         ...... .           
  .  :=.        : ..                     .... .             
   ..=.         .   ..                .   .... .   .        
   .-.    .    :                          ....  .           
          .   ..                           .                
          .   .                             .               
          .  :                              .               

    )" << endl;
}

void ConsoleUI::PrintCutScene7Image()
{
    cout << R"(
                                                                
                    ....::                                  
                  ....  .:.                                 
                   . .  ...                                 
                   .. ::-:.  -:                             
                    .:+##*=+=:*:.:-=+-+++=:.                
                    .-=+*==+#++=---.:-:::-=-:               
                    .:-:---+#=+=:=-:..::-===--.             
                     .:.:##+=+*=::-.::..-::++--.            
                    . .:.:=+*++=..: .: .:.:----:.           
                  . .   ...:-++. .-....   ..::=-:           
                   .        ..    .. .: . ..::=--:          
                             .:.   .....   ..:==--.         
                           . ..   . . .  .  .:---::.        
                                 :.. :+:...  .:::-::.       
                                -= .--.--.   ..:::....:     
                                -+=-++---.     .:-....::    
                      .        :--::::-::..   .:==...:-:    
                       ...... .--:..    ..   ..-=-...:::    
                       ....              .   ..--:...:--.   
                                            ..---...:::-.   
        .... ...............                .:=-...         
    ..:......:::::::::::::::.     .        ..-=:..          
    .:::::::-----=-:::......           .:.-++*-:.  .        
    .:::::::::::..   ................:===+-=+=++: :-::::.   
    .::::::::::......................:..+: =-:+.:-.....:.   
     ......       ..........:....... ...:..:..::....::-:    

    )" << endl;
}

void ConsoleUI::PlayCutScene5Animation()
{
    string Frames[] =
    {
        R"(
      :--:.  .                   .-===:     .--::::-        
    :=+=::...                       ..      .-::---         
    -==-:...:.                                 .::          
     :=:...-:::                                             
      .-::::::               ..:-::..                   ..  
        ::-:                . ..:-:..                 .-==: 
         .                  .:.:-=:.                .-=-==-.
.                  .      .::---:..                 .===-:  
-=-:.           :=+=--=-:=---.::..:                  .:.    
=--==.      ::---::..+*:::-:......          :.          .::.
::-=-     .-::..--:.=+--*=+-.....:.         .:.       .:..:.
          ::........-=.+=--:==:. .=-                  ::..  
          ......  ..:::+:----....::-:  .::.                 
      .:-=.       .::.:::---:::.:.::-.  ..:-:               
  .-+++==+=       .-: ::---::.....:-=:    .:.               
   ==++=**+:      :-:.:-----:. .  .:---                     
   :+*+.::==.    :--::::-=:.. .    .:-+=.        ......     
    -+:..:=+-    .:--:::-:::..      :---.       :-=. .  .   
    .===--==-.   ..:......:...       .:-:      .=++-: .  . .
     :==---=-:  .... .                .-=.    :-::::-..     
      ---:.       ....                ---:    .-::..::.     
               ....                   ...-=++=:.........    
.:.    .      ....            ..       .=+**+-.........     
.........    ....              ..     -++-=-::......  :     
             ....               ..  :++*=::=+-:.......::.   
            ....                  .=+===::-:=:.:.:::.:.-:   
            ...                  .=++--.:-.:-.::-=. .==--:  
           ...                   -=++-. .::-::..:. :-==-:-. 
                                .--==:.:--:...::..---:::.:: 
   .... ..                     . .-==::-:::::-:..:::.:::.:. 
.........                   ..... :=++:++:::..  ......::....
... .. .                ...:... . .:---..:::. ........:.::..
.. ..                ......  ...    :--:.... ......   .::.:.
 . .              .......     ..    :-==:   ......    .:.::.
                .. ...              .::--.    ..      ...:::
  ..          . ...             .... ......            .---.
    .         .               .......                 .:-::.
    . .          ..         .:......             .    .::. .
 ..      .....:....   ...........                     ::..  
 ..            .          .    .                   ....     
   .....               .                       ..::-=-.     
     .........                                ....:::-:     
        ..............                     ....  .. . .     
           ............................  .......  ..::...   

)",

R"(
     ..   ::-:::    .:...           .****=    .             
           ::..       .  ... .     .+*:-*:                  
                  ..    .  :::::.  .:=++=             .     
               :--+*+.   .-...::--:    :.          -::--:   
           .:-::....:    ::..:+=..-                .::::    
    :-:.  :=-....        :-:-=--.:                .:--:     
  .---:-: ....:-:...... .-:-:::-..           .    ..:.      
  ::-:::.   ...-++**#+-:-:..:.:::.          ..              
   .-:::-:..::::::=+=--:::....:....       .---.             
     .-==: ......:+-++*=:::..:.--:.. .    .----:.           
       .:.   ....=:*==-===-:.-++-==-....   .-==:.       ..  
        .  .  ..::=+==-::-=:=++-.:-:=-:.......              
        .      .=:-===*--=:-==----:..--:.  :..              
        .      -::=++=::::.-:::....:.::.....:.. ---:       .
              .=.--===-:. .::...   ...:-:....  ...:--. ..   
              ::--==:.-: .::..       .-+-:.     .. .. ..    
             :-:-:-=-:.. ...        .::.:-:      .    .:::. 
    ..   .: ...:::::::. ...       .-+::......    ..   .---:.
           ...........  ..       :=++..........: . .::--:-. 
           ..... ..           .:=-:==...  ..   ::. ..--:.   
            ......           :+==::-.:. ...   .:-=-:        
 ..  ........               -*+-:.:.--:........:..::.       
.....:......               :-=-:...-=::.....:.:..-:--.     .
 .... ..... .              :--.::..::-..::::  ::=--=-::...  
      . .                 :===:::. .::....:. .:----:-+-:..  
     .            .       -::--.   ..::.  .. ::..:.::::.:.  
      .                   ..:..     ...  .. :::.:::::...:-: 
     .        .                     .....   .......::::---::
              .         ...          .....  ...  .:..::-----
                   .....                .  ..         ..-++=
         .   ..                            .           .-=-:
          ....                               .         .--:.
                                    ...             ..:-... 
                                   ...            ::---::   
          ...                     ..             .....::.   
             . .    ..   ..   .....           ..    ....    
     ..  .......          ..... .                           
  ...... ..     .    .... ...                               
   ......  .         ......                       .         
    .................              .                  .:..  
     ..........  ..   .        .....                 .:::::.
       .........  ....                             .::::::. 
         ..........                              ..::.:::   

)",

R"( 
        .......      -+===+=          :=------.             
            ..       :-====-.       .-==-===.               
                                  .------=:                 
  :++:          .                =--:--=:      ...          
.-+++*+.        ..           .    :-=-:                     
.:=+-+*+-                  .                                
  .-=++=:          .    .:----:.                            
    :-.              .  .--:::-=-      .         :===-.     
          .....::..     ::..:.:-               :=-=+=.      
         :....----:    .::....:              .-=++=:        
        .:-:::...:.    :-:::::                .-=:          
        .::-:.  .        ..::       ..             ..       
        :::....:.                  ..:---=:                 
      .:-:......:.:.        .:::::--*+=:--::         .==-.  
  .---:.:... ..:-+=++*=+--=++----::.:--:            .=-=-==:
 :-=:-=-......-*+=-=++++=+==--::.....              :=----=*:
 :-:++=-:::...:-::::.--.::::......           ..... .-=-=-=. 
 ::==::::..::.-::...:::::::.....           :===:.     :--.  
.-:=:--...-=..-::...:.        ...      ...:::+=-.           
-::-:::-:::: ..::..:.         ....   .:::--:...:.           
-..:::::::.. .-:::..           ::.......... .....           
:.:::---:....::::::    ...  .    ....:  .     ...           
:..-:::..:. ...:::.     .  .:-+*+=---. .. .  ...            
...-:==-:.. ...:..      . .-+*==-::-.... ..   ..            
.-:::::...  .....  ..  .:=+--=++==:::....  .                
 .:-:.::.........  .:--=+-:---.:--==:::... .                
 .....    .    .==*+=--:.:=::..---+-...--:.                 
...         .:-==+=-::...--=:-:..:....-+==-:.         ::.   
..      .:===::...::.....-::..:.::..:====---:.      .----:. 
     ..:-:-=.    ....  .--::::-:..-=-:::::.....     .:-:::-.
      .::.-.           :==-:::. .:-----::..:..        .::--:
       . .            .--=:::  ......:-.:::...          ::: 
                     .+-.:-.  ........:--......             
 ...                ..:=-:. ...........--::. ...            
 :--:.              ...::....:..........:=-:::..       .    
 .-:-:                   ..::.......    .::-=:..    ::::    
  ::::.            .         .......    .:.:.:-:... ::::    
.  :--:.           .....                 ..-=-...   ::.:    
    :::..           .                    .=+=-:..  .:::.    
                 .....                   :--:...  .:::.     
        ....  ......                     :=:.  .            
   ........   .....                     .-:.                
 ......     ......                   .:--:.            .:.  
   ..      .....                  .::---::.           ::::::
   ..    ....                    .. .:....          .:..::.:
       ....                       ........         ....::..:
       ...                      .       ...      .........: 

)"

    };

    int FrameCount = 3;

    int RepeatCount = 3; // 애니메이션을 3번 반복

    for (int repeat = 0; repeat < RepeatCount; repeat++)
    {
        for (int i = 0; i < FrameCount; i++)
        {
            // 현재 i번째 프레임 출력
            cout << Frames[i] << endl;

            // 700밀리초 동안 잠깐 멈춤
            this_thread::sleep_for(chrono::milliseconds(700));

            if (i != FrameCount - 1)
            {
                // 마지막 프레임이 아니면 화면 지우기
                system("cls");
            }
        }
    }
}

void ConsoleUI::PlayCutScene6Animation()
{
    string Frames[] =
    {
        R"(
                                                                                
                                                                                
                                             :---=-----=--.                     
                    :----:.               :-=-:...:..:....--                    
                :---...::-===:          :+-..:::---.....:..:=                   
              --. ..::::::.::-+-       .+-..:*#***+:.::..-:::-                  
            :=.   .::::..  ..:--+.     :+=:-=*#%@%#**--.=:=-:+                  
           --.   ..:..  ...   .::+:     .==-*+==--=+*=--*:.=:=.                 
          --...  ....   .**-.   .:=      =+-.  .:-***##*#+*=-.:                 
::       :- .:--.....  .:#%%%+:  ::      =: +-::++=-=*+==*::-:-:  ....::.       
 .:::    =. -=-:. .. ...:*%#%%#.::        :=%%*-=+===:..-=-:...:-:...:...:::.   
   ..-: =: .=+:=*- .=%%%###++=:.-          +:..=-:+%#+..:........  .:..:....:-: 
..  ..:-.::+.+=+#-:-#%#=++=++*::.           -::--::+*=::.  .. .#%#=.  .. ......-
...   .  :#:::#@%%#**#%#=--..---            .=. :-::.::. .... .- .+*.+*=........
  ...  .  +#-+#%#*#=:-=*=.... ::              -:..--... ....:.  -  :+:-+*...:...
....::::..:#* ..-++=:..--.=*::                 -:--:. ..... .-. ::..:+  .+......
     ..::::=+:. .-=*##-..=**-                  -:..  ..... ...-  =   #:  ..  ...
 .....:.:. : :....:-=---:.::                   -   : .... .... ..*.  +-  :.   ..
    . : :  . .  .......::-:..                  :.  -..... .....-++. .    .*... .
    . ... ..   .      .....::--::.              -  =..#%%%%##*###:  .    :#**:..
                    ....  ........:=-:          - .-.:----....:#*:       .=*+:..
        .......       .            =%%*-.       - .-  .......::-:..       *%#:-.
                  ...              -#*%#+-:     : .:          .::.    .. :++=+=:
                    ........      .: -+##=-=-.  . ..      . .    ::::::..  :-:+=
            :.  .       .....:.   -  .=##+==--- .. .  .            .  .-.. ..--.
            -:  +#+        .   ....   :==-=--.=+.. .. .                .:....   
           .-:  -%=        -::::.   .  .:..:.:-**:.. ..              ..         
           .-.  -=-       :.     ...:. :=::-.=--=**+=:..      ...     ..        
            -   .--       .:.        :::. . .-.-=##%%@%#+--...   .      ...  . .
           ::.  .+.         .:.         ..:.::::.:=+**#**==:. .. .         .    
           :+.  .=            :.                     ..::::. .. ...             
          .:+.  ..             ::.            ..         .... ....  ...         
         .--:.  .                .:.                    .. .. .. .              
         :=- . ..                  .:.                 . ..... ..... ..         
        .==. .                       .:.               ... ... ..  .  ...       
        =+:  .        ::.               ..             .. ....   .              
   .   :+=   .        : .:.               .            ..... ..                 
   .. .+=            :.   ..                            :...  ..  ...           
     .=-             :       .                     .    . ...  ..    .          
    .::      ..     :                                    :  ..  .               
   .         .     ..                                    ..                     
             .     :                                      :                     
             .    :                                        :                    
             .   ..                                        ..                   

        )",

        R"(
                                                                                  
                                                                                  
                                               :---=-----=--.                     
                      :----:.               :-=-:...:..:....--                    
                  :---...::-===:          :+-..:::---.....:..:=                   
                --. ..::::::.::-+-       .+-..:*#***+:.::..-:::-                  
              :=.   .::::..  ..:--+.     :+=:-=*#%@%#**--.=:=-:+                  
             --.   ..:..  ...   .::+:     .==-*+==--=+*=--*:.=:=.                 
            --...  ....   .**-.   .:=      =+-.  .:-***##*#+*=-.:                 
  ::       :- .:--.....  .:#%%%+:  ::      =: +-::++=-=*+==*::-:-:  ....::.       
   .:::    =. -=-:. .. ...:*%#%%#.::        :=%%*-=+===:..-=-:...:-:...:...:::.   
     ..-: =: .=+:=*- .=%%%###++=:.-          +:..=-:+%#+..:........  .:..:....:-: 
  ..  ..:-.::+.+=+#-:-#%#=++=++*::.           -::--::+*=::.  .. .#%#=.  .. ......-
  ...   .  :#:::#@%%#**#%#=--..---            .=. :-::.::. .... .- .+*.+*=........
    ...  .  +#-+#%#*#=:-=*=.... ::              -:..--... ....:.  -  :+:-+*...:...
  ....::::..:#* ..-++=:..--.=*::                 -:--:. ..... .-. ::..:+  .+......
       ..::::=+:. .-=*##-..=**-                  -:..  ..... ...-  =   #:  ..  ...
   .....:.:. : :....:-=---:.::                   -   : .... .... ..*.  +-  :.   ..
      . : :  . .  .......::-:..                  :.  -..... .....-++. .    .*... .
      . ... ..   .      .....::--::.              -  =..#%%%%##*###:  .    :#**:..
                      ....  ........:=-:          - .-.:----....:#*:       .=*+:..
          .......       .            =%%*-.       - .-  .......::-:..       *%#:-.
                    ...              -#*%#+-:     : .:          .::.    .. :++=+=:
                      ........      .: -+##=-=-.  . ..      . .    ::::::..  :-:+=
              :.  .       .....:.   -  .=##+==--- .. .  .            .  .-.. ..--.
              -:  +#+        .   ....   :==-=--.=+.. .. .                .:....   
             .-:  -%=        -::::.   .  .:..:.:-**:.. ..              ..         
             .-.  -=-       :.     ...:. :=::-.=--=**+=:..      ...     ..        
              -   .--       .:.        :::. . .-.-=##%%@%#+--...   .      ...  . .
             ::.  .+.         .:.         ..:.::::.:=+**#**==:. .. .         .    
             :+.  .=            :.                     ..::::. .. ...             
            .:+.  ..             ::.            ..         .... ....  ...         
           .--:.  .                .:.                    .. .. .. .              
           :=- . ..                  .:.                 . ..... ..... ..         
          .==. .                       .:.               ... ... ..  .  ...       
          =+:  .        ::.               ..             .. ....   .              
     .   :+=   .        : .:.               .            ..... ..                 
     .. .+=            :.   ..                            :...  ..  ...           
       .=-             :       .                     .    . ...  ..    .          
      .::      ..     :                                    :  ..  .               
     .         .     ..                                    ..                     
               .     :                                      :                     
               .    :                                        :                    
               .   ..                                        ..                   

        )",

        R"(
                                                                              
                                                                              
                                           :---=-----=--.                     
                  :----:.               :-=-:...:..:....--                    
              :---...::-===:          :+-..:::---.....:..:=                   
            --. ..::::::.::-+-       .+-..:*#***+:.::..-:::-                  
          :=.   .::::..  ..:--+.     :+=:-=*#%@%#**--.=:=-:+                  
         --.   ..:..  ...   .::+:     .==-*+==--=+*=--*:.=:=.                 
        --...  ....   .**-.   .:=      =+-.  .:-***##*#+*=-.:                 
       :- .:--.....  .:#%%%+:  ::      =: +-::++=-=*+==*::-:-:  ....::.       
:::    =. -=-:. .. ...:*%#%%#.::        :=%%*-=+===:..-=-:...:-:...:...:::.   
 ..-: =: .=+:=*- .=%%%###++=:.-          +:..=-:+%#+..:........  .:..:....:-: 
  ..:-.::+.+=+#-:-#%#=++=++*::.           -::--::+*=::.  .. .#%#=.  .. ......-
.   .  :#:::#@%%#**#%#=--..---            .=. :-::.::. .... .- .+*.+*=........
...  .  +#-+#%#*#=:-=*=.... ::              -:..--... ....:.  -  :+:-+*...:...
..::::..:#* ..-++=:..--.=*::                 -:--:. ..... .-. ::..:+  .+......
   ..::::=+:. .-=*##-..=**-                  -:..  ..... ...-  =   #:  ..  ...
....:.:. : :....:-=---:.::                   -   : .... .... ..*.  +-  :.   ..
  . : :  . .  .......::-:..                  :.  -..... .....-++. .    .*... .
  . ... ..   .      .....::--::.              -  =..#%%%%##*###:  .    :#**:..
                  ....  ........:=-:          - .-.:----....:#*:       .=*+:..
      .......       .            =%%*-.       - .-  .......::-:..       *%#:-.
                ...              -#*%#+-:     : .:          .::.    .. :++=+=:
                  ........      .: -+##=-=-.  . ..      . .    ::::::..  :-:+=
          :.  .       .....:.   -  .=##+==--- .. .  .            .  .-.. ..--.
          -:  +#+        .   ....   :==-=--.=+.. .. .                .:....   
         .-:  -%=        -::::.   .  .:..:.:-**:.. ..              ..         
         .-.  -=-       :.     ...:. :=::-.=--=**+=:..      ...     ..        
          -   .--       .:.        :::. . .-.-=##%%@%#+--...   .      ...  . .
         ::.  .+.         .:.         ..:.::::.:=+**#**==:. .. .         .    
         :+.  .=            :.                     ..::::. .. ...             
        .:+.  ..             ::.            ..         .... ....  ...         
       .--:.  .                .:.                    .. .. .. .              
       :=- . ..                  .:.                 . ..... ..... ..         
      .==. .                       .:.               ... ... ..  .  ...       
      =+:  .        ::.               ..             .. ....   .              
 .   :+=   .        : .:.               .            ..... ..                 
 .. .+=            :.   ..                            :...  ..  ...           
   .=-             :       .                     .    . ...  ..    .          
  .::      ..     :                                    :  ..  .               
 .         .     ..                                    ..                     
           .     :                                      :                     
           .    :                                        :                    
           .   ..                                        ..                   

        )"
    };

    int FrameCount = 3;

    int RepeatCount = 3; // 애니메이션을 3번 반복

    for (int repeat = 0; repeat < RepeatCount; repeat++)
    {
        for (int i = 0; i < FrameCount; i++)
        {
            // 현재 i번째 프레임 출력
            cout << Frames[i] << endl;

            // 700밀리초 동안 잠깐 멈춤
            this_thread::sleep_for(chrono::milliseconds(700));

            if (i != FrameCount - 1)
            {
                // 마지막 프레임이 아니면 화면 지우기
                system("cls");
            }
        }
    }

}



// New Cut Scene
void ConsoleUI::ShowNewCutScene1()
{ 
    // TODO: 컷씬 제목 출력 코드
    // 
	// 컷 신 1 이미지 출력
    // 대사 출력 함수
    // TODO: 다음 장면으로 넘어가기 위한 안내 문구 출력 코드
}

void ConsoleUI::ShowNewCutScene2()
{
    // TODO: 컷씬 제목 출력 코드
    // 
    // 컷 신 2 이미지 출력
    // 대사 출력 함수
    // TODO: 다음 장면으로 넘어가기 위한 안내 문구 출력 코드
}

void ConsoleUI::ShowNewCutScene3()
{
    // TODO: 컷씬 제목 출력 코드
    // 
    // 컷 신 3 이미지 출력
    // 대사 출력 함수
    // TODO: 다음 장면으로 넘어가기 위한 안내 문구 출력 코드
}

void ConsoleUI::ShowNewCutScene4()
{    
    // TODO: 컷씬 제목 출력 코드
    // 
    // 컷 신 4 이미지 출력
    // 대사 출력 함수
    // TODO: 다음 장면으로 넘어가기 위한 안내 문구 출력 코드
}

void ConsoleUI::ShowNewCutScene5()
{
    // TODO: 컷씬 제목 출력 코드
    // 
    // 컷 신 5 이미지 출력
    // 대사 출력 함수
    // TODO: 다음 장면으로 넘어가기 위한 안내 문구 출력 코드
}

void ConsoleUI::ShowNewCutScene6()
{
    // TODO: 컷씬 제목 출력 코드
    // 
    // 컷 신 6 이미지 출력
    // 대사 출력 함수
    // TODO: 다음 장면으로 넘어가기 위한 안내 문구 출력 코드
}

void ConsoleUI::ShowNewCutScene7()
{
    // TODO: 컷씬 제목 출력 코드
    // 
    // 컷 신 7 이미지 출력
    // 대사 출력 함수
    // TODO: 다음 장면으로 넘어가기 위한 안내 문구 출력 코드
}

void ConsoleUI::ShowNewCutScene8()
{
    // TODO: 컷씬 제목 출력 코드
    // 
    // 컷 신 8 이미지 출력
    // 대사 출력 함수
    // TODO: 다음 장면으로 넘어가기 위한 안내 문구 출력 코드
}

void ConsoleUI::ShowNewCutScene9()
{
    // TODO: 컷씬 제목 출력 코드
    // 
    // 컷 신 9 이미지 출력
    // 대사 출력 함수
    // TODO: 다음 장면으로 넘어가기 위한 안내 문구 출력 코드
}

void ConsoleUI::ShowNewCutScene10()
{
    // TODO: 컷씬 제목 출력 코드
    // 
    // 컷 신 10 이미지 출력
    // 대사 출력 함수
    // TODO: 다음 장면으로 넘어가기 위한 안내 문구 출력 코드
}

void ConsoleUI::ShowNewCutScene11()
{
    // TODO: 컷씬 제목 출력 코드
    // 컷 신 11 이미지 출력
    // 대사 출력 함수
    // TODO: 다음 장면으로 넘어가기 위한 안내 문구 출력 코드
}

void ConsoleUI::ShowNewCutScene12()
{
    // TODO: 컷씬 제목 출력 코드
    // 컷 신 12 이미지 출력
    // 대사 출력 함수
    // TODO: 다음 장면으로 넘어가기 위한 안내 문구 출력 코드
}

void ConsoleUI::ShowNewCutScene13()
{
    // TODO: 컷씬 제목 출력 코드
    // 
    // 컷 신 3 이미지 출력
    // 대사 출력 함수
    // TODO: 다음 장면으로 넘어가기 위한 안내 문구 출력 코드
}

void ConsoleUI::ShowNewCutScene14()
{
    // TODO: 컷씬 제목 출력 코드
    // 
    // 컷 신 4 이미지 출력
    // 대사 출력 함수
    // TODO: 다음 장면으로 넘어가기 위한 안내 문구 출력 코드
}

void ConsoleUI::ShowNewCutScene15()
{
    // TODO: 컷씬 제목 출력 코드
    // 
    // 컷 신 5 이미지 출력
    // 대사 출력 함수
    // TODO: 다음 장면으로 넘어가기 위한 안내 문구 출력 코드
}

void ConsoleUI::ShowNewCutScene16()
{
    // TODO: 컷씬 제목 출력 코드
    // 
    // 컷 신 6 이미지 출력
    // 대사 출력 함수
    // TODO: 다음 장면으로 넘어가기 위한 안내 문구 출력 코드
}

void ConsoleUI::ShowNewCutScene17()
{
    // TODO: 컷씬 제목 출력 코드
    // 
    // 컷 신 7 이미지 출력
    // 대사 출력 함수
    // TODO: 다음 장면으로 넘어가기 위한 안내 문구 출력 코드
}

void ConsoleUI::ShowNewCutScene18()
{
    // TODO: 컷씬 제목 출력 코드
    // 
    // 컷 신 8 이미지 출력
    // 대사 출력 함수
    // TODO: 다음 장면으로 넘어가기 위한 안내 문구 출력 코드
}

void ConsoleUI::ShowNewCutScene19()
{
    // TODO: 컷씬 제목 출력 코드
    // 
    // 컷 신 9 이미지 출력
    // 대사 출력 함수
    // TODO: 다음 장면으로 넘어가기 위한 안내 문구 출력 코드
}

void ConsoleUI::ShowNewCutScene20()
{
    // TODO: 컷씬 제목 출력 코드
    // 
    // 컷 신 10 이미지 출력
    // 대사 출력 함수
    // TODO: 다음 장면으로 넘어가기 위한 안내 문구 출력 코드
}

void ConsoleUI::ShowNewCutScene21()
{
    // TODO: 컷씬 제목 출력 코드
    // 
    // 컷 신 1 이미지 출력
    // 대사 출력 함수
    // TODO: 다음 장면으로 넘어가기 위한 안내 문구 출력 코드
}

void ConsoleUI::ShowNewCutScene22()
{
    // TODO: 컷씬 제목 출력 코드
    // 
    // 컷 신 2 이미지 출력
    // 대사 출력 함수
    // TODO: 다음 장면으로 넘어가기 위한 안내 문구 출력 코드
}

void ConsoleUI::ShowNewCutScene23()
{
    // TODO: 컷씬 제목 출력 코드
    // 
    // 컷 신 3 이미지 출력
    // 대사 출력 함수
    // TODO: 다음 장면으로 넘어가기 위한 안내 문구 출력 코드
}

void ConsoleUI::ShowNewCutScene24()
{
    // TODO: 컷씬 제목 출력 코드
    // 
    // 컷 신 4 이미지 출력
    // 대사 출력 함수
    // TODO: 다음 장면으로 넘어가기 위한 안내 문구 출력 코드
}

void ConsoleUI::PrintNewCutScene1Image()
{
    cout << R"(
                                                            
                                                            
          .                              .::                
         :::.    .::::.               .*##@##@:*:           
         :##*:  :*#*##         ::.    .#@#:*@@@###:         
          #@:  . :*::. .  ... *##:     :#*##*::**#.         
         *## .:. ....... .. . *@*      .:...:. :*:          
         @@#  . ..  .   :  . :##      :.     .:..           
        .@@# .. :..:###*. :..@@*     .:.::.   :             
        .@@#* .. .*@@##: .. #@@.      ::**:**:.             
         :@@@@*#::##::*::*##@@.       .*:**:**.:.           
           *@@#@**#***#@@@@*:          #**@@**#@@#:         
            :#@@*###**#::.            .**#*#:@#*@@@:        
            :#@@*##@***              .@@*#*@@*:@@@##        
            *@@@**#@***              #@@***#@@:#@#:@.       
            #@@@@:@@*#:            ..@@@: .*@@###*@@:       
           :#@@@#*@@.*::**#@#.   .:. .:....#*@@**@@@*       
          .@####:**#*#@@**@@@:   :.  .:.  .:.  .*#@@@       
          *@@#**####*#**@@@#:     :.   ::..      :*#*       
           .*#@@@@@@@@@##*:**#* .@@#*...     ..   . :       
            :@@@@***##**.::**:.  :*:......::::    .:        
              ... **:*::::.:*:  .:...:...*##. .....         
                    .:..::: ::  : .. : . :.                 
                     ::..:* ::  ..   :  ..                  
                      ...::..     ...:..          .         
                                                            
                                                            

)" << endl;
}

void ConsoleUI::PrintNewCutScene2Image()
{
    cout << R"(
                                                            
                                                            
                 .  .                                       
             .............                    ..   . .      
          .:.............. ....          .   ....... .      
        ..:..:...:............... ..   .. .... ...:....     
       .:....::.......... ....:::.....  ....:....::..:.     
      .:.........:.     .:.*#####*.....   ..........:..     
      .:....  ......... .*..:**::*:...:.  ... ..:..:...     
      .:....     : .... .:.::****#*.......    .... ..:.     
      .:....        .    :.*::*#*: ..........    .....:     
       .::......          ...:**::  .:..:....:::....::      
     .....:.......   .. .....:::::....:...............      
    ....::...:..:.......      .::....................:.     
     . ...:...........  ......::.............     .. ..     
               .  . .. ... .*#*:. ...........               
              ..  ..   . :   #:...........  ..              
              ..   .  .. ..  ::. ..........  ..             
             .     .  ...... .. ............  .             
             .       ................. .....  ..            
             .    ............... ....  ...    .            
            .     ....  ... ....  ...    .. .. .            
            .     ...    ........ ..      .  .  .           
            .      .  .  ............     .   . .           
           .       .      . ......:.:. ::...  .  .          
           .      .       .  ..   ..   .::..     .          
           .      .       .  .    .:    .. ..   ..          
                 .       .   ..          .  .  .  .         
          .      .       .   .                              
                                                            
                                                            

)" << endl;
}

void ConsoleUI::PrintNewCutScene3Image()
{
    cout << R"(
                                                            
                                                            
                                                            
                      .......                               
                    .. .::::  ..                            
                   .  ...*:...  . .:.                  ::   
                   ..::::::::::..  ***::.:. :*:  .:::*#*:   
                     ::.......:     :**:::*..##.:*:****.    
                    .:@####*##:.     .:**::.**#::::**:      
                    .*@@@##@@#:        ..::.:**..:. .       
                      *@@##@@.        :**:.:* ::..***.      
                      .*@#@#*         **:#*::*::***:#.      
                     .:#::*#*:        ::#::#*##**:*#:.      
                .:.::.. :#*. :::.:..    #**#*.:#**#.        
              ::...   ... .... .....:.   .*:#*#*::          
             *..  .     ....  .... ..*                      
            :.... .:.   . .   @@# .:...                     
            :..:..:.:.. . . ..:*:..:....                    
           :. .... . .. . . .. . .... .:                    
           :.. . .... . ... . .... .  .:                    
          .. .. .. .. ..  . . .. ... . ..                   
          :.............  . .....:...:...                   
          :....:.: .. ..  ..  . .:.:....:                   
          ..   .....   .   ..........  ..                   
            ... .......::::............                     
              ::.:  :@##*#@@@#. ...:.                       
             .::....:*####@@#:..:..::               .       
             .........:*##**:.......:                       
             .:...  .....::... .....:                       
              : .   .    ..   .   ..                        

)" << endl;
}

void ConsoleUI::PrintNewCutScene4Image()
{
    cout << R"(
                                                            
                                                            
                                                            
                                                            
                             . ..                           
                           :*:.. ::                         
                         ..********:                        
                         :..*@@@@#...                       
                         ...:#@@**#.:                       
                        ...#@@@@@@#::                       
                        :. *@@##@@:.:.                      
                        :.: *@#@@* ::.                      
                        ..:.****#*..:                       
                        ..:*#@@@@#*...                      
                     :*@#:###*##*##*##@*:                   
                    #@@#::*########*#@@@@*                  
                   :@##*##*##@##@#@:#@@##@.                 
                  .*#***@#*@#@@#@##:##*##@#                 
                  ..:******@#@@#@***#***##@.                
                  :......#:*##@####*****##@*                
                 .@: ... :##*####*@#########                
                 *#*..::  #*#*@#*#@###*:*#@*:               
                .###*:.:.##*#####@@@@##:*@*#*               
                 #@@@@##@@@@#*@##@@@@@#.:**#*               
                 .*#@@***:****####@@@@#::.::                
                    .*::::..::  .@@@@@@*                    
                     .#*#@#@#.  .@@@@###.                   
                     .:::::::    :::::::.                   
                                                            
                                                            

)" << endl;
}

void ConsoleUI::PrintNewCutScene5Image()
{
    cout << R"(
                                                            
                                                            
                                                            
                                                            
                          ..:::..                      .:.  
                         .::*::::...            .   ..:::.  
                        ...::..:::..              .:::....  
  .:.                   .::@@@@@#@*:       ..     :...:::.  
  .::.:.                .*:##@@@##*:      .  .:   ..:..     
  .::.:.::..            .:::::#:**#*      .:::.   .  ..::.  
   ::.::::.:.            :*@@#@@@#*:    ..:....   ..... ..  
  .::.:.::.:.             :*#.:*##:      .:.. .     .::::.  
  .::.::::.:.             ..::**::..   :. ..:::   :.:::::.  
  .::.::::::.          .*:: .:**:::##:.:*###*::   :.:::::.  
  .::.:.::::.      .::#@@ * . .:::#*@##*:###::*::.:**::::.  
  .::.::::.:.  :#@##*@@@*.*.:###:::**##*::###***:*:*@@#*:.  
  .::.::::::. .#@@#@@@@@*: .*@#*:::*@###**:*###:.:::@@@@#:  
     ...::::. .*@@*@@@@##*:***#:#**#@@#####**:*#:...:**#@*  
             . :#@*@@@@*@####******#@@@*###* .****.   .*#*  
             :  *#*@@@##@##*:#:*#**@@@*#@@@*      ..    ..  
            .   ::*@@@:#@@*@***#*@*@@#*@@@@:                
            .    .*@## ....:@:#:#@:@*   :##.:::.            
     :::.   .   ......*::   :*:*:..*   :***#@@@@#*.         
     *::*  .  ..   ...*@@#**#:#*#:.* **@@:*#@@#@#@@*        
    .:*::.  .:    . ...:.**:@*@@@:.:#@##*.:##@#.*#@@@.      
     :.::  .:  .   ...:...**#*##@:.:@@@#:: #@@*.##@@@@.     
    .#*##  .   .  . .  ....:*:#*:. #@@@*##:#@@. *###@@#.    
    .#::#..  . . ..     . .        #@@@.#::#@#   :*####*    
     :..:       .  ...  .          :@@@.#*#@#. :#@#@@#:     
    .:#:* .:.. .    ..  .           @@@:**@#..#@#**:.  :    
     :.:. :# ..   .. ..:.           .....*#::@##*#**@*  .   
          :.          ..::.           .::.  :::.:::..       
                                                            

)" << endl;
}

void ConsoleUI::PrintNewCutScene6Image()
{
    cout << R"(
                                                            
                                                            
                                                            
                       ........                             
                      . :****:.     ..                 ..   
                       .##@@##.     .**::....:*  ...::**.   
                      :*###@#@*.     .**:::*.:#:.*:::**.    
                       :@@##@@:      ...:*::.*#*.:**::..    
                        *@##@*       ***:....:::....:***    
                       .*:****.      ::***:.:...:.:**:*:    
                  ...::.##**@#.....  .:*******#******::.    
                ::::.::::#::#::::.:::: ::***#*.##***::      
               :..:::::::#::#:::::::::.   ::*#*#*::         
              :....::.:::.::.:::.::.:::       :             
            .:::.. :::..:::*::::::..::..                    
           .:......::#.:@@@#*:..... .:::                    
          ...::.:::::#::***:...:..  .::..                   
          .....................:. . .::::                   
           ......  .   ......::.... ......                  
                   :..:...:::.:::.:  ..:..                  
                   :.::.::.::::::..  ..:::                  
                  ...:..::::::::.... ..:..                  
                  ....:.:::::.::.. . ..::.                  
                  :.:::.::::::::.:.. .:::.                  
                  :.:::.::::::::::.: .**:                   
                 ..::::.::::::::::...#@@:           .       
                  .......::::::.....:::*.                   
                  ..:...      ...... :.                     
                  :.:.:..    .::.:.:                        
                                                            

)" << endl;
}

void ConsoleUI::PrintNewCutScene7Image()
{
    cout << R"(
                                                            
                                                            
                                                            
                       ...                                  
                 .-.  .. ::         .::..                   
              .:-*+: :=###-         .***:.  ---.            
             .. :...:.##%+:.  . :    =%@#=:..-+#=.          
             ....    .--.. .:..-++....++%#=. . ::..         
               ...: . ....... . =@=--:.-+**..:..            
                  :   .  -+-:.:=:::..:-=**#* :.:.           
                 :..  -++%*#* .+..:::: .*%###+:             
              ...:...+%#%%##-  *. +##:- +*=*%*==-.          
            ::.     .#%+*#*-  .=- -#@##===+++-=+++.         
          .-=+-....  :#%-:.:..:+*==+%**%#*==#+==-:          
         .+**+==:.          ::+##+-:-=-=****++=:.           
         :%*+*+: .       .:.+*+-+=.-**=+*%**++=:.           
         .+*+*+#-.  .. .-+=+=-:..=.==+-=+*****=- ..         
           :-++#%#=:: .-++#*-    -++===#--+=*+++            
            :. .-#%%#+:.+*=:..   .=---:*%--+**++-.          
           ::.. :=-+=::   ..:-    -+-: .*+-*==*--..         
          :......:.::.::.  ..::   ..-.  -+--+=-:.:.         
         ..  ...  .. .   .:.    .:.... .:....:.   .         
               ..::...     .:      .:.. .                   
              .:.  .::..     :   .:.          ...           
                                                            

)" << endl;
}

void ConsoleUI::PrintNewCutScene8Image()
{
    cout << R"(
                                                            
                                                            
                                                            
                 ....                 .........             
              ..........             :::::...  :.           
             .    .. ....            :..**.::.  .           
             .     #@@#.:   ....     .#@####::: .           
             ..*::@#**@*  .**.. ::   .**:#@@*#* .           
          :...:*@@@@@@*. ..:**##*:.   :@@@@##*#*:           
         ::..:@@#@@@##: ....:#@@#* .  .:*###*:*:.:.         
       .:..:::#@#:#@#:  . ..*#@@##.:    :*:.:*::....:..     
     .::::.....#@* .:   ...:@@@#@#.:     :: #::..:......    
    ::..:*:.....::...:. : . *@###.::.  .....*...:...:..     
   .:.::...:.....:....:.....:#**:...  ::...:*..:.:.....     
   .::.:....:::..::..:...::*#@@@#*::. :.......:.........    
   .:...  ..:::: ::..:*#@**##*#*##*#@#*.:.:...:..:::. ..    
    ...    ......::..*@#****##*##@:#@##*..:..:.......       
   .:.     .......:..#***##*#@@###*####@:............       
   .. .    .....:::::..:::::**#@*:*#**#@* ......... .       
   .:::.  . .:::::::#*......*:###****:#@# ...:      ....    
     ....:.  .....::@#. ... .#***###*##@@.:......::.:...    
   ..   . ..#:*....*#*:  ::.****#@##*:##:.:...::::::...     
     .:    :*.::...*#####**@@@###@@##*###*.: .  .::*  .     
      :.   .   . ..:#@@@@***#####*#@@@@@#. ..               
       :.  .. .  .....:***:.*#@@@*#@@#*:....  .             
       :       . ......##**@#:..*::***..  ... .. .   .      
       :....   ..... .:@@##@@.  #@@#@@*.    .......   .     
       :...::........ *@@#@@@   @@@#@@#.  ...  ..           
       :...::::..   ..#@@#@@#   #@@#@@@.    ..  .     .     
       . ......      .:::::::   :::::::.                    

)" << endl;
}

void ConsoleUI::PrintNewCutScene9Image()
{
    cout << R"(
                                                            
                                                            
                                                            
                 .....                .........             
               ..........            ::::....  .            
              .    .......           :.:*#:::.  .           
              . .  :@@@*:.           .#####*.** .           
              .:*:@@*:#*.             :*:#@###*..           
          .:...**@@@@@#:              .##@@##*#*:.          
         .::..*@#*@@@#:                .*##*:**:.::.        
        .:....:#@#.*#:                  ::: **:......:.     
     .:::::.....*@....                   .. *.:........     
    .:...:*:....... ..:.              .:...:#..:.......     
    ..:::....:.........:             .::...::.:........     
    .*:.:. ...:: .*:..::       ..   .:.:.....::...:....     
    ....   .......::.....       **:.:. .....:::..:... .     
    ...     ...:..::.....       .#**:::....:::....:.        
    .. .    .......:......:     :.:**::.  :. ......         
    ....  . ....:::*...:**:    .....:**:: .. :  ...         
     ..:...  .....:::.**::     ..   ..**::::...  ......     
        ......:**::::*:.:.       ...   ::::.....:::....     
     ...    :@@@#*::....:.             :..:. ...::::        
       :    .###*:::.....:             :. ... .. ... .      
       ...  ..... .:.  ..:.            :.    .::.           
       .:      .. ... .  ..            :. ... ...           
        :.       .... . .::            :  . .......  .      
        :..............:#@*           ..   .  ....          
        :....:::.. . .::#*#.          ..  ...  ...          
        .....:...   ....:*:           ..      .             
                                                            

)" << endl;
}

void ConsoleUI::PrintNewCutScene10Image()
{
    cout << R"(
                                                            
     ...................................................    
     %@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@:   
     %@#::::::::::::::::::::::::::::::::::::::--:::::=@@:   
     %@*               ..::..                :.      -@@:   
     %@*             .-.  ..:=.              .:      -@@:   
     %@*            .:*=:.:--- :              .= .   -@@:   
     %@*            . .:-#@@@#...              *+*-  -@@:   
     %@*            .  :+#%%**#::              -@#++.-@@:   
     %@*            :.-*#*%@%%@::               +@%##+@@:   
     %@*   *- -=    ::.=@@@%%@#..  ..            +%**+@@:   
     %@* -=.#::#     ...-#@##%-=##@@%#-:.         ..++@@:   
     %@* .-*-#-%:  -##**-=:--**=%#@%##%%@%*==.  .=#%#+@@:   
     %@* ===%@@@#.=###%*-#=#%#+=#%@%##%#%%**#%#:@@%##+@@:   
     %@*   =%%%%@%*+*%*#-@=*%+*=%##%=+=#*+%@@@+#%%##*+@@:   
     %@*    =%%%#*=@#%====*+=+#=**=**. ..+##*+%#%#*##+@@:   
     %@*     .::=--%*-:=%**++++=****+=  .*%%*#%%#####+@@:   
     %@*      :=-:-:  =#%%*#++==#%@@*+  +##**+######*+@@:   
     %@*              :%*%*+=+**@%%#%*:=++=+=**##*+--+@@:   
     %@*               =##%%===#@@###%##**+**###*-.=++@@:   
     %@*               -%@@%++*##+@@@@%%##%*#*=: .+*#+@@:   
     %@*               +*@%#+#%@%+######*+--:    #+#*+@@:   
     %@*              -#%##**#%@%+*###**+        *#*#+@@:   
     %@*             =##%@**=++:*%@@%#%%@*      -####+@@:   
     %@*            -%@%%@@+ .  =@@@%%@@@@+     #@*##+@@:   
     %@*           :#@@%@@%.    .%%@@@%@@%%-    %##*#+@@:   
     %@*          .*#@@@@@+   -. =@@@@@@@@@@.  -%#%#*+@@:   
     %@*          .#@@@@@%   .-:  #@@@@@@@%-   #%####+@@:   
     %@%############################%################%@@:   
     +**************************************************.   
                                                            

)" << endl;
}

void ConsoleUI::PrintNewCutScene11Image()
{
    cout << R"(
    ....................................................    
   :            .::::.                                 ..   
   :          :*:. ..:*.                               ..   
   :         .*...::...*                               ..   
   :         .*.  .  . *                               ..   
   :         .*.       *.              ...:.           ..   
   :          *:.     :*            .::... .::         ..   
   :          :**:*:*:*.            *....... .:        ..   
   :          .*::::::*.           .*.*##:.  .:        ..   
   :       .:::.......::::.         .**#**#*:*:        ..   
   :  ..:**::::::::::::::::*::.      *##@@@@*::        ..   
   :  *.::::::::.::::::::::::::*      *##@@**:.::.     ..   
   : ::.::::::::.::::::::.:::.:*.    ::::::*:.  .::::. ..   
   : *:...::::::.:.::::::.....::*  ::.. ..#*.....  ...*..   
   :::....::::..........:.......:.:. .:..:#:..::.  .  ::.   
   :*:.. ..... ........ .... ...:*:.  ::..*..::.      .#.   
   *:.... ..   ........      ..:::#.  .........       .*.   
   *:....       .....        ...:.#.  . .:.:.          .:   
  :::... *        .   .    .:....::.     :..            :   
  *......*.      ...       ::.......     ....          .:.  
  :.....::.    ......     ..........  . ....       :..  :.  
   ::....:..... ....   .........:*..     ...       .... .:  
     .:.  ...:::.:*::*.:.... .:: *:.    ....        ... :.  
       .*   ..::*##*::*:... .*   ::*:  . ...        .:*:*   
        *.   .:*###*:.::    .:   *:::    ..          ***.   
        *....:::*##**:.  ...::   **:*   .....       .::*    
       :::..::*::::::.......:*  .*@@:     ...      :#@**    
 ......*::........  ........:::.:*#**.  .    .    :#@@**..  
 ......:*....................*:..:***:.      .... .:***:..  
 .......*.                 .::......::.     :....    *....  
  ..... ..   .    .         ...........     .. ..    . ...  

)" << endl;
}

void ConsoleUI::PrintNewCutScene12Image()
{
    cout << R"(
                                                            
                                                            
                                ....                        
                              ::....:.                      
                             .:..:.. :                      
                              :*#**:::...                   
                    .*:.     :::##@#:...:::.                
        ..    .....  .**::..::. .**::...  .::.              
       .**::.::..:*    .*:**:   :..*:...     .:.            
        :*#*:...##**. .***: :**.. ..:..   :....:.           
        ..:::  .*###*. .:**.  .*::::...   ::*:::            
        :.:::: .:###**        .:  .:::::...*:::             
        ...::.:..::::::.     .. ..:**....::** :             
         :..  ......::::::   :.*::***.    .:..::..          
            ..:...........:::::::........  :.  ..:..        
               . . . .  ...........  .....  :     ..::      
                           ..........  .... .:              
                           ...:.::::.   .... .:             
                   ..       ... ....::.   ... .:.           
                        ..     ....  :::  ..:.  :  .        
                                   :....:::....  :          
                                     .... .:  .. ..         
                                       ...      : :         
                                                            
                                                            
                                                            

)" << endl;
}

void ConsoleUI::PrintNewCutScene13Image()
{
    cout << R"(
                                                            
                                                            
                                                            
                                                 ...        
                                              ....          
           .===.                          ....         :    
           .@@@:                      ....             :    
        ---=@@@+---               ....                 :    
        %@@@@@@@@@@.          ....     ......          :    
        ===+@@@+===.       ....    .:--===-:.. ..  ....:    
           .@@@:          :      ..:-=+*++==----::..::.-    
           .+++.     .....:...      .-+###*+=++*=-:--::-    
                    .. ..... : .:...:---::.  *#%#****=--    
                          :- : :--..         **##***+=:-    
                    .  .::+= : -==.:.        *+#+++=*+:-    
                  :....=:+++ : =++:-:        ++*++=++=:-    
                .:.:.=++=:-: : =*+:-:..      +=++--==-:-    
             ..:::....=+-.   : -**:-:...     =-::::::::-    
            ::..:-:....:..:: : -++:-::..     -+-====----    
           :-:::..:....:..::.: :=-.::...     -=====---:-    
          :.::.. ...:..-: .::: :--.:.        --::::---:.    
         :.....  .  ...-....:: .-:.:.        ::::::=:.      
        :.::..   ... ::-...:.: .::...        :::::-...      
        ....::  . ...::-:... .:.:. ..        .:::::::..     
            ..::. .::.:::=:   :...:::::-::::......:....     
              . .:***=::.     .:...::-=-====-.....:         
             .   :=+=::.. .  ...:     ...::::.... :.        
             .  .  . ....:... . ..          ..:::::         
             .     . .:::::.. ..:.             .  .:        
                    ..........:=+:                .:        
               .:.::::::.:.:::::=.                          
               ...:--:..   .::--:                           
                  .....      ....                           
                                                            

)" << endl;
}

void ConsoleUI::PrintNewCutScene14Image()
{
    cout << R"(                                
                                                            
                                                            
                   .::                                      
                   --*+-                                    
                  --+***+-                                  
                 .-=*+****+-                                
            :.   --**=-=+***+-...      ...                  
             .  :=+*+=...-+**+=-:.. :=-::.--                
      ..        ==**-=   :-:=++==:..=..:.. .-               
      :=--:.   -=*#+.. ...:---+**+-:+*%**-:=.               
      :=--:-::.==#+-. ..::.=-*+##+==-+##%@*=-.              
      :====--:-=+*= :.... =-+++=:++--.:%%*++::---::         
      :==-=---==+=-.. ...:==+.  =#. -::--*#++.::::-.        
      :==---===*:-     .:::-:.. -=...:++*%*++=:-   -.       
      ::----=-+*-. :. .::=-::-. -=..+==+**=+++:..  .-:      
      . ..::=-**:  ..:-===.:..  =. =+=-*%#===: :.    :-:.   
           :-=+=:..:::===.  .:.-:  :=+=*%#++=-..+:. .       
          :--=+=  .--=====-----+. ..:=++++=+=:  .-+. .-     
      ..  :-==--::-:..  ..::::--::..-::=+-==:   =+=:   +.   
      .   ::++=. . .::::::.   ..::.....::%#--:--+=-..   .   
        . ::*+=-..:.=*=::.:-:::   .....  =##=**==:.  .::    
          :-**+::.--+++: ...   .--:  .... :--*#+.           
      .-. :-*+==+=--++*-  :...:..::=..:..  -:--:--.         
          .=**+**+=:==+:...:- ..... -. .  .-    ::--.       
          .=+*==*+*=+-=:            -.    .-      ::--.     
           ==+*+***=+==:   .        .-    .-        .:=:    
           ==++****+==-:             -    .-     .:         
           -===++++=:.               -    -.                
           ---==:.                   -.   -.                
           ...                       .:   :.                
                                                            

)" << endl;
}

void ConsoleUI::PrintNewCutScene15Image()
{
    cout << R"(
                                                                                
                                                                                
                                       .                                        
                                    ::..:.:                                     
                                   :..*#*..:                                    
                                   :.:*#*:.:                                    
                                   ..:#***.:                                    
                                   :..*##:.:.                                   
                                 .:::.....::::..                                
                              .:*:::..:::...::*:::                              
                             ::*:::*::::*:*:::.:*::                             
                            ::.:.:::*****:**.::.:.::                            
                           .::.:..::********:.:::.:::.                          
                          :... ....::::::::::...: .:::.                         
                        .:.:..  ....:*****:::..    ..:::                        
                       .:*:..    ..:::*******.. ..  ..:::                       
                      ::::.. ...: .:::::*: .:..  :.:  .:::.                     
                    .:::.  .:.:.: ...:::::.::.. .:.:.. .:::.                    
                   .::.. .. :.*.:.....::::*:... ::.:  .  .:..                   
                  :*:  ..   :......::::***:::.. . ...  .. ..::                  
                 **....     :.  ...:..................   :::#**:                
                 :....        .. :::::.:::::::::   ::::.  *.::::                
                .....           ::***:::::::****.  ...:: .:.:::                 
                 ..             ::***:.....::*##:    .:.::..                    
                               .::#**:.   ..:****:    .....:                    
                               .::**..      .:*##*.    .:..:                    
                               ::::::.       .:*##:   :.: ..                    
                               :.:*:.  ....  ..:*#*  .::.                       
                               ::*:.. .   .. .:.:**: ...                        

)" << endl;
}

void ConsoleUI::PrintNewCutScene16Image()
{
    cout << R"(
                                                            
     ...................................................    
     %@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@:   
     %@#::::::::::::::::::::::::::::::::::::::--:::::=@@:   
     %@*               ..::..                :.      -@@:   
     %@*             .-.  ..:=.              .:      -@@:   
     %@*            .:*=:.:--- :              .= .   -@@:   
     %@*            . .:-#@@@#...              *+*-  -@@:   
     %@*            .  :+#%%**#::              -@#++.-@@:   
     %@*            :.-*#*%@%%@::               +@%##+@@:   
     %@*   *- -=    ::.=@@@%%@#..  ..            +%**+@@:   
     %@* -=.#::#     ...-#@##%-=##@@%#-:.         ..++@@:   
     %@* .-*-#-%:  -##**-=:--**=%#@%##%%@%*==.  .=#%#+@@:   
     %@* ===%@@@#.=###%*-#=#%#+=#%@%##%#%%**#%#:@@%##+@@:   
     %@*   =%%%%@%*+*%*#-@=*%+*=%##%=+=#*+%@@@+#%%##*+@@:   
     %@*    =%%%#*=@#%====*+=+#=**=**. ..+##*+%#%#*##+@@:   
     %@*     .::=--%*-:=%**++++=****+=  .*%%*#%%#####+@@:   
     %@*      :=-:-:  =#%%*#++==#%@@*+  +##**+######*+@@:   
     %@*              :%*%*+=+**@%%#%*:=++=+=**##*+--+@@:   
     %@*               =##%%===#@@###%##**+**###*-.=++@@:   
     %@*               -%@@%++*##+@@@@%%##%*#*=: .+*#+@@:   
     %@*               +*@%#+#%@%+######*+--:    #+#*+@@:   
     %@*              -#%##**#%@%+*###**+        *#*#+@@:   
     %@*             =##%@**=++:*%@@%#%%@*      -####+@@:   
     %@*            -%@%%@@+ .  =@@@%%@@@@+     #@*##+@@:   
     %@*           :#@@%@@%.    .%%@@@%@@%%-    %##*#+@@:   
     %@*          .*#@@@@@+   -. =@@@@@@@@@@.  -%#%#*+@@:   
     %@*          .#@@@@@%   .-:  #@@@@@@@%-   #%####+@@:   
     %@%############################%################%@@:   
     +**************************************************.   
                                                            

)" << endl;
}

void ConsoleUI::PrintNewCutScene17Image()
{
    cout << R"( 
                                                            
         .:::::.                                            
  .::::::* ..:.*:::::::::::::::::::::::::::::::::***::::::. 
  :.     *..*#*:                               .:*:::.   .. 
  :.    .:::#**                                *:##:.*   .. 
  :. ::*:::*.:*.                               .**#:.*   .. 
  :..:.:::.::.:*                               :#*####*. .. 
  :.*....::..::::                             .*#**###@* .. 
  :::.. .:......::                            :****#**@#... 
  :*..:..::.......::**:::.........:::::::     **:::##:##:.. 
  :*.:*...:...:**...:**::**#####***::*::  .:****..*@#*##:.. 
  :*.::..::...:: ....::::.                ...##*::*@####:.. 
  :.::*..:.....*                            :#*::::#@##*:.. 
  :.:**....  ..:                            **#:*::*@#** .. 
  :.  *::....:::                             :#:*:.*@##* .. 
  :.  :.:.**.::.                             *#:*::*@##* .. 
  :.  *....*..:.                              :**:**::*  .. 
  :. .:..: *..*                               .**::****  .. 
  :. .:..: :..*                               .**::::**  .. 
  :. :..:. :..:.                              ::*:..*:*. .. 
  .::*..*::*. .:::::::::::::::::::::::::::::::#***::***:::. 
     ::::   ......                           :::..  *#*     
                                                            

)" << endl;
}

void ConsoleUI::PrintNewCutScene18Image()
{
    cout << R"(
                                                            
                                                            
                                                            
                                                            
                                                            
                             .*::                           
                             *.*                            
                           .*:::                            
           .::::::::..:**:..*:::                            
          ::.::.....:##@@@****.                             
        ..:..***##::###*#@*:.:*****:.                       
       *#*...#*#@##*#*#***#@::*##@@@#*.                     
      .#.:.  ...:.:*:::**:**#:***:**#@*:                    
     :***:::.......***::.:*#: ::::*:::**:                   
        .*#***:#:*****::*#*...::..*::::*#*:.                
      .:*::..:****:.*###...::..::.:::*: *###**::..          
      .***#**:::**:###*.    :*:.:*::**::::*:::...:*         
        ..:: .***#*:*:::.::.    :**.::..::**:::::.::.       
              .::::**::.*:*......*:*:.....::::*:*...*:      
                  .:.  :*:****:*:::::::... .::::.::..*      
                      .**:..*:::.:::::*.         .....      
                        .:::::***::.:**:                    
                             ...                            
                                                            

)" << endl;
}

void ConsoleUI::PrintNewCutScene19Image()
{
    cout << R"(
                                                            
                                                            
                                                            
                ..                                          
             .**:**:.                                       
            .*::#****:..::::.                               
            .*.***##**:..::::*:.                            
           :::  .::*.*##**::...::*::.    .:::.              
          :**: .  ...:*###:#*::....::*:*****#**             
       .:::*####*:::.:::#####*.*:.. .:****::***.            
       *****::#**.:..:...*#*####*:::****::..:***            
         .::***:.:.:. ..:.*::#*:::::::::::*:****.           
        :******: *.:. : .:.:::::*:::...::  *.:::*           
        :*******:*.:. **.. .:.::**::.::    .:...*.          
         ::::***:*.*..***...  ..:****::     :..:.::.        
        .******.*::..*:*:. ..   .:****::    :.....::**      
       .*:#**#***##.*.::.        .::***:**:::::::**:::      
        :####:******. ::: ..       .:***:***:::*:::*.       
        .*:    ::*:*:****###.    .****::::::::....:::*      
                   ::: .:*:***#**..:.    ...:::::::.::.     
                        ::.::::::.               ..:::      
                         .#*:::*::*.                        
                           ..                               

)" << endl;
}

void ConsoleUI::PrintNewCutScene20Image()
{
    cout << R"(
                                                            
                                                            
                                                            
                                                            
                     :---:.                                 
                   =+-=:.--+:                               
                  :+::--::. #                               
            .::.  :#=%%#*:.:+*+++==-:.   .::.               
          :*++*#*+**+=**%#+-=*+=*#+=***+**+=++.             
          *-:-:+=-:=+++%@#+=:--.-=-:=+:-+=:-:-+             
          -+-:=:+: =+#+=-:+-..-===++=..-+:=:=+:             
            :*-:=::=+-. . -: :=-:===--.-=:-*:               
             *::-=:....--.:- :+=-.:----:---+                
             +--=:-. --==-:=:-===-. .::-::==                
             +===-.:.:=-=:-::---==. .-::--=-                
             *-=-:..  -:=----:::=-   ..-=--==               
           .=*=-:.    .+++==+=::-:.    ..++=++:             
          :*+-:=++:  .++=-::-=+=---.  .-+**#==+:            
          +=:-==:=- :+===-...--==---. :-=:**-.-*            
          :*-::----:====-:++: ::--.:: .-:.:.::+:            
           .-+---:===--:.-+=-  ...  .. =-:::+=.             
             ==+-=---:. .-==: .:::--==.:=-+-+               
             *-* .--:.  :=-=-.=====+==-.+-*-*               
        :-:-=+:.   :..  :=--- :-------:.-:--*               
       =+----::.  :::.  .-=--.::::::::---:-:*               
        -==:.. . :=--:.. :---.-==--==--==.-:*               
           --+::::---:::.:=--.::---------:::*               
             :*-:-=-----+--:::+-------==+.:==               
              -+.*      .+.. +:         +::*                
              :+-*       +::.--         =--*    .           
               :-.      .+--::=          :-.    ..          
                        -=::.:+                             
                         :===-                              
                                                            
                                                            

)" << endl;
}

void ConsoleUI::PrintNewCutScene21Image()
{
    cout << R"(
                                                            
                                                            
                                                            
                                                            
                  -****++=.                                 
                 ++:.::::=#                                 
                 %. .:-%##-                                 
                 *-.=+%#+%.                                 
                -#:-==#%*#.                                 
               +*--:--=##:                                  
              *+:-==-::#-                                   
             -#:.++-.=::%.             .:..                 
             ++:.=-. .-:=+           =*+==+++:              
             ++:.=+. .:-:%          .%-+=.:..*-             
             =+:.-=. .:-:#.          #**#::. -+             
             -*: :-: ::-:*-         .%*@%++..#.             
             :#::.:-..:=:=+          ***===:=*              
             .#:...-- .::-*          .-%=-.==+*:            
             *+=....-:.::-*           .#::==+==#=           
             #-.  ..:=:::#.           #=-====+=-%.          
              -*:   ++*:=+           :*:=+:--=--*:          
               += . :-=-*-           *=--=:===::%.          
               .#= ::-+:%.           %::=-:=+-:-#           
                ++ :-+=+*            %.-=::--:.++           
                *=.:-*:*-           **.--+=:...*+           
               .#:::---#          .#=-:==:...--=#           
               ++.:::.#:         =#**=::...:---:#.          
               #-..-::%          #=++=..:=-==-=.*=          
               %:..:.:%          .%=:.-=-=+==--.=#+         
               #:..: :*.        .++-:=+=-:.    .::*-        

)" << endl;
}

void ConsoleUI::PrintNewCutScene22Image()
{
    cout << R"(
                                                            
                                                            
                                                            
                                                            
                         .::::.                             
                      .###*::*##*.                          
                     ##:....:...:#*                         
                    *#............#*                        
                    @*..***::**:. *#                        
                    #*.:########. *#                        
                   .@:.***:*****:.*@                        
                    ##.#*********.#*                        
                    :@*:########:*@:                        
                .:###:::*##**##*:.:###:.                    
             :###*:....::******::....:*###*.                
            ##::.......#:.::::.:#.......::*#                
           .@:.........::::::*:::.........:@:               
           #*:..........:**###::...........*#               
          .@*............*:##:*............:@.              
          ##.... ........##****........ ....*#              
          #*. ..  ........##*#........ .....:@              
         .@:..... ........:**......... .....:@:             
         :#. ...   ........... ......   .....#*             
         *#:....   ... ..  ... .. ..    .....#*             
        .@*.....    ................   ......:@.            
        .@: ....     ..   ..... ...     .... .@.            
         @*  :*#**  .... ...... ....  :***:. :@             
         *#.:##***: .... ...... ...  :**#@#:.#*             
          *#:::::**. ..  ......  ..  :***:*:#*              
           *#*::***:..  ... ....  ..:**::.:#*               
            :@:..**:*: ... .. ..  :*:*:...@*                
            #*.. .:#***:........::***:. ..*#                
           .@:.....:***##:    :##::*:......@:               
          .@*.......**####:  :#*#*#*.......*@.              
          #*:........***#****:*#*#*........:*#              
         *#...........::::.**.::::..........:#*             
        .@:..........      .:      ..........:@.            

)" << endl;
}

void ConsoleUI::PrintNewCutScene23Image()
{
    cout << R"(
                                                            
                                                            
     *:::::::::                                             
     *... .....:.                                           
     *..: ......::         ::::.                            
     *..: .......*        *... .*.                          
     *..: .......*        ##*. ..:                          
     *..: .......*        **#*::.*....                      
     * .: .......*        :*#*::*.:::.*:.                   
     * .: .......*         :**:**:.:....:*:.                
     *..: .......*         .*::*::.:.......:::              
     *..: ::..::.*  .:..   ::::*..:..  .:..:**:             
     * .: ::::::.*  #*:#.  *::.:.....  ::.#*::*             
     *..: .  .**:*  **::****.........  .*. **:*             
     *..:  . .:..*   .:::::*  . .......  ::.***.            
     *..:  ......*       :::::* ....:.... :*#*:*            
     *..: . .....*            *  ......... .*#**:           
     *.:: ...:...*            :. ....  ....:**:.            
     *::: :::..:.*            .*::...    *:.                
     *..: ..::**:*          .**:...      *                  
     *.:: :..*#*:*         **:..   ::    .:        ..:.     
     *.:: ...:*:.*        .*... ::: ::.   ::***:::::..*     
     *.::.:..:#:.*        .*.. :.    .*..  ..... .    *     
     *.:: ...:*:.*        ::.. *      .*:..:::::::::. .:    
     *..: ...:*:.*        *..  *         ..         ::.:    
     *..: ....::::       .*.. :.                     ::     
     *..: ...:::         *:.  *                             
     *... .::.      .*::**.  ::                             
     *...::.         :::..   :.                             
     *:::               .:::::                        ..    
     ..                                                     
                                                            

)" << endl;
}

void ConsoleUI::PrintNewCutScene24Image()
{
    cout << R"(                                
                                                            
                                                            
 ...**......::***:..:::::*::......*:....*.                  
 ..:*#:*****::.::::.:::***:*...:::*:....*.                  
 ..:*#**::**....**:...:*****.:.:::#:....*.                  
 ..:*#*::**::.....::.::*****...:::*:::::*.                  
 ..:*#:*::*............:****:.::::*:::***.                  
  ..**:::.:....::.......**#*::::::*:.**##.   .              
 :::**:*:....:*::.......:*#*:::**:#*.::*:   .*:             
.*****:*::  ........::::***:::::::#*::.    . .*:            
.:::**::::.. ...:.:....:****:::::*:.     :... .::           
 ..:*#::::::....***:**:********:.        :*::. ::           
 ...*#:::::*:...::::*::*****:.       .    .:....::.         
 ..:**:*:::*....:::::****:.      .         ....::*.         
 ..:***#::::....:*:*:....                    .. ::          
 ::****#:::::..:****: .....:  .                 ..          
 :::***#::*:::***:. ..:##.          ..*:.::::.              
 :*:***#*::***:.::   .*##...         .:.:..:..              
.:#****#***:.     .   .*#* .          .::**:.               
.:#*****:.         .  .:*:..            .:**#:   ...        
.:***:.               .**###::::*.    .:.::**:*::::..       
.*:.             .     .:*##@##*#:**::*:.:*::**##**:        
                 .   . .. .::***.:*#*:**:*::**:**:.         
                    ...:*.   ..:.:****##*:*#*::::           
             .         :**..:.....::******:::::..           
                        ::::::::..       ....               
                        .:***:.          :::                
                         .:.             :.                 
                                        :*  .  .            

)" << endl;
}



// 주사위
std::vector<std::string>
ConsoleUI::PrintDice1()
{
    return SplitLines(R"(
                          .........................                 
                         .:::..................   ..                
                         ::....                   ..                
                         ::..                     ..                
                         :..                      ..                
                         :.                       ..                
                         :.         .:::.         ..                
                         :.         *####.        ..                
                         :.         :###:         ..                
                         :.                       ..                
                         :.                       ..                
                         :.                       ..                
                         :.                       ..                
                         :.                       ..                
                          .........................                 
)");
}

std::vector<std::string>
ConsoleUI::PrintDice2()
{
    return SplitLines(R"(
                                                            
                                                            
                                                            
                                                            
                                                            
                                                            
                   ::::::..................                 
                  .:......                :                 
                  .:..*###.               :                 
                  .: .##@@.               :                 
                  .:   ...                :                 
                  .:                      :                 
                  .:                      :                 
                  .:                      :                 
                  .:                      :                 
                  .:               .***.  :                 
                  .:               *##@*  :                 
                  ..               .**:.  :                 
                  ..                      :                 
                   .......................                  
                                                            
                                                            
                                                            
                                                            
                                                            
)");
}

std::vector<std::string>
ConsoleUI::PrintDice3()
{
    return SplitLines(R"(
                                                            
                                                            
                                                            
                                                            
                                                            
                  .::::...................                  
                  ::.. .                 :                  
                  :. :*##.               :                  
                  :. *#@@:               :                  
                  :.  ::.                :                  
                  :         .::.         :                  
                  :.       .*###.        :                  
                  :         *#@*         :                  
                  :                      :                  
                  :               .:**:  :                  
                  :               :##@#  :                  
                  :                :*:.  :                  
                  :                      :                  
                   ......................                   
                                                            
                                                            
                                                            
                                                            
                                                            

)");
}

std::vector<std::string>
ConsoleUI::PrintDice4()
{
    return SplitLines(R"(
                                                            
                                                            
                                                            
                                                            
                                                            
                    ......................                  
                   :::.................   :                 
                   ::.....          .::.  :                 
                   :. :###*        :###*  :                 
                   :. :#@#:        .*##:  :                 
                   :.                     :                 
                   :.                     :                 
                   :.                     :                 
                   :.                     .                 
                   :   .:.          .::.  :                 
                   :. :###*        .*###  :                 
                   :  .*##:        .*##:  :                 
                   :                      :                 
                    ......................                  
                                                            
                                                            
                                                            
                                                            

)");
}

std::vector<std::string>
ConsoleUI::PrintDice5()
{
    return SplitLines(R"(
                                                            
                                                            
                                                            
                                                            
                                                            
                  .........................                 
                 .::...                   :                 
                 .:. .:::.         .:**.  :                 
                 .:. *##@*         *##@#  :                 
                 ..  :#@#.         .*##.  :                 
                 ..                       :                 
                 ..         .:**.         :                 
                 ..         *##@*         :                 
                 ..         .***.         :                 
                 ..                  .    :                 
                 ..  :*##:         .**#*  :                 
                 ..  *##@*         :##@#  :                 
                 ..  .:*:.          :::.  :                 
                 ..                       :                 
                   .......................                  
                                                            
                                                            
                                                            
                                                            
                                                            

)");
}

std::vector<std::string>
ConsoleUI::PrintDice6()
{
    return SplitLines(R"(
                                                            
                                                            
                                                            
                                                            
                                                            
                  ........................                  
                  :::..                  :                  
                  :. .***.        .***.  :                  
                  :. *##@*        :##@*  :                  
                  :. .:*:          :*:.  :                  
                  :    .            ..   :                  
                  :  :*##:        .*##*  :                  
                  :  :##@:        .##@*  :                  
                  :   .:.          ...   :                  
                  :   ...          ...   :                  
                  :  :*##:        .*##*  :                  
                  :  .#@#:        .*##:  :  ...             
                  :                      :  ...             
                   .......................                  
                                                            
                                                            
                                                            
                                                            
                                                            
                                                            

)");
}

std::vector<std::string>
ConsoleUI::PrintDiceResult(int diceValue)
{
    switch (diceValue)
    {
    case 1:
        return PrintDice1();

    case 2:
        return PrintDice2();

    case 3:
        return PrintDice3();

    case 4:
        return PrintDice4();

    case 5:
        return PrintDice5();

    case 6:
        return PrintDice6();

    default:
        return SplitLines(R"(
잘못된 주사위 값
)");
    }
}




void ConsoleUI::PrintDiceAnimationBySpeed(int delayMilliseconds)
{
    int frame = 0;

    string Frames[5] =
    {
        R"(
                                                                    
                                                            
                                                            
      ............   ..........                             
 ...........................-**=-:.                         
..........................-#%#+=--==-.                      
 .......................-#%%%*+=:..-===-.                   
 .....................-*%%%%#*===----=====:.                
 ....................+*%%%%%#+===---:---:.:=-.              
 ...................*+#+**##*=:.:--:. :--:.-=-              
 ..................=%##***%*+=-:.:---:-------:              
 .................:#%%%%%#*======----------=-.              
  ................+#+#%#*+=:::---====--...---               
    ..............#=##*+=--...:-----===-::--.               
       ..........=%##+==----------------===-.               
       ..........+#*=-:::---:..::-:....----.                
             .....===:...:--:...:--:..:--:.                 
                 ...:-=-------::-------:.                   
                      .:-----:...:---:.                     
                         ..:--::::-:.                       
                             .::-:.                         
                                                            
                                                            
                                                            
                                                            
                                                            

        )",
        R"(
                                                            
                                                            
                                                            
                                                            
                       .:.                                  
                      =%%#*=-:.                             
                     =%#**###*+=:.                          
                    =%#: .+*####*+=::.                      
                   =%##=:=*####*****+=-:.                   
                  =%%###*******=..=**++==-:.                
                 =%####**-::***- :=**+=-====-               
                -%#=-=**+. :+*******+-.:====:               
               :%#+ ..***++********+=::-===:                
               +##*==*******+*****+=--:-==:                 
               .-+********=. .+**+=--..-=-                  
                  .:-+****+:.=**+=-----=-                   
                      .-=+*****+=-==-::-                    
                         .:-++==--==:.:                     
                             .::-----:                      
                                  ...                       
                                                            
                                                            

        )",
        R"(
                                                            
                                                            
                                                            
                                                            
                                                            
                    .:::...                                 
                   #%%%%%%%%%###**++==-:                    
                  =@%*-:=#########*###**+-                  
                  %%#. .:######*-  :##*+==+:                
                 -@%#*==*######*: :+#**+::=+=.              
                 #%%#####*=-=####*###**=.:==++              
                :@%#####*-  :+#######*+=--====              
                +%%######+::+#######**+==-===-              
                %%#-..=#######*++###**==-.-==:              
               -@%*  :=######+. .-#**+==-.-==.              
               +%%#*++#######+. -*#*++==--==-               
               +###***########**##**+=====-=:               
                -++---====+++++++++======- -.               
                  -+=-::---::--------====:.-                
                    -+=---::..:::::::--==--.                
                      .:::::::::::....:----                 
                                    ......                  
                                                            
                                                            
                                                 :          
                                                            
                                                            
                                                            

        )",
        R"(
                                                            
                                                            
                                                            
                                                            
                                                            
                                                            
                         :-====-::.                         
                       -#%*::*######*+=-.                   
                     =#%####*+*########*+:                  
                   =#%######--*######**+==.                 
                 .#%#########*==####*+=-.:-                 
                 +%##########*=+***+===-.-=                 
                 **+++++++*****++==========.                
                 =*++======-:-=====-==--===:                
                 -*++======- .-======- :===:                
                  #++===::-==========-:-===:                
                  +*+===:.:===============-                 
                  :*=..=================-:                  
                   -+-:-===============-.                   
                     :--=============-.                     
                          ..::-----:.                       
                                                            
                                             ..             
                                                            
                                                            
                                                            

        )",
        R"(
                                                            
                                                            
                                                            
                                                            
                                                            
                       .-==--:.                             
                     :*%@@@@%%%%#+-.                        
                    +%++%@@@@@%%#*++=-.                     
                  .*%+=%@@@%@%%#*+======:.                  
                 .*@%%%%%@@%@%%*+=-:.-=====:                
                .*@@%%+-%@@@%%*+==.. .-======-.             
               .*@@%%+-#@@@%%*+===-..---=======-.           
              .#@%%@%%%%%@%%*+===-----------::===.          
             .*@%%@@%%#=#%%*+==------------.  :-=:          
             =@%%@@%%*:+%%*+==------.  :---...:==.          
             #%%%%%%%%#%#*+=-..:----.  :-------=:           
             =####%%%%##*==-:.  -----:-------==:            
              :====+++++==---:::-------------=:             
                .::---::--------------::----=:              
                  .:---:::-----------.  .--=:               
                     .:-:::----------:..:--:                
                        ...:--::----------.                 
                           ..::::::-----:.                  
                                  .....                     
                                                 :.         
                                                            
                                                            
                                                            

        )"
    };

    int FrameCount = 5;

    // 키보드 입력이 들어올 때까지 계속 주사위 애니메이션 재생
    while (!_kbhit())
    {
        system("cls");

        // 현재 프레임 인덱스 변수
        int currentFrame = frame % FrameCount;

        // 현재 프레임 아스키 이미지 출력 코드
        cout << CYAN << BOLD;
        cout << Frames[currentFrame] << endl;
        cout << RESET;

        // 프레임 증가 코드
        frame++;

        // 프레임 간 대기 시간 코드
        this_thread::sleep_for(chrono::milliseconds(delayMilliseconds));
    }

    // 버퍼에 남아있는 키 입력 소모
    _getch();
}
/*
    // 주사위 애니메이션 속도 조절 사용예시

    // delayMilliseconds 값이 클수록 애니메이션이 느려집니다.
    // delayMilliseconds 값이 작을수록 애니메이션이 빨라집니다.

    // 예시)
    // 700ms : 느린 애니메이션
    // 300ms : 보통 속도 애니메이션
    // 150ms : 빠른 애니메이션

    int main()
    {
        // 느린 주사위 애니메이션 실행
        ConsoleUI::PrintDiceAnimationBySpeed(700);

        // 빠른 주사위 애니메이션 실행
        ConsoleUI::PrintDiceAnimationBySpeed(100);

        return 0;
    }
*/


// 추가 목록 들 기존의 함수와 중복되는 것들 있는지 확인 부탁드립니다.
// 기존의 함수들이 많아 그냥 수정된 버전으로 다시 만들었습니다.

// [추가] 전투 시작 출력 함수
void ConsoleUI::PrintBattleStart(GameContext& context)
{
    Player& player = context.GetPlayer();
    Monster& monster = context.GetMonster();

    PrintLine();
    cout << "전투 시작!" << endl;
    cout << "플레이어: " << player.GetName() << endl;
    cout << "상대: " << monster.GetName() << endl;
    PrintLine();
}


void ConsoleUI::PrintAct1Cutscene()
{
    ShowCutScene1();
}

void ConsoleUI::PrintAct2Cutscene()
{
    ShowCutScene2();
}

void ConsoleUI::PrintAct3Cutscene()
{
    ShowCutScene3();
}

void ConsoleUI::PrintEnding()
{
    PrintLine();
    PrintTitle("엔딩");
    PrintLine();
    PrintMessage("게임이 종료되었습니다.");
    PrintLine();
}

void ConsoleUI::PrintPlayerStatus(GameContext& context)
{
    PrintPlayerStatusEveryTime(context);
}

//컷신 화면 나누기
void ConsoleUI::PrintFixedWidthText(const std::string& text, int width)
{
    std::string output = text;

    if ((int)output.length() > width)
    {
        output = output.substr(0, width);
    }

    std::cout << std::left << std::setw(width) << output;
}

void ConsoleUI::DrawCutSceneScreen(
    const std::vector<std::string>& sceneLines,
    const std::vector<std::string>& dialogueLines
)
{
    ClearScreen();

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    int consoleWidth = 120;
    int consoleHeight = 35;

    if (GetConsoleScreenBufferInfo(hConsole, &csbi))
    {
        consoleWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        consoleHeight = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    }

    // 좌우 테두리 2칸을 제외한 실제 내용 폭
    int screenWidth = consoleWidth - 2;

    // 최소 크기 보정
    if (screenWidth < 40)
    {
        screenWidth = 40;
    }

    if (consoleHeight < 20)
    {
        consoleHeight = 20;
    }

    // 전체 출력 줄 수 계산
    // 위/중간/아래 테두리 3줄 + 대기 문구 공간 약 2줄을 제외
    int usableHeight = consoleHeight - 5;

    // 상단 컷신 영역 약 2/3
    int sceneHeight = usableHeight * 2 / 3;

    // 하단 대사 영역 약 1/3
    int dialogueHeight = usableHeight - sceneHeight;

    // 너무 작아지는 것 방지
    if (sceneHeight < 10)
    {
        sceneHeight = 10;
    }

    if (dialogueHeight < 5)
    {
        dialogueHeight = 5;
    }

    std::cout << "+" << std::string(screenWidth, '-') << "+" << std::endl;

    // 상단 컷신 영역
    for (int i = 0; i < sceneHeight; i++)
    {
        std::cout << "|";

        if (i < static_cast<int>(sceneLines.size()))
        {
            PrintFixedWidthText(sceneLines[i], screenWidth);
        }
        else
        {
            PrintFixedWidthText("", screenWidth);
        }

        std::cout << "|" << std::endl;
    }

    std::cout << "+" << std::string(screenWidth, '-') << "+" << std::endl;

    // 하단 대사 영역
    for (int i = 0; i < dialogueHeight; i++)
    {
        std::cout << "|";

        if (i == 0)
        {
            PrintFixedWidthText("[대사]", screenWidth);
        }
        else if (i - 1 < static_cast<int>(dialogueLines.size()))
        {
            PrintFixedWidthText(dialogueLines[i - 1], screenWidth);
        }
        else
        {
            PrintFixedWidthText("", screenWidth);
        }

        std::cout << "|" << std::endl;
    }

    std::cout << "+" << std::string(screenWidth, '-') << "+" << std::endl;
}



    

void ConsoleUI::DrawGameScreen(
    const std::vector<std::string>& cutSceneLines,
    const std::vector<std::string>& logLines,
    const std::vector<std::string>& statusLines,
    const std::vector<std::string>& monsterstatus,
    const std::vector<std::string>& choiceLines
)
{
    MoveCursor(0, 0);

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    int consoleWidth = 120;
    int consoleHeight = 35;

    if (GetConsoleScreenBufferInfo(hConsole, &csbi))
    {
        consoleWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        consoleHeight = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    }

    // 콘솔 끝까지 꽉 채우면 자동 줄바꿈이 생길 수 있으므로 여유를 둠
    int totalWidth = consoleWidth - 6;
    int totalHeight = consoleHeight - 4;

    if (totalWidth < 80)
    {
        totalWidth = 80;
    }

    if (totalHeight < 24)
    {
        totalHeight = 24;
    }

    int leftWidth = totalWidth / 2;
    int rightWidth = totalWidth - leftWidth - 1;

    int topHeight = totalHeight * 2 / 3;
    int bottomHeight = totalHeight - topHeight;

    auto PrintCell = [](const std::string& text, int width)
        {
            std::string output = text;

            if ((int)output.length() > width)
            {
                output = output.substr(0, width);
            }

            std::cout << output;

            int padding = width - static_cast<int>(output.length());

            if (padding < 0)
            {
                padding = 0;
            }

            std::cout << std::string(padding, ' ');
        };

    auto PrintBorder = [&]()
        {
            std::cout
                << "+"
                << std::string(leftWidth, '=')
                << "+"
                << std::string(rightWidth, '=')
                << "+"
                << std::endl;
        };

    PrintBorder();

    // 상단 영역: 컷신 / 게임 로그
    for (int i = 0; i < topHeight; i++)
    {
        std::cout << "|";

        if (i == 0)
        {
            PrintCell("[컷신 / 렌더링]", leftWidth);
        }
        else if (i - 1 < static_cast<int>(cutSceneLines.size()))
        {
            PrintCell(cutSceneLines[i - 1], leftWidth);
        }
        else
        {
            PrintCell("", leftWidth);
        }

        std::cout << "||";

        if (i == 0)
        {
            PrintCell("[게임 로그]", rightWidth);
        }
        else if (i - 1 < static_cast<int>(logLines.size()))
        {
            PrintCell(logLines[i - 1], rightWidth);
        }
        else
        {
            PrintCell("", rightWidth);
        }

        std::cout << "|" << std::endl;
    }

    PrintBorder();

    // 하단 영역: 선택창 / 플레이어 상태 + 몬스터 상태
    int playerStatusWidth = rightWidth / 2;
    int monsterStatusWidth = rightWidth - playerStatusWidth - 1;

    for (int i = 0; i < bottomHeight; i++)
    {
        std::cout << "|";

        // 왼쪽 하단: 선택창
        if (i == 0)
        {
            PrintCell("[선택창]", leftWidth);
        }
        else if (i - 1 < static_cast<int>(choiceLines.size()))
        {
            PrintCell(choiceLines[i - 1], leftWidth);
        }
        else
        {
            PrintCell("", leftWidth);
        }

        std::cout << "||";

        // 오른쪽 하단 내부 왼쪽: 플레이어 스테이터스
        if (i == 0)
        {
            PrintCell("[플레이어]", playerStatusWidth);
        }
        else if (i - 1 < static_cast<int>(statusLines.size()))
        {
            PrintCell(statusLines[i - 1], playerStatusWidth);
        }
        else
        {
            PrintCell("", playerStatusWidth);
        }

        std::cout << "|";

        // 오른쪽 하단 내부 오른쪽: 몬스터 스테이터스
        if (i == 0)
        {
            PrintCell("[몬스터]", monsterStatusWidth);
        }
        else if (i - 1 < static_cast<int>(monsterstatus.size()))
        {
            PrintCell(monsterstatus[i - 1], monsterStatusWidth);
        }
        else
        {
            PrintCell("", monsterStatusWidth);
        }

        std::cout << "|" << std::endl;
    }

    PrintBorder();

    

}

void ConsoleUI::Render(const ScreenBuffer& buffer)
{
    int width = buffer.GetWidth();
    int height = buffer.GetHeight();

    std::vector<CHAR_INFO> consoleBuffer(width * height);

    const auto& cells = buffer.GetBuffer();

    for (int i = 0; i < cells.size(); i++)
    {
        consoleBuffer[i].Char.UnicodeChar = cells[i].ch;
        consoleBuffer[i].Attributes = cells[i].color;
    }

    COORD bufferSize =
    {
        (SHORT)width,
        (SHORT)height
    };

    COORD bufferCoord = { 0,0 };

    SMALL_RECT writeRegion =
    {
        0,
        0,
        (SHORT)(width - 1),
        (SHORT)(height - 1)
    };

    WriteConsoleOutputW(
        hConsole,
        consoleBuffer.data(),
        bufferSize,
        bufferCoord,
        &writeRegion);
}


// 게임 로그 반환

// 전투 로그 총괄
void ConsoleUI::AddLog(
    std::vector<std::string>& logs,
    const std::string& text)
{
    logs.push_back(text);

    if (logs.size() > 12)
    {
        logs.erase(logs.begin());
    }
}


// 일반 공격 로그
std::string
ConsoleUI::PrintPlayerMeleeAttackResultMessage(
    const std::string& playerName,
    const std::string& monsterName,
    int damage)
{
    return playerName +
        "의 공격! " +
        monsterName +
        "에게 " +
        std::to_string(damage) +
        " 데미지!";
}


// 스킬 공격 로그
std::string
ConsoleUI::PrintPlayerSkillAttackResultMessage(
    const std::string& playerName,
    const std::string& monsterName,
    int damage)
{
    return playerName +
        "의 스킬 공격! " +
        monsterName +
        "에게 " +
        std::to_string(damage) +
        " 데미지!";
}

// mp 부족
std::string
ConsoleUI::PrintNotEnoughMp()
{
    return "MP가 부족합니다.";
}


// 스턴 성공
std::string
ConsoleUI::PrintStunSuccess(
    const std::string& monsterName)
{
    return monsterName +
        " 스턴 성공!";
}

// 몬스터 스턴 상태 출력
std::string
ConsoleUI::PrintMonsterStunned(
    const std::string& monsterName)
{
    return monsterName +
        "은(는) 기절 상태입니다.";
}


// 받은 데미지 로그
std::string
ConsoleUI::PrintMonsterAttackResult(
    const std::string& monsterName,
    const std::string& playerName,
    int damage)
{
    return monsterName +
        "의 공격! " +
        playerName +
        "에게 " +
        std::to_string(damage) +
        " 데미지!";
}


// 도망 성공
std::string
ConsoleUI::PrintRunawaySuccess()
{
    return "도망에 성공했습니다.";
}


// 도망 실패
std::string
ConsoleUI::PrintRunawayFail()
{
    return "도망에 실패했습니다.";
}

// 승리
std::string
ConsoleUI::PrintBattleVictory(
    const std::string& monsterName)
{
    return monsterName +
        " 처치 성공!";
}

// 패배
std::string
ConsoleUI::PrintBattleDefeat(
    const std::string& playerName)
{
    return playerName +
        "이(가) 쓰러졌습니다.";
}

// 리워드
std::string
ConsoleUI::PrintReward(
    int exp,
    int gold)
{
    return "EXP +" +
        std::to_string(exp) +
        " / GOLD +" +
        std::to_string(gold);
}

// 렙업
std::string
ConsoleUI::PrintLevelUp(
    const std::string& playerName,
    int level)
{
    return playerName +
        " Level Up! Lv." +
        std::to_string(level);
}

//감나빗
std::string
ConsoleUI::PrintAttackMiss()
{
    return "공격이 빗나갔습니다.";
}

// 박스 크기 고정
void ConsoleUI::DrawFrame(
    int width,
    int height)
{
    std::cout << "┌";

    for (int i = 0; i < width - 2; ++i)
    {
        std::cout << "─";
    }

    std::cout << "┐\n";

    for (int y = 0; y < height - 2; ++y)
    {
        std::cout << "│";

        for (int x = 0; x < width - 2; ++x)
        {
            std::cout << " ";
        }

        std::cout << "│\n";
    }

    std::cout << "└";

    for (int i = 0; i < width - 2; ++i)
    {
        std::cout << "─";
    }

    std::cout << "┘\n";
}


void ConsoleUI::DrawFullLayout(const UIScreen& screen)
{
    ClearScreen();
    MoveCursor(0, 0);

    const int leftWidth = 75;
    const int rightWidth = 75;

    const int topHeight = 22;
    const int bottomHeight = 14;

    auto FitText =
        [](const std::string& text, int width)
        {
            std::string output = text;

            if ((int)output.size() > width)
            {
                output = output.substr(0, width);
            }

            output +=
                std::string(
                    width - output.size(),
                    ' '
                );

            return output;
        };

    // ✅ screen 기준으로 연결
    const auto& leftTop = screen.a;
    const auto& rightTop = screen.b;
    const auto& leftBottom = screen.c;
    const auto& rightBottom = screen.d;

    // 상단 프레임
    std::cout
        << "┌"
        << Repeat("─", leftWidth)
        << "┬"
        << Repeat("─", rightWidth)
        << "┐\n";

    // 상단 내용
    for (int i = 0; i < topHeight; i++)
    {
        std::string left =
            (i < leftTop.size()) ?
            leftTop[i] : "";

        std::string right =
            (i < rightTop.size()) ?
            rightTop[i] : "";

        std::cout
            << "│"
            << FitText(left, leftWidth)
            << "│"
            << FitText(right, rightWidth)
            << "│\n";
    }

    // 중간 프레임
    std::cout
        << "├"
        << Repeat("─", leftWidth)
        << "┼"
        << Repeat("─", rightWidth)
        << "┤\n";

    // 하단 내용
    for (int i = 0; i < bottomHeight; i++)
    {
        std::string left =
            (i < leftBottom.size()) ?
            leftBottom[i] : "";

        std::string right =
            (i < rightBottom.size()) ?
            rightBottom[i] : "";

        std::cout
            << "│"
            << FitText(left, leftWidth)
            << "│"
            << FitText(right, rightWidth)
            << "│\n";
    }

    // 하단 프레임
    std::cout
        << "└"
        << Repeat("─", leftWidth)
        << "┴"
        << Repeat("─", rightWidth)
        << "┘\n";
}

std::string ConsoleUI::Repeat(const std::string& text, int count)
{
    std::string result;

    for (int i = 0; i < count; i++)
    {
        result += text;
    }

    return result;
}


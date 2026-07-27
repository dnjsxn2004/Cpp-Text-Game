#pragma once

#include "Player.h"
#include "Monster.h"
#include "Inventory.h"

// GameContext
// 
// 역할:
// - 게임 전체에서 공유해야 하는 객체와 상태를 보관하는 클래스
// - Player, Monster, Inventory 같은 공통 객체를 가지고 있습니다.
// - 각 시스템은 GameContext& context를 매개변수로 받아
//   필요한 객체에 접근
// 
// 규칙:
// 1. Player, Monster, Inventory 객체는 각 시스템에서 새로 만들지 않는다
// 2. 공통으로 사용해야 하는 객체는 GameContext에 저장
// 3. 각 시스템은 GameContext& context를 매개변수로 받는다
// 4. 필요한 객체는 GetPlayer(), GetMonster(), GetInventory()로 가져온다
// 5. 값을 수정해야 하면 GameContext&를 사용합니다.
// 6. 값만 읽으면 const GameContext&를 사용합니다.

class GameContext
{
public:
    GameContext()
        : isRunning(true),
        isGameOver(false),
        player(),
        monster(),
        inventory()
    {
    }


    // [공통 / 게임 진행 상태] 멤버 함수

    bool IsGameRunning() const;
    void SetGameRunning(bool isRunning);

    bool IsGameOver() const;
    void SetGameOver(bool isGameOver);

    // [Player] 접근 함수
    
    // 플레이어 객체를 가져온다
    // HP, 공격력, 골드, 이름, 직업 등은 Player 클래스에서 관리

    Player& GetPlayer();

    // [Monster] 접근 함수
    
    // 몬스터 객체를 가져온다
    // 몬스터 HP, 공격력, 보상 골드 등은 Monster 클래스에서 관리

    Monster& GetMonster();

    // [Inventory] 접근 함수
 
    // 인벤토리 객체를 가져온다.
    // 포션 개수, 아이템 개수 등은 Inventory 클래스에서 관리


    Inventory& GetInventory();

private:

    // [공통 / 게임 진행 상태] 멤버 변수
 

    bool isRunning;
    bool isGameOver;


    // [공통 객체] 멤버 변수

    // 게임 전체에서 공유하는 실제 데이터 객체
    // 각 시스템은 이 객체들을 직접 새로 만들지 않고,
    // GameContext의 Get 함수로 접근


    Player player;
    Monster monster;
    Inventory inventory;
};

// GameContext 사용법 예시

// [1] Player 사용 예시

// 플레이어 HP를 10 감소시키는 예시

// void PlayerSystem::DamagePlayer(GameContext& context)
// {
//     Player& player = context.GetPlayer();
//
//     int damage = 10;
//     player.SetHp(player.GetHp() - damage);
// }
//
// [2] Monster 사용 예시

// 몬스터 HP를 20 감소시키는 예시
//
// void SomeSystem::DamageMonster(GameContext& context)
// {
//     Monster& monster = context.GetMonster();
//
//     int damage = 20;
//     monster.SetHp(monster.GetHp() - damage);
// }
//
// [3] Battle 사용 예시

// 플레이어가 몬스터를 공격하는 전투 예시
//
// void BattleSystem::PlayerAttack(GameContext& context)
// {
//     Player& player = context.GetPlayer();
//     Monster& monster = context.GetMonster();
//
//     int damage = player.GetAttack();
//     monster.SetHp(monster.GetHp() - damage);
//
//     if (monster.GetHp() <= 0)
//     {
//         player.SetGold(player.GetGold() + monster.GetRewardGold());
//     }
// }
//
// [4] Inventory 사용 예시

// HP 포션을 사용해서 플레이어 체력을 회복하는 예시입니다.
//
// void InventorySystem::UseHpPotion(GameContext& context)
// {
//     Player& player = context.GetPlayer();
//     Inventory& inventory = context.GetInventory();
//
//     if (inventory.GetHpPotionCount() <= 0)
//     {
//         return;
//     }
//
//     inventory.SetHpPotionCount(inventory.GetHpPotionCount() - 1);
//     player.SetHp(player.GetHp() + 30);
// }


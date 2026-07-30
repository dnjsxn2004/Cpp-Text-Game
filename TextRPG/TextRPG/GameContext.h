// GameContext
// 
// ����:
// - ���� ��ü���� �����ؾ� �ϴ� ��ü�� ���¸� �����ϴ� Ŭ����
// - Player, Monster, Inventory ���� ���� ��ü�� ������ �ֽ��ϴ�.
// - �� �ý����� GameContext& context�� �Ű������� �޾�
//   �ʿ��� ��ü�� ����
// 
// ��Ģ:
// 1. Player, Monster, Inventory ��ü�� �� �ý��ۿ��� ���� ������ �ʴ´�
// 2. �������� ����ؾ� �ϴ� ��ü�� GameContext�� ����
// 3. �� �ý����� GameContext& context�� �Ű������� �޴´�
// 4. �ʿ��� ��ü�� GetPlayer(), GetMonster(), GetInventory()�� �����´�
// 5. ���� �����ؾ� �ϸ� GameContext&�� ����մϴ�.
// 6. ���� ������ const GameContext&�� ����մϴ�.

#pragma once

#include "Player.h"
#include "Monster.h"
#include "Inventory.h"

class GameContext
{
public:
    GameContext();
    ~GameContext();

    // Player*를 직접 들고 있으므로 복사 금지
    GameContext(const GameContext&) = delete;
    GameContext& operator=(const GameContext&) = delete;

public:
    bool IsGameRunning() const;
    void SetGameRunning(bool isRunning);

    bool IsGameOver() const;
    void SetGameOver(bool isGameOver);

    // 일반 게임 로직용: 플레이어가 반드시 있다고 가정
    Player& GetPlayer();
    const Player& GetPlayer() const;

    // nullptr 체크가 필요한 곳에서 사용
    Player* GetPlayerPtr();
    const Player* GetPlayerPtr() const;

    // 캐릭터 선택/교체용
    void SetPlayer(Player* newPlayer);
    bool HasPlayer() const;

    Monster& GetMonster();
    const Monster& GetMonster() const;
    void SetMonster(const Monster& monster);

    Inventory& GetInventory();
    const Inventory& GetInventory() const;

private:
    bool isRunning;
    bool isGameOver;

    Player* player;
    Monster monster;
    Inventory inventory;
};



// GameContext ���� ����

// [1] Player ��� ����

// �÷��̾� HP�� 10 ���ҽ�Ű�� ����

// void PlayerSystem::DamagePlayer(GameContext& context)
// {
//     Player& player = context.GetPlayer();
//
//     int damage = 10;
//     player.SetHp(player.GetHp() - damage);
// }
//
// [2] Monster ��� ����

// ���� HP�� 20 ���ҽ�Ű�� ����
//
// void SomeSystem::DamageMonster(GameContext& context)
// {
//     Monster& monster = context.GetMonster();
//
//     int damage = 20;
//     monster.SetHp(monster.GetHp() - damage);
// }
//
// [3] Battle ��� ����

// �÷��̾ ���͸� �����ϴ� ���� ����
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
// [4] Inventory ��� ����

// HP ������ ����ؼ� �÷��̾� ü���� ȸ���ϴ� �����Դϴ�.
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


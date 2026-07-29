#pragma once

#include "Player.h"
#include "Monster.h"
#include "Inventory.h"

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


    // [���� / ���� ���� ����] ��� �Լ�

    bool IsGameRunning() const;
    void SetGameRunning(bool isRunning);

    bool IsGameOver() const;
    void SetGameOver(bool isGameOver);

    // [Player] ���� �Լ�
    
    // �÷��̾� ��ü�� �����´�
    // HP, ���ݷ�, ���, �̸�, ���� ���� Player Ŭ�������� ����

    Player& GetPlayer();

    // [Monster] ���� �Լ�
    
    // ���� ��ü�� �����´�
    // ���� HP, ���ݷ�, ���� ��� ���� Monster Ŭ�������� ����

    Monster& GetMonster();

    // [Inventory] ���� �Լ�
 
    // �κ��丮 ��ü�� �����´�.
    // ���� ����, ������ ���� ���� Inventory Ŭ�������� ����


    Inventory& GetInventory();

private:

    // [���� / ���� ���� ����] ��� ����
 

    bool isRunning;
    bool isGameOver;


    // [���� ��ü] ��� ����

    // ���� ��ü���� �����ϴ� ���� ������ ��ü
    // �� �ý����� �� ��ü���� ���� ���� ������ �ʰ�,
    // GameContext�� Get �Լ��� ����


    Player player;
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


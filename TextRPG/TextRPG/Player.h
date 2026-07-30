#pragma once
#include <string>
#include "StatBonus.h"

class Player
{
protected:
    std::string name;
    int Hp = 200;
    int Mp = 100;
    int MaxHp = 200;
    int MaxMp = 100;
    int Level = 1;
    int MaxLevel = 10;
    int Attack = 30;
    int Exp = 0;
    int MaxExp = 100;
    int Defense = 10;
    int Gold = 0;
    StatBonus PotionBonus;
    StatBonus EquipBonus;
    int PotionEffectCount = 0;
    int Str = 0;
    int Dex = 0;
    int Intel = 0;
    int Luk = 0;
    bool PotionCheck = false;

public:

    Player();          // 기본 생성자
    virtual ~Player(); // 가상 소멸자

    // Getter 선언
    std::string GetName() const;
    int GetHp() const;
    int GetMaxHp() const;
    int GetMp() const;
    int GetMaxMp() const;
    int GetLevel() const;
    int GetMaxLevel() const;
    int GetAttack() const;
    int GetExp() const;
    int GetMaxExp() const;
    int GetDefense() const;
    int GetGold() const;
    int GetPotionEffectCount() const;
    int GetStr() const;
    int GetDex() const;
    int GetIntel() const;
    int GetLuk() const;

    // Setter 선언
    void SetName(const std::string& newName);
    void SetHp(int newHp);
    void SetMaxHp(int newMaxHp);
    void SetMp(int newMp);
    void SetMaxMp(int newMaxMp);
    void SetLevel(int newLevel);
    void SetMaxLevel(int newMaxLevel);
    void SetAttack(int newAttack);
    void SetExp(int newExp);
    void SetMaxExp(int newMaxExp);
    void SetDefense(int newDefense);
    void SetGold(int newGold);
    void SetPotionBonus(StatBonus newPotionBonus);
    void SetEquipBonus(StatBonus newEquipBonus);
    void SetPotionEffectCount(int value);
    void SetStr(int value);
    void SetDex(int value);
    void SetIntel(int value);
    void SetLuk(int value);


    //LevelUp 관련
    bool IsLevelUpCheck(int NewExp); // 조건 만족 시, 레벨 업 적용 함수
    void GainExp(int Exp); // 경험치 획득 함수

    //실적용 데미지 관련 함수
    virtual int GetMeleeDamage(const StatBonus& equipBonus, const StatBonus& potionBonus); // 평타 (Str과 Dex기반 보너스 적용)
    virtual int GetSkillDamage(const StatBonus& equipBonus, const StatBonus& potionBonus); // 스킬 (Intel과 Luk기반 보너스 적용) 
    virtual int GetTrueDefense(const StatBonus& equipBonus, const StatBonus& potionBonus); // 실적용 방어력

    //장비 보너스 적용 / 포션 보너스 적용 여부
    void ApplyEquipBonus(bool EquipCheck, StatBonus Bonus); //장비 착용 확인(bool을 통해 체크 / 착용하지 않을 시 보너스를 0으로 초기화) 후, 장비 보너스를 세트하는 함수
    void DrinkPotion(StatBonus AppliedBonus); //포션을 마셨을 때, 지속 시간과 보너스를 적용하는 함수.
    void UpdatePotionTurn();  //포션 지속 확인(count > 0 일시 / 지속 시간이 0 이하일 시 보너스를 0으로 초기화) 함수.
    void ApplyEquipHpMpBonus(bool IsEquip, StatBonus Bonus); //장비 착용 여부 확인 후, 최대 Hp와 최대 Mp 및 현재 Hp, Mp 보너스 적용 함수.

};
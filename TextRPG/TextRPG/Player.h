#pragma once
#include <string>

struct StatBonus
{
    int hp = 0;
    int mp = 0;
    int str = 0;
    int def = 0;
    int dex = 0;
    int intel = 0;
    int luk = 0;

    // 편하게 값을 넣기 위한 생성자 추가
    StatBonus(int _hp = 0, int _mp = 0, int _str = 0, int _def = 0, int _dex = 0, int _intel = 0, int _luk = 0)
        : hp(_hp), mp(_mp), str(_str), def(_def), dex(_dex), intel(_intel), luk(_luk) {
    }
};


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

public:

    Player();          // 기본 생성자
    virtual ~Player(); // ★ 상속을 위한 가상 소멸자 (필수)

    // Getter 선언 (멤버 변수를 변경하지 않으므로 const 키워드 사용)
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
    int GetPotionBonus() const;
    int GetEquipBonus() const;
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
    bool IsLevelUpCheck(int NewExp);

    //실질적 데미지 관련 함수
    virtual int GetMeleeDamage(const StatBonus& bonus); // 평타
    virtual int GetSkillDamage(const StatBonus& bonus); // 스킬

};
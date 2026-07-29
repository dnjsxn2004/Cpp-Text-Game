#pragma once
#include <string>

struct StatBonus // 장비와 포션을 통해 얻는 보너스를 넣기 위한 구조체
{
    int hp = 0;
    int mp = 0;
    int str = 0;
    int att = 0;
    int def = 0;
    int dex = 0;
    int intel = 0;
    int luk = 0;

    StatBonus operator+(const StatBonus& other) const // 장비 보너스와 포션 보너스를 합쳐서 계산하기 위한 코드
    {
        StatBonus result;
        result.hp = hp + other.hp;
        result.mp = mp + other.mp;
        result.str = str + other.str;
        result.att = att + other.att;
        result.def = def + other.def;
        result.dex = dex + other.dex;
        result.intel = intel + other.intel;
        result.luk = luk + other.luk;
        return result;
    }

    // 편하게 값을 넣기 위한 생성자 추가
    StatBonus(int _hp = 0, int _mp = 0, int _str = 0, int _att = 0, int _def = 0, int _dex = 0, int _intel = 0, int _luk = 0)
        : hp(_hp), mp(_mp), str(_str), att(_att), def(_def), dex(_dex), intel(_intel), luk(_luk) {
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

    //장비 보너스 적용 / 포션 보너스 적용 여부
    void ApplyEquipBonus(bool EquipCheck, StatBonus Bonus); //장비 착용 확인(bool을 통해 체크 / 착용하지 않을 시 보너스를 0으로 초기화) 후, 장비 보너스를 세트하는 함수
    void ApplyPotionBonus(int Count, StatBonus Bonus);  //포션 지속 확인(count > 0 일시 / 지속 시간이 0 이하일 시 보너스를 0으로 초기화) 후, 포션 보너스를 세트하는 함수


};
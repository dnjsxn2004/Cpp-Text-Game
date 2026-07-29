#include "Player.h"

// Player 객체가 직접 생성될 때의 기본 세팅
Player::Player()
{
    name = "Player";
}

// 가상 소멸자 구현부 (비워두어도 됨)
Player::~Player()
{

}

// Getter 구현
std::string Player::GetName() const {
    return name;
}

int Player::GetHp() const {
    return Hp;
}

int Player::GetMaxHp() const {
    return MaxHp;
}

int Player::GetMp() const {
    return Mp;
}

int Player::GetMaxMp() const {
    return MaxMp;
}

int Player::GetLevel() const {
    return Level;
}

int Player::GetMaxLevel() const {
    return MaxLevel;
}

int Player::GetAttack() const {
    return Attack;
}

int Player::GetExp() const {
    return Exp;
}

int Player::GetMaxExp() const {
    return MaxExp;
}

int Player::GetDefense() const {
    return Defense;
}

int Player::GetGold() const {
    return Gold;
}

int Player::GetPotionEffectCount() const {
    return PotionEffectCount;
}

int Player::GetStr() const {
    return Str;
}

int Player::GetDex() const {
    return Dex;
}

int Player::GetIntel() const {
    return Intel;
}

int Player::GetLuk() const {
    return Luk;
}


// Setter 구현
void Player::SetName(const std::string& newName) {
    name = newName;
}

void Player::SetHp(int newHp) {
    Hp = newHp;
    if (Hp > GetMaxHp())
    {
        Hp = GetMaxHp();
    }
    if (Hp < 0)
    {
        Hp = 0;
    }
}

void Player::SetMaxHp(int newMaxHp) {
    MaxHp = newMaxHp;
}

void Player::SetMp(int newMp) {
    Mp = newMp;
    if (Mp > GetMaxMp())
    {
        Mp = GetMaxMp();
    }
    if (Mp < 0)
    {
        Mp = 0;
    }
}

void Player::SetMaxMp(int newMaxMp) {
    MaxMp = newMaxMp;
}

void Player::SetLevel(int newLevel) {
    Level = newLevel;
}

void Player::SetMaxLevel(int newMaxLevel) {
    MaxLevel = newMaxLevel;
}

void Player::SetAttack(int newAttack) {
    Attack = newAttack;
}

void Player::SetExp(int newExp) {
    Exp = newExp;
}

void Player::SetMaxExp(int newMaxExp) {
    MaxExp = newMaxExp;
}

void Player::SetDefense(int newDefense) {
    Defense = newDefense;
}

void Player::SetGold(int newGold) {
    Gold = newGold;
}

void Player::SetPotionBonus(StatBonus value) {
    PotionBonus = value;
}

void Player::SetEquipBonus(StatBonus value) {
    EquipBonus = value;
}

void Player::SetPotionEffectCount(int value) {
    PotionEffectCount = value;
}

void Player::SetStr(int value) {
    Str = value;
}

void Player::SetDex(int value) {
    Dex = value;
}

void Player::SetIntel(int value) {
    Intel = value;
}

void Player::SetLuk(int value) {
    Luk = value;
}

void Player::GainExp(int Exp)
{
    SetExp()

}

//경험치 획득 후, 현재 경험치가 최대 경험치 이상이고, 현재 레벨이 최대 레벨 캡인 10 미만일 때 레벨을 올리고 스텟을 조정하는 함수.
bool Player::IsLevelUpCheck(int newExp) {
    if (Player::GetExp() >= GetMaxExp() && GetLevel() < 10)
    {
        SetMaxHp(GetMaxHp() + 20);
        SetMaxMp(GetMaxMp() + 20);
        SetLevel(GetLevel() + 1);
        SetAttack(GetAttack() + 5);
        SetExp(0);
        SetMaxExp(GetMaxExp() + 50);
        SetHp(GetMaxHp());
        SetMp(GetMaxMp());
        SetDefense(GetDefense() + 5);
        return true;
    }
    else
    {
        return false;
    }
}

void Player::ApplyEquipBonus(bool EquipCheck, StatBonus Bonus) //장비 착용 확인(bool을 통해 체크 / 착용하지 않을 시 보너스를 0으로 초기화) 후, 장비 보너스를 세트하는 함수
{
    if (EquipCheck == true)
    {
        SetEquipBonus(Bonus);
    }
    else
    {
        SetEquipBonus({ 0 });
    }
}

void Player::ApplyPotionBonus(int Count, StatBonus Bonus) //포션 지속 확인(count > 0 일시 / 지속 시간이 0 이하일 시 보너스를 0으로 초기화) 후, 포션 보너스를 세트하는 함수
{
    if (Count > 0)
    {
        SetPotionBonus(Bonus);
    }
    else
    {
        SetPotionBonus({0});
    }

}


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

//경험치 입력 시 획득 및 누적하는 함수.
void Player::GainExp(int Exp)
{
    SetExp(GetExp() + Exp);
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


void Player::DrinkPotion(StatBonus AppliedBonus) //포션을 마셨을 때, 불러와 지속 시간과 보너스를 적용시키는 함수.
{
    // 포션의 스탯 보너스를 적용
    SetPotionBonus(AppliedBonus);

    // 지속될 턴 수를 세팅
    SetPotionEffectCount(5);

    PotionCheck = true;
}


void Player::UpdatePotionTurn() //포션 지속 시간 함수.
{
    // 현재 남은 턴 수
    int CurrentCount = GetPotionEffectCount();

    // 턴이 남아있다면 1을 감소
    if (CurrentCount > 0)
    {
        SetPotionEffectCount(CurrentCount - 1);

        // 깎은 직후 남은 턴이 0이 되었다면, 보너스를 초기화
        if (GetPotionEffectCount() == 0)
        {
            SetPotionBonus({ 0 });
            PotionCheck = false;
        }
    }
    if (CurrentCount > 0 && PotionCheck)
    {
        SetPotionEffectCount(5);
    }
}

void Player::ApplyEquipHpMpBonus(bool IsEquip, StatBonus Bonus)
{
    if (IsEquip == true)
    {
        // 최대치를 먼저 늘려준 뒤 현재치를 증가
        SetMaxHp(GetMaxHp() + Bonus.hp);
        SetHp(GetHp() + Bonus.hp);

        SetMaxMp(GetMaxMp() + Bonus.mp);
        SetMp(GetMp() + Bonus.mp);
    }
    else
    {
        // 현재치를 먼저 깎은 뒤 최대치를 감소
        SetHp(GetHp() - Bonus.hp);
        SetMaxHp(GetMaxHp() - Bonus.hp);

        SetMp(GetMp() - Bonus.mp);
        SetMaxMp(GetMaxMp() - Bonus.mp);

        // 체력 템을 벗었다고 해서 캐릭터가 즉사하는 것을 방지
        if (GetHp() <= 0)
        {
            SetHp(1); // 최소 체력 1 유지
        }

        // 마나도 음수가 되지 않도록 방지
        if (GetMp() < 0)
        {
            SetMp(0);
        }
    }
}

int Player::GetMeleeDamage(const StatBonus& equipBonus, const StatBonus& potionBonus)
{
    StatBonus totalBonus = equipBonus + potionBonus;

    int finalDamage = Attack
        + totalBonus.att
        + (Str + totalBonus.str) * 2
        + (Dex + totalBonus.dex);

    return finalDamage;
}

int Player::GetSkillDamage(const StatBonus& equipBonus, const StatBonus& potionBonus)
{
    StatBonus totalBonus = equipBonus + potionBonus;

    int finalDamage = Attack
        + totalBonus.att
        + (Intel + totalBonus.intel) * 2
        + (Luk + totalBonus.luk);

    return finalDamage;
}

int Player::GetTrueDefense(const StatBonus& equipBonus, const StatBonus& potionBonus)
{
    StatBonus totalBonus = equipBonus + potionBonus;

    int finalDefense = Defense
        + totalBonus.def;

    return finalDefense;
}

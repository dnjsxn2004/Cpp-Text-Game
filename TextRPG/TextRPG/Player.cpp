#include "Player.h"

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

int Player::GetLevel() const {
    return Level;
}

int Player::GetMaxLevel() const {
    return MaxLevel;
}

int Player::GetAtt() const {
    return Att;
}

int Player::GetExp() const {
    return Exp;
}

int Player::GetMaxExp() const {
    return MaxExp;
}

// Setter 구현
void Player::SetName(const std::string& newName) {
    name = newName;
}

void Player::SetHp(int newHp) {
    Hp = newHp;
}

void Player::SetMaxHp(int newMaxHp) {
    MaxHp = newMaxHp;
}

void Player::SetLevel(int newLevel) {
    Level = newLevel;
}

void Player::SetMaxLevel(int newMaxLevel) {
    MaxLevel = newMaxLevel;
}

void Player::SetAtt(int newAtt) {
    Att = newAtt;
}

void Player::SetExp(int newExp) {
    Exp = newExp;
}

void Player::SetMaxExp(int newMaxExp) {
    MaxExp = newMaxExp;
}

#pragma once
#pragma once
#include <string>

class Player
{
protected:
    std::string name;
    int Hp = 200;
    int MaxHp = 200;
    int Level = 1;
    int MaxLevel = 10;
    int Att = 30;
    int Exp = 0;
    int MaxExp = 100;


public:
    // Getter 선언 (멤버 변수를 변경하지 않으므로 const 키워드 사용)
    std::string GetName() const;
    int GetHp() const;
    int GetMaxHp() const;
    int GetLevel() const;
    int GetMaxLevel() const;
    int GetAtt() const;
    int GetExp() const;
    int GetMaxExp() const;

    // Setter 선언
    void SetName(const std::string& newName);
    void SetHp(int newHp);
    void SetMaxHp(int newMaxHp);
    void SetLevel(int newLevel);
    void SetMaxLevel(int newMaxLevel);
    void SetAtt(int newAtt);
    void SetExp(int newExp);
    void SetMaxExp(int newMaxExp);




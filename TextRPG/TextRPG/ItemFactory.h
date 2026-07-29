#pragma once
#include "Item.h"

//아이템 종류 클래스
class ItemFactory
{
public:
    //담배
    static Item CreateCigarette();
    //술
    static Item CreateAlcohol();
    //마약
    static Item CreateDrug();
    //위스키
    static Item CreateWhiskey();
    //주사기
    static Item CreateSyringe();
};

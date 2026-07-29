#pragma once
#include "Item.h"

//아이템 종류 클래스
class ItemFactory
{
public:

    //소비 아이템
    //담배
    static Item CreateCigarette(int quantity = 1);
    //술
    static Item CreateAlcohol(int quantity = 1);
    //마약
    static Item CreateDrug(int quantity = 1);
    //위스키
    static Item CreateWhiskey(int quantity = 1);
    //주사기
    static Item CreateSyringe(int quantity = 1);
    //대마초
    static Item CreateCannabis(int quantity = 1);

    //장비 아이템
    //무기쪽
    static Item CreateKnife();
    static Item CreateBat();
    static Item CreateKnuckle();
    static Item CreateKatana();
    //아머쪽
    static Item CreateThomBrowne();
    static Item CreateGucci();

    //퀘스트 아이템
    static Item CreateQuestkey();
};
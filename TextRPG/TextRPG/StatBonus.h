#pragma once

struct StatBonus
{
    int hp = 0;
    int mp = 0;
    int str = 0;
    int att = 0;
    int def = 0;
    int dex = 0;
    int intel = 0;
    int luk = 0;

    StatBonus operator+(const StatBonus& other) const
    {
        return StatBonus(
            hp + other.hp,
            mp + other.mp,
            str + other.str,
            att + other.att,
            def + other.def,
            dex + other.dex,
            intel + other.intel,
            luk + other.luk
        );
    }

    StatBonus(
        int _hp = 0,
        int _mp = 0,
        int _str = 0,
        int _att = 0,
        int _def = 0,
        int _dex = 0,
        int _intel = 0,
        int _luk = 0
    )
        : hp(_hp),
        mp(_mp),
        str(_str),
        att(_att),
        def(_def),
        dex(_dex),
        intel(_intel),
        luk(_luk)
    {
    }
};

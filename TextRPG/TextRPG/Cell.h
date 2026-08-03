#pragma once

#include <Windows.h>

struct Cell
{
    wchar_t ch = L' ';
    WORD color = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
};

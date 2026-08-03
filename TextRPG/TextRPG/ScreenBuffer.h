#pragma once

#include <vector>
#include <string>

#include "Cell.h"

class ScreenBuffer
{
public:

    ScreenBuffer(int width, int height);

    void Clear();

    void DrawText(
        int x,
        int y,
        const std::wstring& text,
        WORD color = 7);

    Cell& At(int x, int y);

    int GetWidth() const;
    int GetHeight() const;

    const std::vector<Cell>& GetBuffer() const;

private:

    int width;
    int height;

    std::vector<Cell> buffer;
};

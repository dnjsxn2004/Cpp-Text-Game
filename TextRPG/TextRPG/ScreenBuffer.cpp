#include "ScreenBuffer.h"

ScreenBuffer::ScreenBuffer(int width, int height)
    :
    width(width),
    height(height)
{
    buffer.resize(width * height);
}

void ScreenBuffer::Clear()
{
    for (auto& cell : buffer)
    {
        cell.ch = L' ';
        cell.color = 7;
    }
}

Cell& ScreenBuffer::At(int x, int y)
{
    return buffer[y * width + x];
}

void ScreenBuffer::DrawText(
    int x,
    int y,
    const std::wstring& text,
    WORD color)
{
    if (y < 0 || y >= height)
    {
        return;
    }

    for (int i = 0; i < text.size(); i++)
    {
        int drawX = x + i;

        if (drawX < 0 || drawX >= width)
        {
            continue;
        }

        Cell& cell = At(drawX, y);

        cell.ch = text[i];
        cell.color = color;
    }
}

int ScreenBuffer::GetWidth() const
{
    return width;
}

int ScreenBuffer::GetHeight() const
{
    return height;
}

const std::vector<Cell>& ScreenBuffer::GetBuffer() const
{
    return buffer;
}

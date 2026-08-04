#pragma once

#include <string>
#include <vector>

namespace AnsiPlayer
{
    void Init();
    void Clear();
    bool PrintFile(const std::string& path);
    std::vector<std::string> CollectFiles(const std::string& folderPath);
    void Play(const std::vector<std::string>& files, int delayMs, bool loop);
    void PlayFolder(const std::string& folderPath, int delayMs, bool loop);
    std::vector<std::string> LoadLines(
        const std::string& filePath,
        int offsetX = 0,
        int offsetY = 0,
        int maxWidth = 50,
        int maxHeight = 20
    );


    void DrawPanelAscii(
        const std::vector<std::string>& ascii,
        int panelWidth,
        int panelHeight);

    static std::string CutToWidth(const std::string& text, int width)
    {
        if (static_cast<int>(text.length()) <= width)
            return text;

        return text.substr(0, width);
    }
}

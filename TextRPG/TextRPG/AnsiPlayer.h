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
    std::vector<std::string> LoadLines(const std::string& filePath);
}

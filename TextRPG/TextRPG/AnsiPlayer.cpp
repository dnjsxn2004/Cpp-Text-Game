#include "AnsiPlayer.h"
#define NOMINMAX

#include <windows.h>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <algorithm>

namespace fs = std::filesystem;

namespace AnsiPlayer
{
    void Init()
    {
        HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
        DWORD dwMode = 0;
        GetConsoleMode(hOut, &dwMode);
        SetConsoleMode(hOut, dwMode
            | ENABLE_VIRTUAL_TERMINAL_PROCESSING
            | ENABLE_PROCESSED_OUTPUT);
        SetConsoleOutputCP(CP_UTF8);
    }

    void Clear()
    {
        HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
        COORD origin = { 0, 0 };
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        DWORD written = 0;
        GetConsoleScreenBufferInfo(hOut, &csbi);
        DWORD size = csbi.dwSize.X * csbi.dwSize.Y;
        FillConsoleOutputCharacterA(hOut, ' ', size, origin, &written);
        FillConsoleOutputAttribute(hOut, csbi.wAttributes, size, origin, &written);
        SetConsoleCursorPosition(hOut, origin);
    }

    bool PrintFile(const std::string& path)
    {
        std::ifstream file(path, std::ios::binary);
        if (!file) {
            std::cerr << "[AnsiPlayer] 파일 열기 실패: " << path << "\n";
            return false;
        }

        std::string content(
            (std::istreambuf_iterator<char>(file)),
            std::istreambuf_iterator<char>()
        );

        HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
        COORD origin = { 0, 0 };
        SetConsoleCursorPosition(hOut, origin);

        DWORD written = 0;
        WriteConsoleA(hOut, content.c_str(), (DWORD)content.size(), &written, NULL);
        return true;
    }

    std::vector<std::string> CollectFiles(const std::string& folderPath)
    {
        std::vector<std::string> files;

        if (!fs::exists(folderPath) || !fs::is_directory(folderPath)) {
            std::cerr << "[AnsiPlayer] 폴더 없음: " << folderPath << "\n";
            return files;
        }

        for (auto& entry : fs::directory_iterator(folderPath)) {
            if (entry.is_regular_file() && entry.path().extension() == ".txt")
                files.push_back(entry.path().string());
        }

        std::sort(files.begin(), files.end());
        return files;
    }

    void Play(
        const std::vector<std::string>& files,
        int  delayMs,
        bool loop)
    {
        if (files.empty()) {
            std::cerr << "[AnsiPlayer] 파일 목록이 비어있습니다.\n";
            return;
        }

        do {
            for (const auto& path : files)
            {
                Clear();
                PrintFile(path);
                Sleep(delayMs);

                if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) return;
            }
        } while (loop);
    }

    void PlayFolder(
        const std::string& folderPath,
        int  delayMs,
        bool loop)
    {
        auto files = CollectFiles(folderPath);
        std::cout << "[AnsiPlayer] " << files.size()
            << "개 파일 발견: " << folderPath << "\n";
        Sleep(600);
        Play(files, delayMs, loop);
    }
    std::vector<std::string> LoadLines(
        const std::string& filePath,
        int offsetX,
        int offsetY,
        int maxWidth,
        int maxHeight)
    {
        std::ifstream file(filePath);

        if (!file)
        {
            return { "[이미지 로드 실패] " + filePath };
        }

        std::vector<std::string> raw;
        std::string line;

        while (std::getline(file, line))
        {
            if (!line.empty() && line.back() == '\r')
            {
                line.pop_back();
            }

            raw.push_back(line);
        }

        std::vector<std::string> result;

        for (int y = 0; y < maxHeight; y++)
        {
            int srcY = y + offsetY;

            std::string output;

            if (srcY < static_cast<int>(raw.size()))
            {
                std::string srcLine = raw[srcY];

                if (offsetX < static_cast<int>(srcLine.size()))
                {
                    output = srcLine.substr(offsetX);
                }
            }

            result.push_back(output);
        }

        return result;
    }






    void DrawPanelAscii(
        const std::vector<std::string>& ascii,
        int panelWidth,
        int panelHeight)
    {
        for (int y = 0; y < panelHeight; y++)
        {
            if (y >= ascii.size())
            {
                std::cout << '\n';
                continue;
            }

            std::string line = ascii[y];

            if (line.length() > panelWidth)
            {
                line = line.substr(0, panelWidth);
            }

            std::cout << line << '\n';
        }
    }






} // namespace AnsiPlayer

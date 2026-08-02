#pragma once

#include "GameContext.h"
#include "Shop.h"


class GameManager
{
public:
    GameManager();
    ~GameManager();

    void Run();

private:
    GameContext context;
    Shop shop;

    bool loadSuccess;
    bool isWin;
    bool playerLevelUp;

private:
    // 전체 실행 단위
    void Initialize();
    void TitleFlow();

    // 시작 컷신 흐름
    void PlayOpeningCutscenes();

    // 캐릭터 선택
    void SelectCharacter();

    // 메인 메뉴 루프
    void MainLoop();
    void ProcessMainMenu(int choice);

    // 일반 컨텐츠
    void StartNormalBattle();
    void OpenShop();
    void OpenInventory();
    void ShowPlayerStatus();

    // 스토리 진행 선택 시 실행되는 고정 흐름
    void StartStoryBattleFlow();
    bool StartMiddleBossBattle();
    bool StartFinalBossBattle();

    // 종료 처리
    void Ending();
    void GameOver();
};

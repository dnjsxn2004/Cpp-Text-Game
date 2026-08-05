#include "GameManager.h"

#include <iostream>
#include <vector>

#include "ConsolUI.h"
#include "InputManager.h"
#include "Battle.h"
#include "Jin.h"
#include "Ryu.h"
#include "Gang.h"
#include "Monster.h"
#include "Player.h"
#include "GameState.h"
#include "AnsiPlayer.h"
#include "BattleResult.h"



GameManager::GameManager()
    : context(),
    shop(),
    loadSuccess(false),
    isWin(false),
    playerLevelUp(false),
    selectedCharacterIndex(0)
{
}

GameManager::~GameManager()
{
}


void GameManager::Run()
{
    Initialize();

    while (context.IsGameRunning())
    {
        switch (currentState)
        {
        case GameState::Title:
            ConsoleUI::PrintStartScreen();
            InputManager::Wait();
            currentState = GameState::CutScene;
            break;

        case GameState::CutScene:
            PlayOpeningCutscenes();
            currentState = GameState::CharacterSelect;
            break;

        case GameState::CharacterSelect:
            RenderCharacterSelect();
            HandleCharacterSelectInput();
            break;

        case GameState::MainMenu:
            RenderMainMenu();
            HandleMainMenuInput();
            break;

        case GameState::Battle:

            StartNormalBattle();

            if (context.IsGameRunning())
            {
                currentState = GameState::MainMenu;
            }

            break;

        case GameState::Shop:
            RenderShop();
            HandleShopInput();
            break;

        case GameState::Inventory:
            RenderInventory();
            HandleInventoryInput();
            break;

        case GameState::Status:
            RenderStatus();
            HandleStatusInput();
            break;

        case GameState::Story:
            RenderStory();
            HandleStoryInput();
            break;

        case GameState::Exit:
            context.SetGameRunning(false);
            break;
        }
    }
}



void GameManager::Initialize()
{
    logs.clear();
    AddLog("게임 시작");

    context.SetGameRunning(true);
    context.SetGameOver(false);

    currentState = GameState::Title;

    loadSuccess = false;
    isWin = false;
    playerLevelUp = false;
}


void GameManager::PlayOpeningCutscenes()
{
    // ─────────────────────────────────────────
    // 1막 ① : 야바위 전 — 세 사람의 아지트, 주사위 내기 직전
    // ─────────────────────────────────────────
    ConsoleUI::DrawCutSceneScreen(
        AnsiPlayer::LoadLines(R"(C:\ascii\RedNewCut1.txt)", 0, 0, 120, 28),
        {
            "낡은 창고 한켠, 희미한 전구 하나가 흔들린다.",
            "세 아이가 바닥에 둘러앉아 주사위를 손에 쥐고 있다.",
            "진태식 : 자, 이번엔 내가 이긴다. 무조건.",
            "류노스케 : 웃기고 있네. 오늘은 내 차례야.",
            "강사라 : 둘 다 조용히 해. 어차피 주사위가 결정하잖아."
        }
    );

    InputManager::Wait();

    // ─────────────────────────────────────────
    // 주사위 애니메이션
    // ─────────────────────────────────────────
    AnsiPlayer::PlayFolder(R"(C:\ascii\DiceAnime)", 120, false);

    InputManager::Wait();

    // ─────────────────────────────────────────
    // 1막 ② : 야바위 후 — 진태식 6, 류노스케 1
    // ─────────────────────────────────────────
    ConsoleUI::DrawCutSceneScreen(
        AnsiPlayer::LoadLines(R"(C:\ascii\RedNewCut1.txt)", 0, 0, 120, 28),
        {
            "진태식 : 6이다! 역시 주사위는 내 편이야.",
            "류노스케 : ...(주사위를 내려다본다) 1.",
            "류노스케 : 젠장.",
            "강사라 : 노스케, 괜찮아? 다음엔 이길 수 있어.",
            "류노스케 : (조용히) ...언젠간 내가 굴릴 주사위가 바뀔 거야.",
            "진태식 : (주사위를 손에 쥐며) 이거, 내가 갖는다.",
            "강사라 : 셋이 같이 있으면 됐지, 뭐."
        }
    );

    InputManager::Wait();

    // ─────────────────────────────────────────
    // 2막 ① : 각자의 성장 — 강사라 (불법 진료소)
    // ─────────────────────────────────────────
    ConsoleUI::DrawCutSceneScreen(
        AnsiPlayer::LoadLines(R"(C:\ascii\MainCut2.txt)", 0, 0, 120, 28),
        {
            "시간이 흘렀다.",
            "강사라는 의사가 되었다.",
            "하지만 그녀가 선택한 곳은 번듯한 병원이 아니었다.",
            "강사라 : (붕대를 감으며) 아파도 병원 못 가는 사람이 너무 많아.",
            "강사라 : 여기라도 있어야지."
        }
    );

    InputManager::Wait();

    // ─────────────────────────────────────────
    // 2막 ② : 각자의 성장 — 진태식 (언더커버)
    // ─────────────────────────────────────────
    ConsoleUI::DrawCutSceneScreen(
        AnsiPlayer::LoadLines(R"(C:\ascii\RedNewCut6.txt)", 0, 0, 120, 28),
        {
            "진태식은 경찰이 되었다.",
            "그리고 지금, 그는 두식이파 조직원으로 살고 있다.",
            "진태식 : (혼잣말) 조금만 더. 증거만 잡으면 끝난다.",
            "진태식 : ...노스케, 너는 어디쯤 있냐."
        }
    );

    InputManager::Wait();

    // ─────────────────────────────────────────
    // 2막 ③ : 각자의 성장 — 류노스케 (야쿠자 후계자)
    // ─────────────────────────────────────────
    ConsoleUI::DrawCutSceneScreen(
        AnsiPlayer::LoadLines(R"(C:\ascii\RedNewCut5.txt)", 0, 0, 120, 28),
        {
            "류노스케는 야쿠자 후계자가 되었다.",
            "아버지의 그늘 아래, 그는 조금씩 달라지고 있었다.",
            "류노스케 : (거울을 보며) 약한 놈은 살아남지 못해.",
            "류노스케 : ...그게 이 세계의 규칙이니까."
        }
    );

    InputManager::Wait();

    // ─────────────────────────────────────────
    // 2막 ④ : 진료소 조우 — 부상당한 진태식 방문
    // ─────────────────────────────────────────
    ConsoleUI::DrawCutSceneScreen(
        AnsiPlayer::LoadLines(R"(C:\ascii\MainCut3.txt)", 0, 0, 120, 28),
        {
            "허름한 진료소 문이 열렸다.",
            "어깨에 피를 흘린 채 진태식이 들어선다.",
            "강사라 : ...태식아?",
            "강사라 : (굳은 표정으로) 어디서 다친 거야. 일단 앉아.",
            "진태식 : (주위를 살피며, 낮게) 오랜만이다, 사라야.",
            "진태식 : 아무한테도 말하지 마."
        }
    );

    InputManager::Wait();

    // ─────────────────────────────────────────
    // 2막 ⑤ : 진료소 조우 — 진 · 류 대립
    // ─────────────────────────────────────────
    ConsoleUI::DrawCutSceneScreen(
        AnsiPlayer::LoadLines(R"(C:\ascii\RedNewCut9.txt)", 0, 0, 120, 28),
        {
            "그때, 문이 다시 열렸다.",
            "류노스케가 진태식을 보고 눈이 굳는다.",
            "류노스케 : ...진태식.",
            "류노스케 : (차갑게) 두식이파 조직원이 여기까지 기어왔어?",
            "진태식 : (침묵. 부정하지 않는다.)",
            "강사라 : (두 사람 사이에 서며) 그만해, 노스케. 여기선 안 돼.",
            "류노스케 : (진태식을 오래 바라보다, 돌아서며) ...다음엔 이런 자비 없다."
        }
    );

    InputManager::Wait();

    // ─────────────────────────────────────────
    // 막간 : 아버지의 압박
    // ─────────────────────────────────────────
    ConsoleUI::DrawCutSceneScreen(
        AnsiPlayer::LoadLines(R"(C:\ascii\RedNewCut10.txt)", 0, 0, 120, 28),
        {
            "야쿠자 본부. 어둠 속에 류노스케 혼자 서 있다.",
            "아버지 : 두식이파를 확실히 처리해라.",
            "아버지 : 후계자라면 그 정도는 해야지.",
            "류노스케 : (주먹을 쥐며, 침묵)",
            "아버지 : 못 하겠으면... 네 자리는 없다.",
            "류노스케 : (혼자, 낮게) ...반드시 해낸다.",
            "류노스케 : 이게 내가 굴려야 할 주사위라면."
        }
    );

    InputManager::Wait();

    // ─────────────────────────────────────────
    // 3막 ① : 카지노 밀담 — 마약 교섭장
    // ─────────────────────────────────────────
    ConsoleUI::DrawCutSceneScreen(
        AnsiPlayer::LoadLines(R"(C:\ascii\RedNewCut11.txt)", 0, 0, 120, 28),
        {
            "어두운 카지노 뒷방. 두식이파의 마약 교섭이 한창이다.",
            "진태식 : (속으로) 증거를 잡아야 해. 조금만 더.",
            "진태식 : (긴장하며 주위를 살핀다.)"
        }
    );

    InputManager::Wait();

    // ─────────────────────────────────────────
    // 3막 ② : 카지노 습격 — 류노스케 기습
    // ─────────────────────────────────────────
    ConsoleUI::DrawCutSceneScreen(
        AnsiPlayer::LoadLines(R"(C:\ascii\MainCut4.txt)", 0, 0, 120, 28),
        {
            "갑자기 불이 꺼진다.",
            "총성. 비명. 야쿠자 조직원들이 쏟아져 들어온다.",
            "류노스케 : (어둠 속에서 나타나며) 오늘 밤, 여기서 끝낸다.",
            "진태식 : (류노스케를 발견하고) ...노스케?!"
        }
    );

    InputManager::Wait();

    // ─────────────────────────────────────────
    // 3막 ③ : 류노스케, 진태식을 칼로 찌름
    // ─────────────────────────────────────────
    ConsoleUI::DrawCutSceneScreen(
        AnsiPlayer::LoadLines(R"(C:\ascii\RedNewCut12.txt)", 0, 0, 120, 28),
        {
            "류노스케 : (칼을 꺼내며, 떨리는 손으로) 넌 내 앞을 막는 패다.",
            "류노스케 : ...미안하다, 태식.",
            "진태식 : (칼에 찔리며) 노스케...! 너, 진심이야...?",
            "류노스케 : (등을 돌리며, 낮게) ...주사위는 이미 굴렸어."
        }
    );

    InputManager::Wait();

    AnsiPlayer::PlayFolder(R"(C:\ascii\MainCut6AniJinRyuKnife)", 240, false);

    InputManager::Wait();

    // ─────────────────────────────────────────
    // 3막 ④ : 진태식, 진료소로 이동
    // ─────────────────────────────────────────
    ConsoleUI::DrawCutSceneScreen(
        AnsiPlayer::LoadLines(R"(C:\ascii\RedNewCut13.txt)", 0, 0, 120, 28),
        {
            "진태식은 피를 흘리며 거리를 걷는다.",
            "진태식 : (이를 악물며) ...사라한테 가야 해.",
            "진태식 : 거기밖에 없어."
        }
    );

    InputManager::Wait();


    // ─────────────────────────────────────────
    // 3막 ⑤ : 류노스케, 진료소 습격
    // ─────────────────────────────────────────
    ConsoleUI::DrawCutSceneScreen(
        AnsiPlayer::LoadLines(R"(C:\ascii\RedNewCut15.txt)", 0, 0, 120, 28),
        {
            "진료소 문이 부서진다.",
            "류노스케가 부하들을 이끌고 들어선다.",
            "류노스케 : (차갑게) 두식이는 어디 있어.",
            "강사라 : (진태식 앞을 막아서며) 여기선 안 돼, 노스케!"
        }
    );

    InputManager::Wait();

    // ─────────────────────────────────────────
    // 3막 ⑥ : 진 · 류 맞짱
    // ─────────────────────────────────────────
    ConsoleUI::DrawCutSceneScreen(
        AnsiPlayer::LoadLines(R"(C:\ascii\MainCut5.txt)", 0, 0, 120, 28),
        {
            "진태식 : (몸을 일으키며) 노스케, 나한테 와.",
            "류노스케 : (조용히) ...그래. 너부터 끝내지.",
            "두 사람이 마주선다.",
            "한때 같은 주사위를 굴리던 친구들이."
        }
    );

    InputManager::Wait();


    AnsiPlayer::PlayFolder(R"(C:\ascii\MainCut5AniGamblingFight)", 240, false);

    InputManager::Wait();

    // ─────────────────────────────────────────
    // 3막 ⑦ : 진태식 패배
    // ─────────────────────────────────────────
    ConsoleUI::DrawCutSceneScreen(
        AnsiPlayer::LoadLines(R"(C:\ascii\RedNewCut15.txt)", 0, 0, 120, 28),
        {
            "진태식이 쓰러진다.",
            "류노스케 : (내려다보며, 낮게) ...일어나지 마.",
            "진태식 : (바닥에서, 숨을 고르며) 노스케... 아직 늦지 않았어.",
            "류노스케 : (침묵)"
        }
    );

    InputManager::Wait();

    // ─────────────────────────────────────────
    // 3막 ⑧ : 강사라 제지
    // ─────────────────────────────────────────
    ConsoleUI::DrawCutSceneScreen(
        AnsiPlayer::LoadLines(R"(C:\ascii\RedNewCut16.txt)", 0, 0, 120, 28),
        {
            "강사라 : (류노스케 앞에 서며) 제발, 노스케.",
            "강사라 : 여기서 멈춰. 아직 돌아올 수 있어.",
            "강사라 : 우리 셋이 같이 있던 거 기억하지?",
            "류노스케 : (흔들리는 눈으로) ...사라야, 비켜.",
            "강사라 : 싫어."
        }
    );
    InputManager::Wait();


    AnsiPlayer::PlayFolder(R"(C:\ascii\NewCut16AniKangDEAD)", 240, false);


    InputManager::Wait();

    // ─────────────────────────────────────────
    // 3막 ⑨ : 강사라 죽음
    // ─────────────────────────────────────────
    ConsoleUI::DrawCutSceneScreen(
        AnsiPlayer::LoadLines(R"(C:\ascii\RedNewCut18.txt)", 0, 0, 120, 28),
        {
            "류노스케 : (눈을 감으며) ...늦었어.",
            "칼날이 번뜩인다.",
            "강사라 : (쓰러지며, 희미하게) ...둘이서 싸우지 마.",
            "강사라 : 우리... 셋이었잖아.",
            "진태식 : 사라...!! 사라야!!",
            "류노스케 : (굳은 표정. 아무 말도 하지 않는다.)"
        }
    );

    InputManager::Wait();

    // ─────────────────────────────────────────
    // 강사라 시체 안고 좌절 — 게임 시작 직전
    // ─────────────────────────────────────────
    ConsoleUI::DrawCutSceneScreen(
        AnsiPlayer::LoadLines(R"(C:\ascii\RedNewCut22.txt)", 0, 0, 120, 28),
        {
            "진태식은 강사라를 안은 채 바닥에 주저앉는다.",
            "진태식 : (떨리는 목소리로) ...왜.",
            "진태식 : 내가 막았어야 했는데.",
            "진태식 : (손에 쥔 주사위를 바라보며) 노스케...",
            "진태식 : 이걸로 끝낸다.",
            "— 게임이 시작된다 —"
        }
    );

    InputManager::Wait();
}


void GameManager::RenderMainMenu()
{
    UIScreen screen;

    std::vector<std::string> playerStatus;

    if (context.HasPlayer())
    {
        Player& player = context.GetPlayer();

        playerStatus.push_back(
            "이름 : " + player.GetName()
        );

        playerStatus.push_back(
            "HP : " +
            std::to_string(player.GetHp())
        );

        playerStatus.push_back(
            "MP : " +
            std::to_string(player.GetMp())
        );
    }

    screen.a = AnsiPlayer::LoadLines(
        R"(C:\ascii\RedNewCut1.txt)",
        0,
        0,
        50,
        22
    );

    screen.b = logs;

    screen.c =
    {
        "1. 전투",
        "2. 상점",
        "3. 인벤토리",
        "4. 상태 보기",
        "5. 스토리 진행",
        "0. 게임 종료"
    };

    screen.d = playerStatus;

    ConsoleUI::DrawFullLayout(screen);
}


void GameManager::HandleMainMenuInput()
{

    int choice = InputManager::InputInMassegeToRange("선택: ", 0, 5);

    switch (choice)
    {
    case 1:
        currentState = GameState::Battle;
        break;

    case 2:
        currentState = GameState::Shop;
        break;

    case 3:
        currentState = GameState::Inventory;
        break;

    case 4:
        currentState = GameState::Status;
        break;

    case 5:
        currentState = GameState::Story;
        break;

    case 0:
        currentState = GameState::Exit;
        break;
    }
}


void GameManager::StartNormalBattle()
{
    ConsoleUI::ClearScreen();

    if (!context.HasPlayer())
    {
        AddLog("플레이어가 없습니다.");
        context.SetGameOver(true);
        return;
    }

    Monster monster = SpawnRandomMonster(context);

    context.SetMonster(monster);

    logs.clear();

    AddLog("전투 시작!");
    AddLog(monster.GetName() + " 등장!");

    Battle battle(context);

    battle.RunBattle(context);

    if (context.GetPlayer().GetHp() > 0)
    {
        AddLog("전투 종료");
    }
    else
    {
        AddLog("전투 패배...");
        context.SetGameOver(true);
        context.SetGameRunning(false);
    }

    InputManager::Wait();
    ConsoleUI::ClearScreen();
}

void GameManager::StartStoryBattleFlow()
{
    ConsoleUI::ClearScreen();

    ConsoleUI::DrawCutSceneScreen(
        AnsiPlayer::LoadLines(R"(C:\ascii\MainCut5.txt)", 0, 0, 120, 28),
        {
            "중간 보스 왈"
        }
        );

    InputManager::Wait();

    BattleResult middleResult = StartMiddleBossBattle();

    // 패배
    if (middleResult == BattleResult::Lose)
    {
        GameOver();

        context.SetGameRunning(false);

        return;
    }

    // 도망 성공
    if (middleResult == BattleResult::Escape)
    {
        Ending();

        currentState = GameState::MainMenu;

        return;
    }


    ConsoleUI::DrawCutSceneScreen(
        AnsiPlayer::LoadLines(R"(C:\ascii\RedNewCut5.txt)", 0, 0, 120, 28),
        {
            "보스 왈"
        }
        );

    InputManager::Wait();


    BattleResult finalResult =  StartFinalBossBattle();

    if (finalResult == BattleResult::Lose)
    {
        GameOver();

        context.SetGameRunning(false);

        return;
    }

    if (finalResult == BattleResult::Escape)
    {
        Ending();

        currentState = GameState::MainMenu;

        return;
    }

    Ending();

    currentState = GameState::MainMenu;
}


void GameManager::HandleStoryInput()
{
    InputManager::Wait();

    StartStoryBattleFlow();

    if (context.IsGameRunning())
    {
        currentState = GameState::MainMenu;
    }
}



BattleResult GameManager::StartMiddleBossBattle()
{
    InputManager::Wait();

    Monster middleBoss = SpawnMiddleBoss(context);
    context.SetMonster(middleBoss);

    Battle battle(context);

    BattleResult result = battle.RunBattle(context);

    InputManager::Wait();

    return result;
}


BattleResult GameManager::StartFinalBossBattle()
{
    InputManager::Wait();

    Monster finalBoss = SpawnFinalBoss(context);
    context.SetMonster(finalBoss);

    Battle battle(context);

    BattleResult result = battle.RunBattle(context);

    InputManager::Wait();

    return result;
}


void GameManager::Ending()
{
    // 장면 ④ — 마지막 독백 (RedNewCut21 : 류노스케 난간 앞)
    ConsoleUI::DrawCutSceneScreen(
        AnsiPlayer::LoadLines(R"(C:\ascii\RedNewCut21.txt)", 0, 0, 120, 28),
        {
            "류노스케 : 나는 처음부터 1이었어, 태식아.",
            "류노스케 : 아무리 발버둥쳐도...",
            "류노스케 : 내 주사위는 항상 1이 나왔어.",
            "류노스케 : 아버지한테도, 조직한테도, 너한테도.",
            "류노스케 : 이긴 적이 한 번도 없었어."
        }
    );
    InputManager::Wait();

    // 장면 ⑤ — 마지막 인사 (RedNewCut22 : 뒤돌아보지 않고)
    ConsoleUI::DrawCutSceneScreen(
        AnsiPlayer::LoadLines(R"(C:\ascii\RedNewCut22.txt)", 0, 0, 120, 28),
        {
            "류노스케 : 태식아.",
            "류노스케 : ...",
            "류노스케 : 잘 살아.",
        }
    );
    InputManager::Wait();

    // 자살 애니메이션
    AnsiPlayer::PlayFolder(R"(C:\ascii\NewCut23AniRyuFall)", 240, false);

    InputManager::Wait();

    // 장면 ⑥ — 엔딩 나레이션 (RedNewCut20 : 화면 암전)
    ConsoleUI::DrawCutSceneScreen(
        AnsiPlayer::LoadLines(R"(C:\ascii\RedNewCut20.txt)", 0, 0, 120, 28),
        {
            "주사위는 굴러갔다.",
            "진태식의 주사위는 6이었다.",
            "하지만 그는 아무것도 느끼지 못했다.",
            "이긴다는 것이 이런 의미였다면—",
            "처음부터, 지는 편이 나았을지도 모른다."
        }
    );

    InputManager::Wait();
}

void GameManager::GameOver()
{
    ConsoleUI::PrintGameOver();
    InputManager::Wait();
}

void GameManager::AddLog(const std::string& text)
{
    logs.push_back(text);

    if (logs.size() > 8)
    {
        logs.erase(logs.begin());
    }
}

void GameManager::HandleCharacterSelectInput()
{
    int choice = InputManager::InputInMassegeToRange("선택: ", 0, 2);

    if (choice == 0)
    {
        currentState = GameState::Exit;
        return;
    }

    bool confirm = ShowCharacterPreview(choice);

    if (!confirm)
    {
        return; // 다시 선택 화면으로
    }

    if (choice == 1)
    {
        context.SetPlayer(new Jin());
        AddLog("진태식을 선택했습니다.");
    }
    else
    {
        context.SetPlayer(new Ryu());
        AddLog("류노스케를 선택했습니다.");
    }

    currentState = GameState::MainMenu;
}

bool GameManager::ShowCharacterPreview(int choice)
{
    UIScreen screen;

    if (choice == 1)
    {
        screen.a = ConsoleUI::PrintJinWhiteImage();

        screen.b =
        {
            "[ 진태식 ]",
            "",
            "무술: 유도",
            "",
            "마약유통을 잡기위해 두식이파에 잠입한 비밀경찰",
            "의리와 책임을 중시한다.",
            "",
 
        };
    }
    else
    {
        screen.a = ConsoleUI::PrintRyuWhiteImage();

        screen.b =
        {
            "[ 류노스케 ]",
            "",
            "무술: 가라데",
            "",
            "냉철한 야쿠자 후계자.",
            "",
   
        };
    }

    screen.c =
    {
        "",
        "이 캐릭터를 선택하시겠습니까?",
        "",
        "1. 예",
        "2. 아니오"
    };

    screen.d =
    {
        "선택: "
    };

    ConsoleUI::DrawFullLayout(screen);

    int confirm = InputManager::InputInMassegeToRange("", 1, 2);

    return confirm == 1;
}




void GameManager::RenderCharacterSelect()
{
    UIScreen screen;

    Jin jin;
    Ryu ryu;

    if (selectedCharacterIndex == 0)
    {
        screen.a = ConsoleUI::PrintJinBlackImage();
    }
    else
    {
        screen.a = ConsoleUI::PrintRyuBlackImage();
    }

    Player* preview =
        (selectedCharacterIndex == 0)
        ? static_cast<Player*>(&jin)
        : static_cast<Player*>(&ryu);

    
    screen.b =
    {
        "[ 캐릭터 선택 ]",
        "",
        (selectedCharacterIndex == 0)
        ? jin.GetDescription()
        : ryu.GetDescription()
    };

    
    screen.c =
    {
        (selectedCharacterIndex == 0 ? "> 진태식" : "  진태식"),
        (selectedCharacterIndex == 1 ? "> 류노스케" : "  류노스케"),
        
    };

    screen.d =
    {
        "HP  : " + std::to_string(preview->GetHp()),
        "MP  : " + std::to_string(preview->GetMp()),
        "ATK : " + std::to_string(preview->GetAttack())
    };

    ConsoleUI::DrawFullLayout(screen);
}

void GameManager::RenderShop()
{
    UIScreen screen;

    Player& player = context.GetPlayer();

    std::vector<std::string> productLines;
    std::vector<int> displayToRealIndex;

    int displayIndex = 1;

    const auto& all = shop.GetProducts();

    // ===== 무기 =====
    productLines.push_back("[ 무기 ]");

    auto weapons = shop.GetProductsByCategory(ShopCategory::Weapon);

    for (const Item& item : weapons)
    {
        const StatBonus& b = item.GetStatBonus();

        std::string line =
            std::to_string(displayIndex) + ". " +
            item.GetName() + " | " +
            std::to_string(item.GetPrice()) + "G | " +
            "ATK+" + std::to_string(b.att);

        productLines.push_back(line);

        for (int i = 0; i < all.size(); i++)
        {
            if (all[i].GetName() == item.GetName())
            {
                displayToRealIndex.push_back(i);
                break;
            }
        }

        displayIndex++;
    }

    productLines.push_back("");

    // ===== 방어구 =====
    productLines.push_back("[ 방어구 ]");

    auto armors = shop.GetProductsByCategory(ShopCategory::Armor);

    for (const Item& item : armors)
    {
        const StatBonus& b = item.GetStatBonus();

        std::string line =
            std::to_string(displayIndex) + ". " +
            item.GetName() + " | " +
            std::to_string(item.GetPrice()) + "G | " +
            "DEF+" + std::to_string(b.def);

        productLines.push_back(line);

        for (int i = 0; i < all.size(); i++)
        {
            if (all[i].GetName() == item.GetName())
            {
                displayToRealIndex.push_back(i);
                break;
            }
        }

        displayIndex++;
    }

    productLines.push_back("");

    // ===== 소비 아이템 =====
    productLines.push_back("[ 소비아이템 ]");

    auto consumables = shop.GetProductsByCategory(ShopCategory::Consumable);

    for (const Item& item : consumables)
    {
        const StatBonus& b = item.GetStatBonus();

        std::string line =
            std::to_string(displayIndex) + ". " +
            item.GetName() + " | " +
            std::to_string(item.GetPrice()) + "G | " +
            "HP+" + std::to_string(b.hp) +
            " MP+" + std::to_string(b.mp);

        productLines.push_back(line);

        for (int i = 0; i < all.size(); i++)
        {
            if (all[i].GetName() == item.GetName())
            {
                displayToRealIndex.push_back(i);
                break;
            }
        }

        displayIndex++;
    }

    screen.a = AnsiPlayer::LoadLines(
        R"(C:\ascii\RedNewCut4.txt)",
        0,
        0,
        50,
        22
    );


    screen.b = productLines;

    screen.c =
    {
        "1. 아이템 구매",
        "2. 아이템 판매",
        "0. 뒤로가기"
    };

    screen.d =
    {
        "이름 : " + player.GetName(),
        "Gold : " + std::to_string(player.GetGold()),
        "",
        "소지품 수 : " +
        std::to_string(
            context.GetInventory().GetItems().size()
        )
    };

    ConsoleUI::DrawFullLayout(screen);

    shopIndexMap = displayToRealIndex; 
}

void GameManager::RenderSellItemList()
{
    UIScreen screen;

    Player& player = context.GetPlayer();
    Inventory& inventory = context.GetInventory();

    const std::vector<Item>& items = inventory.GetItems();
    std::vector<int> sellable = inventory.GetSellableItemIndices();

    std::vector<std::string> itemLines;

    itemLines.push_back("[ 판매 가능 아이템 ]");
    itemLines.push_back("");

    if (sellable.empty())
    {
        itemLines.push_back("판매 가능한 아이템이 없습니다.");
    }
    else
    {
        for (int i = 0; i < static_cast<int>(sellable.size()); i++)
        {
            int realIndex = sellable[i];

            const Item& item = items[realIndex];
            const StatBonus& b = item.GetStatBonus();

            int sellPrice = shop.GetSellPrice(item);

            std::string line =
                std::to_string(i + 1) + ". " +
                item.GetName() +
                " | 판매가 " + std::to_string(sellPrice) + "G" +
                " | 수량 " + std::to_string(item.GetQuantity()) +
                " | ";

            if (item.GetType() == ItemType::Equipment)
            {
                if (item.GetEquipmentType() == EquipmentType::Weapon)
                {
                    line += "ATK+" + std::to_string(b.att);
                }
                else if (item.GetEquipmentType() == EquipmentType::Armor)
                {
                    line += "DEF+" + std::to_string(b.def);
                }
                else
                {
                    line += "장비";
                }
            }
            else if (item.GetType() == ItemType::Consumable)
            {
                line +=
                    "HP+" + std::to_string(b.hp) +
                    " MP+" + std::to_string(b.mp);
            }
            else
            {
                line += "기타";
            }

            itemLines.push_back(line);
        }
    }

    screen.a = AnsiPlayer::LoadLines(
        R"(C:\ascii\RedNewCut4.txt)",
        0,
        0,
        50,
        22
    );

    screen.b = itemLines;

    screen.c =
    {
        "판매할 아이템 번호 입력",
        "0. 취소"
    };

    screen.d =
    {
        "이름 : " + player.GetName(),
        "Gold : " + std::to_string(player.GetGold()),
        "",
        "판매 가능 수 : " + std::to_string(sellable.size())
    };

    ConsoleUI::DrawFullLayout(screen);
}




void GameManager::HandleShopInput()
{
    int choice =
        InputManager::InputInMassegeToRange(
            "선택: ",
            0,
            2
        );

    switch (choice)
    {
    case 1:
    {
        if (shopIndexMap.empty())
        {
            AddLog("상품이 없습니다.");
            break;
        }

        int index = InputManager::InputInMassegeToRange(
            "구매할 상품 번호: ",
            1,
            static_cast<int>(shopIndexMap.size())
        ) - 1;

        int realIndex = shopIndexMap[index];

        const std::vector<Item>& products = shop.GetProducts();

        if (realIndex < 0 || realIndex >= static_cast<int>(products.size()))
        {
            AddLog("잘못된 상품입니다.");
            break;
        }

        const Item& product = products[realIndex];

        int quantity = 1;

        if (product.GetType() == ItemType::Equipment)
        {
            quantity = 1;
        }
        else
        {
            quantity =
                InputManager::InputInMassegeToRange(
                    "수량: ",
                    1,
                    99
                );
        }

        if (shop.BuyItem(realIndex, quantity, context))
        {
            AddLog("구매 완료");
        }
        else
        {
            AddLog("구매 실패");
        }

        break;
    }

    case 2:
    {
        Inventory& inventory = context.GetInventory();

        std::vector<int> sellable =
            inventory.GetSellableItemIndices();

        if (sellable.empty())
        {
            AddLog("판매 가능한 아이템이 없습니다.");
            break;
        }

        RenderSellItemList();

        int sellChoice =
            InputManager::InputInMassegeToRange(
                "판매할 아이템 번호, 취소는 0: ",
                0,
                static_cast<int>(sellable.size())
            );

        if (sellChoice == 0)
        {
            break;
        }

        int sellIndex = sellChoice - 1;

        int realIndex = sellable[sellIndex];

        const std::vector<Item>& items = inventory.GetItems();

        if (realIndex < 0 || realIndex >= static_cast<int>(items.size()))
        {
            AddLog("잘못된 아이템입니다.");
            break;
        }

        const Item& item = items[realIndex];

        int maxQuantity = item.GetQuantity();

        int quantity = 1;

        if (item.GetType() == ItemType::Equipment)
        {
            quantity = 1;
        }
        else
        {
            quantity =
                InputManager::InputInMassegeToRange(
                    "판매 수량: ",
                    1,
                    maxQuantity
                );
        }

        if (shop.SellItem(realIndex, quantity, context))
        {
            AddLog("판매 완료");
        }
        else
        {
            AddLog("판매 실패");
        }

        break;
    }

    case 0:
        currentState = GameState::MainMenu;
        break;
    }
}




void GameManager::RenderStatus()
{
    UIScreen screen;

    Player& player = context.GetPlayer();
    Inventory& inventory = context.GetInventory();


    screen.a = AnsiPlayer::LoadLines(
        R"(C:\ascii\RedNewCut6.txt)",
        0,
        0,
        50,
        22
    );

    screen.b =
    {
        "이름 : " + player.GetName(),
        "레벨 : " + std::to_string(player.GetLevel()),
        "",

        "HP   : " +
            std::to_string(player.GetHp()) + " / " +
            std::to_string(player.GetMaxHp()),

        "MP   : " +
            std::to_string(player.GetMp()) + " / " +
            std::to_string(player.GetMaxMp()),

        "EXP  : " +
            std::to_string(player.GetExp()) + " / " +
            std::to_string(player.GetMaxExp()),

        "",
        "ATK  : " + std::to_string(player.GetAttack()),
        "DEF  : " + std::to_string(player.GetDefense()),
        "",
        "Gold : " + std::to_string(player.GetGold())
    };



    screen.c =
    {
        "0. 뒤로가기"
    };

    screen.d =
    {
        "무기 : " + inventory.GetEquippedWeaponName(),
        "방어구 : " + inventory.GetEquippedArmorName()
    };

    ConsoleUI::DrawFullLayout(screen);
}


void GameManager::HandleStatusInput()
{
    InputManager::InputInMassegeToRange(
        "0. 뒤로가기: ",
        0,
        0
    );

    currentState = GameState::MainMenu;
}



void GameManager::RenderStory()
{
    UIScreen screen;

    Player& player = context.GetPlayer();

    screen.a = AnsiPlayer::LoadLines(
        R"(C:\ascii\RedNewCut13.txt)",
        0,
        0,
        50,
        22
    );

    screen.b =
    {
        "강사라가 죽은 뒤,",
        "진료소엔 무거운 침묵만 남아있다.",
        "",
        "희미한 담배 냄새가 공기 속에 남아 있다.",
        "",
        "아직 끝난 건 아니다."
    };

    screen.c =
    {
        "ENTER : 메인 메뉴로"
    };

    screen.d =
    {
        player.GetName(),
        "HP : " + std::to_string(player.GetHp()),
        "MP : " + std::to_string(player.GetMp())
    };

    ConsoleUI::DrawFullLayout(screen);
}





void GameManager::RenderInventory()
{
    UIScreen screen;

    Player& player = context.GetPlayer();
    Inventory& inventory = context.GetInventory();

    const auto& items = inventory.GetItems();

    std::vector<std::string> itemLines;

    for (int i = 0; i < items.size(); i++)
    {
        const Item& item = items[i];
        const StatBonus& b = item.GetStatBonus();

        int sellPrice = shop.GetSellPrice(item);

        std::string line =

            std::to_string(i + 1) + ". " +
            item.GetName() + " | " +
            std::to_string(sellPrice) + "G | ";

        if (item.GetType() == ItemType::Equipment)
        {
            if (item.GetEquipmentType() == EquipmentType::Weapon)
            {
                line += "ATK+" + std::to_string(b.att);
            }
            else
            {
                line += "DEF+" + std::to_string(b.def);
            }
        }
        else
        {
            line +=
                "HP+" + std::to_string(b.hp) +
                " MP+" + std::to_string(b.mp);
        }

        if (item.IsEquipped())
        {
            line += " [장착중]";
        }

        itemLines.push_back(line);
    }

    screen.a = AnsiPlayer::LoadLines(
        R"(C:\ascii\RedNewCut6.txt)",
        10,
        5,
        50,
        22
    );

    screen.b = itemLines;

    screen.c =
    {
        "1 ~ N : 사용 / 장착",
        "0 : 뒤로가기"
    };

    screen.d =
    {
        "이름 : " + player.GetName(),
        "Gold : " + std::to_string(player.GetGold()),
        "",
        "아이템 수 : " +
        std::to_string(items.size())
    };

    ConsoleUI::DrawFullLayout(screen);
}



void GameManager::HandleInventoryInput()
{
    Inventory& inventory = context.GetInventory();

    const auto& items = inventory.GetItems();

    if (items.empty())
    {
        AddLog("인벤토리가 비어 있습니다.");

        InputManager::Wait();

        currentState = GameState::MainMenu;

        return;
    }

    int choice =
        InputManager::InputInMassegeToRange(
            "선택: ",
            0,
            static_cast<int>(items.size())
        );

    if (choice == 0)
    {
        currentState = GameState::MainMenu;
        return;
    }

    int index = choice - 1;

    std::string itemName = items[index].GetName();
    ItemType type = items[index].GetType();

    bool result = false;

    if (type == ItemType::Equipment)
    {
        result = inventory.EquipItem(index, context);

        if (result)
        {
            AddLog(itemName + " 장착 완료");
        }
        else
        {
            AddLog(itemName + " 장착 실패");
        }
    }
    else
    {
        result = inventory.UseItem(index, context);

        if (result)
        {
            AddLog(itemName + " 사용 완료");
        }
        else
        {
            AddLog(itemName + " 사용 실패");
        }
    }
}








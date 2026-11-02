#include "TitleScene.h"
#include "../File/AssetContainer.h"
#include "../File/Sprite.h"
#include "../Input/InputManager.h"
#include <DxLib.h>
#include <cstring>

TitleScene::TitleScene()
    : SceneBase()
    , bgSprite(nullptr)
    , marioSprite(nullptr)
    , mushroomSprite(nullptr)
    , nameMarioSprite(nullptr)
    , worldSprite(nullptr)
    , timeSprite(nullptr)
    , topSprite(nullptr)
    , coinSprite(nullptr)
    , fontAlphaSprite(nullptr)
    , fontNumSprite(nullptr)
    , disp_timer(0.0f)
    , is_disp(true)
    , coinAnimFrame(0)
    , coinCurrentFrame(0)
    , selectMenu(0)
{

}

TitleScene::~TitleScene()
{

}

void TitleScene::Initialize()
{
    // 背景・マリオ・キノコ
    bgSprite = new Sprite("title.png");
    marioSprite = new DivSprite("Mario/mario.png", 9, 1);
    mushroomSprite = new Sprite("Item/Mushroom.png");

    // UIアセット（AssetContainer経由で "assets/Images/" + "UI/..."）
    nameMarioSprite = new Sprite("UI/name_mario.png");
    worldSprite = new Sprite("UI/world.png");
    timeSprite = new Sprite("UI/time.png");
    topSprite = new Sprite("UI/top.png");
    coinSprite = new DivSprite("UI/uicoin.png", 4, 1);

    // フォント
    fontAlphaSprite = new DivSprite("UI/string.png", 26, 1);
    fontNumSprite = new DivSprite("UI/num.png", 15, 1);
}

eSceneType TitleScene::Update(float delta_second)
{
    // コインのパラパラアニメーション更新
    coinAnimFrame++;
    if (coinAnimFrame >= 12) // 回転スピード調整
    {
        coinAnimFrame = 0;
        coinCurrentFrame = (coinCurrentFrame + 1) % 4;
    }

    // 上下キー / DPAD でメニュー移動
    if (InputManager::GetKeyState(KEY_INPUT_UP) == eInputState::ePressed ||
        InputManager::GetKeyState(KEY_INPUT_DOWN) == eInputState::ePressed ||
        InputManager::GetButtonState(XINPUT_BUTTON_DPAD_UP) == eInputState::ePressed ||
        InputManager::GetButtonState(XINPUT_BUTTON_DPAD_DOWN) == eInputState::ePressed)
    {
        selectMenu = (selectMenu == 0) ? 1 : 0;
    }

    // 決定キーでインゲーム遷移
    if (InputManager::GetKeyState(KEY_INPUT_SPACE) == eInputState::ePressed ||
        InputManager::GetKeyState(KEY_INPUT_RETURN) == eInputState::ePressed ||
        InputManager::GetButtonState(XINPUT_BUTTON_A) == eInputState::ePressed ||
        InputManager::GetButtonState(XINPUT_BUTTON_START) == eInputState::ePressed)
    {
        return eSceneType::eInGame;
    }

    return GetNowSceneType();
}

void TitleScene::DrawStringCustom(int x, int y, const char* str) const
{
    if (!fontAlphaSprite || !fontNumSprite) return;

    int len = (int)strlen(str);
    int charWidth = 32;

    for (int i = 0; i < len; i++)
    {
        char c = str[i];
        int drawX = x + (i * charWidth);

        if (c >= 'A' && c <= 'Z')
        {
            DrawRotaGraph(drawX, y, 2.0, 0.0, (*fontAlphaSprite)[c - 'A'], TRUE);
        }
        else if (c >= 'a' && c <= 'z')
        {
            DrawRotaGraph(drawX, y, 2.0, 0.0, (*fontAlphaSprite)[c - 'a'], TRUE);
        }
        else if (c >= '0' && c <= '9')
        {
            DrawRotaGraph(drawX, y, 2.0, 0.0, (*fontNumSprite)[c - '0'], TRUE);
        }
        else if (c == '-') DrawRotaGraph(drawX, y, 2.0, 0.0, (*fontNumSprite)[10], TRUE);
        else if (c == 'x') DrawRotaGraph(drawX, y, 2.0, 0.0, (*fontNumSprite)[11], TRUE);
        else if (c == '!') DrawRotaGraph(drawX, y, 2.0, 0.0, (*fontNumSprite)[12], TRUE);
        else if (c == '.') DrawRotaGraph(drawX, y, 2.0, 0.0, (*fontNumSprite)[14], TRUE);
    }
}

void TitleScene::Draw() const
{
    // 1. タイトル背景描画
    if (bgSprite && bgSprite->GetHandle() != -1)
    {
        DrawRotaGraph(512, 384, 1.6, 0.0, bgSprite->GetHandle(), TRUE);
    }

    // ==========================================
    // 2. 最上部ヘッダーUI（座標一括調整版）
    // ==========================================

    // MARIO & スコア (X: 200 -> 250, Y: 60/95 -> 30/60)
    if (nameMarioSprite && nameMarioSprite->GetHandle() != -1)
    {
        DrawRotaGraph(150, 30, 1.8, 0.0, nameMarioSprite->GetHandle(), TRUE);
    }
    DrawStringCustom(93, 60, "000000");

    // アニメーションコイン & コイン枚数 (X: 420/450 -> 420/450, Y: 95 -> 60)
    if (coinSprite && coinSprite->GetSize() > 0)
    {
        DrawRotaGraph(380, 60, 1.8, 0.0, (*coinSprite)[coinCurrentFrame], TRUE);
    }
    DrawStringCustom(410, 65, "x00");

    // WORLD & ステージ (X: 650 -> 610, Y: 60/95 -> 30/60)
    if (worldSprite && worldSprite->GetHandle() != -1)
    {
        DrawRotaGraph(650, 30, 1.8, 0.0, worldSprite->GetHandle(), TRUE);
    }
    DrawStringCustom(615, 60, "1-1");

    // TIME (X: 850 -> 760, Y: 60 -> 30)
    if (timeSprite && timeSprite->GetHandle() != -1)
    {
        DrawRotaGraph(850, 30, 1.8, 0.0, timeSprite->GetHandle(), TRUE);
    }

    // ==========================================
    // 3. メニューテキスト & ハイスコア
    // ==========================================
    DrawStringCustom(320, 480, "1 PLAYER GAME");
    DrawStringCustom(320, 520, "2 PLAYER GAME");
    DrawStringCustom(340, 565, "TOP- 000000");

    // 4. キノコカーソル描画
    if (mushroomSprite && mushroomSprite->GetHandle() != -1)
    {
        int cursorY = (selectMenu == 0) ? 482 : 522;
        DrawRotaGraph(275, cursorY, 0.8, 0.0, mushroomSprite->GetHandle(), TRUE);
    }

    // 5. マリオ描画
    if (marioSprite && marioSprite->GetSize() > 0)
    {
        DrawRotaGraph(155, 634, 2.0, 0.0, (*marioSprite)[0], TRUE);
    }
}


void TitleScene::Finalize()
{
    delete bgSprite;        bgSprite = nullptr;
    delete marioSprite;     marioSprite = nullptr;
    delete mushroomSprite;  mushroomSprite = nullptr;

    delete nameMarioSprite; nameMarioSprite = nullptr;
    delete worldSprite;     worldSprite = nullptr;
    delete timeSprite;      timeSprite = nullptr;
    delete topSprite;       topSprite = nullptr;
    delete coinSprite;      coinSprite = nullptr;

    delete fontAlphaSprite; fontAlphaSprite = nullptr;
    delete fontNumSprite;   fontNumSprite = nullptr;
}

eSceneType TitleScene::GetNowSceneType() const
{
    return eSceneType::eTitle;
}
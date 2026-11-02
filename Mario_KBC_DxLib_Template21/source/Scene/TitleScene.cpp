#pragma once
#include "TitleScene.h"
#include "../File/AssetContainer.h"
#include "../File/Sprite.h"
#include "../Input/InputManager.h"
#include <DxLib.h>

TitleScene::TitleScene()
    : SceneBase()
    , bgSprite(nullptr)
    , marioSprite(nullptr)
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
    // AssetContainer 側で "assets/Images/" が付与されるため
    // assets/Images/ 直下に title_bg.png がある場合は "title_bg.png" と記述します
    // (もし UI フォルダ内にある場合は "UI/title_bg.png" に変更してください)
    bgSprite = new Sprite("title.png");
    marioSprite = new DivSprite("Mario/mario.png", 9, 1);
}

eSceneType TitleScene::Update(float delta_second)
{
    // SPACEキーまたはコントローラーのSTART/Aボタンでインゲームへ遷移
    if (InputManager::GetKeyState(KEY_INPUT_SPACE) == eInputState::ePressed ||
        InputManager::GetKeyState(KEY_INPUT_RETURN) == eInputState::ePressed ||
        InputManager::GetButtonState(XINPUT_BUTTON_A) == eInputState::ePressed ||
        InputManager::GetButtonState(XINPUT_BUTTON_START) == eInputState::ePressed)
    {
        return eSceneType::eInGame;
    }

    return GetNowSceneType();
}

void TitleScene::Draw() const
{
    // 1. タイトル背景の描画テスト
    if (bgSprite && bgSprite->GetHandle() != -1)
    {
        DrawRotaGraph(512, 384, 1.6, 0, bgSprite->GetHandle(), TRUE);
        DrawRotaGraph(155, 642, 1.5, 0.0, (*marioSprite)[0], TRUE);
    }
}

void TitleScene::DrawStringCustom(int x, int y, const char* str) const
{
    // 背景テストのため一時的に不使用
}

void TitleScene::Finalize()
{
    delete bgSprite; bgSprite = nullptr;
}

eSceneType TitleScene::GetNowSceneType() const
{
    return eSceneType::eTitle;
}
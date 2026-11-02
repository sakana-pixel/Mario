#pragma once
#include "SceneBase.h"

class Sprite;
class DivSprite;

class TitleScene : public SceneBase {
private:
    // 背景・マリオ・キノコ
    Sprite* bgSprite;
    DivSprite* marioSprite;
    Sprite* mushroomSprite;

    // UI画像アセット
    Sprite* nameMarioSprite;
    Sprite* worldSprite;
    Sprite* timeSprite;
    Sprite* topSprite;
    DivSprite* coinSprite; // uicoin.png (4分割)

    // 文字フォントスプライト
    DivSprite* fontAlphaSprite;
    DivSprite* fontNumSprite;

    // タイマー・アニメーション
    float disp_timer;
    bool is_disp;
    int coinAnimFrame;
    int coinCurrentFrame;

    int selectMenu; // 0: 1 PLAYER GAME, 1: 2 PLAYER GAME

    // カスタム文字描画関数
    void DrawStringCustom(int x, int y, const char* str) const;

public:
    TitleScene();
    virtual ~TitleScene() override;

    virtual void Initialize() override;
    virtual void Finalize() override;
    virtual eSceneType Update(float delta_second) override;
    virtual void Draw() const override;

    virtual eSceneType GetNowSceneType() const override;

    int GetSelectMenu() const { return selectMenu; }
};
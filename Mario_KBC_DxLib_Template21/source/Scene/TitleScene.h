#pragma once
#include "SceneBase.h"

class Sprite;
class DivSprite;

class TitleScene : public SceneBase {
private:
    // UI用スプライト
    Sprite* bgSprite;

    Sprite* worldSprite;
    Sprite* timeSprite;
    Sprite* topSprite;

    // 分割スプライト
    DivSprite* marioSprite;
    DivSprite* coinSprite;
    DivSprite* fontAlphaSprite;
    DivSprite* fontNumSprite;

    // 点滅・アニメーション制御
    float disp_timer;
    bool is_disp;
    int coinAnimFrame;
    int coinCurrentFrame;

    int selectMenu;         // 0: 1 PLAYER GAME, 1: 2 PLAYER GAME

    // 文字列描画用の便利関数
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
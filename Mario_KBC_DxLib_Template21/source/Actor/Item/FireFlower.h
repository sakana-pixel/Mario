#pragma once
#include "DxLib.h"

class FireFlower {
private:
    float x;
    float y;
    int width;
    int height;
    int state;
    float startY;
    bool active;

    // アニメーション用
    int imageHandles[4]; // 4コマ分の画像を保存する配列
    int animFrame;       // アニメーションのカウント用
    int currentFrame;    // 現在表示するコマの番号 (0~3)

public:
    FireFlower();

    void Spawn(float startX, float startYPos);
    void Update();
    void Draw();
    void Deactivate();

    bool IsActive();
    float GetX();
    float GetY();
    int GetWidth();
    int GetHeight();
};
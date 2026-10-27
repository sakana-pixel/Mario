#pragma once
#include "DxLib.h"

class SuperStar {
private:
    float x;
    float y;
    float vx;
    float vy;
    float boundPower;
    int width;
    int height;
    int state;
    float startY;
    bool active;

    // アニメーション用
    int imageHandles[4];
    int animFrame;
    int currentFrame;

public:
    SuperStar();

    void Spawn(float startX, float startYPos);
    void Update(float groundY);
    void Draw();
    void Deactivate();

    bool IsActive();
    float GetX();
    float GetY();
    int GetWidth();
    int GetHeight();
};
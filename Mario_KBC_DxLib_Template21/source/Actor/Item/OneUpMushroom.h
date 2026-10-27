#pragma once
#include "DxLib.h"

class OneUpMushroom {
private:
    float x;
    float y;
    float vx;
    float vy;
    int width;
    int height;
    int state;
    float startY;
    bool active;
    int imageHandle;

public:
    OneUpMushroom();

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
#include "SuperStar.h"

SuperStar::SuperStar() {
    x = 0.0f;
    y = 0.0f;
    vx = 1.2f;
    vy = 0.0f;
    boundPower = -4.2f;
    width = 32;
    height = 32;
    state = 0;
    startY = 0.0f;
    active = false;
    animFrame = 0;
    currentFrame = 0;

    for (int i = 0; i < 4; i++) {
        imageHandles[i] = -1;
    }
}

void SuperStar::Spawn(float startX, float startYPos) {
    x = startX;
    y = startYPos;
    startY = startYPos;
    vx = 2.0f;
    vy = 0.0f;
    state = 0;
    active = true;
    animFrame = 0;
    currentFrame = 0;

    // 画像を4分割して読み込む
    LoadDivGraph("assets/Images/Item/star.png", 4, 4, 1, 32, 32, imageHandles);
}

void SuperStar::Update(float groundY) {
    if (active == false) return;

    if (state == 0) {
        y -= 1.0f;
        if (startY - y >= height) {
            state = 1;
            vy = boundPower;
        }
    }
    else if (state == 1) {
        x += vx;

        vy += 0.1f;
        y += vy;

        if (y + height >= groundY) {
            y = groundY - height;
            vy = boundPower;
        }
    }

    // --- アニメーションの更新 ---
    animFrame++;
    if (animFrame >= 4) { // スターはチカチカ早く点滅させたいので 4フレームごとに切り替え
        animFrame = 0;
        currentFrame = (currentFrame + 1) % 4;
    }
}

void SuperStar::Draw() {
    if (active == false || imageHandles[0] == -1) return;

    DrawGraph((int)x, (int)y, imageHandles[currentFrame], TRUE);
}

void SuperStar::Deactivate() {
    active = false;
}

bool SuperStar::IsActive() { return active; }
float SuperStar::GetX() { return x; }
float SuperStar::GetY() { return y; }
int SuperStar::GetWidth() { return width; }
int SuperStar::GetHeight() { return height; }
#include "FireFlower.h"

FireFlower::FireFlower() {
    x = 0.0f;
    y = 0.0f;
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

void FireFlower::Spawn(float startX, float startYPos) {
    x = startX;
    y = startYPos;
    startY = startYPos;
    state = 0;
    active = true;
    animFrame = 0;
    currentFrame = 0;

    // 画像を4分割して読み込む（全4枚、横4列、縦1行、1枚の横幅32px、縦幅32px）
    LoadDivGraph("assets/Images/Item/flower.png", 4, 4, 1, 32, 32, imageHandles);
}

void FireFlower::Update() {
    if (active == false) return;

    if (state == 0) {
        y -= 1.0f;
        if (startY - y >= height) {
            state = 1;
        }
    }

    // --- アニメーションの更新 ---
    animFrame++;
    if (animFrame >= 8) { // 8フレームごとに次のコマへ（数字を小さくすると高速化）
        animFrame = 0;
        currentFrame = (currentFrame + 1) % 4; // 0 -> 1 -> 2 -> 3 -> 0 ...
    }
}

void FireFlower::Draw() {
    if (active == false || imageHandles[0] == -1) return;

    // 現在のコマ番号（currentFrame）の画像を描画する
    DrawGraph((int)x, (int)y, imageHandles[currentFrame], TRUE);
}

void FireFlower::Deactivate() {
    active = false;
}

bool FireFlower::IsActive() { return active; }
float FireFlower::GetX() { return x; }
float FireFlower::GetY() { return y; }
int FireFlower::GetWidth() { return width; }
int FireFlower::GetHeight() { return height; }
//#include "DxLib.h"
//#include "Mushroom.h"
//#include "OneUpMushroom.h"
//#include "FireFlower.h"
//#include "SuperStar.h"
//
//int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
//    // 画面モードの設定
//    ChangeWindowMode(TRUE);
//    SetGraphMode(640, 480, 32);
//    if (DxLib_Init() == -1) return -1;
//    SetDrawScreen(DX_SCREEN_BACK);
//
//    // --- 1. 各アイテムのインスタンス作成 ---
//    Mushroom      mushroom;
//    OneUpMushroom oneUp;
//    FireFlower    flower;
//    SuperStar     star;
//
//    // --- 2. テスト出現（横に並べて出現させる） ---
//    // 画像は Spawn() の中で自動的に読み込まれます
//    mushroom.Spawn(100.0f, 300.0f);
//    oneUp.Spawn(200.0f, 300.0f);
//    flower.Spawn(300.0f, 300.0f);
//    star.Spawn(400.0f, 300.0f);
//
//    // テスト用の床の高さ
//    float groundY = 400.0f;
//
//    // メインループ
//    while (ProcessMessage() == 0 && ClearDrawScreen() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0) {
//
//        // SPACEキーを押したら全員再出現（なんども動作チェックするための仕組み）
//        if (CheckHitKey(KEY_INPUT_SPACE) == 1) {
//            mushroom.Spawn(100.0f, 300.0f);
//            oneUp.Spawn(200.0f, 300.0f);
//            flower.Spawn(300.0f, 300.0f);
//            star.Spawn(400.0f, 300.0f);
//        }
//
//        // --- 3. 更新処理 ---
//        mushroom.Update(groundY);
//        oneUp.Update(groundY);
//        flower.Update();
//        star.Update(groundY);
//
//        // --- 4. 描画処理 ---
//        // 床の描画（わかりやすいようにグレーの四角を描く）
//        DrawBox(0, (int)groundY, 640, 480, GetColor(128, 128, 128), TRUE);
//
//        // 各アイテムの描画
//        mushroom.Draw();
//        oneUp.Draw();
//        flower.Draw();
//        star.Draw();
//
//        // 操作説明のテキスト表示
//        DrawString(10, 10, "SPACEキー: アイテムを再出現", GetColor(255, 255, 255));
//        DrawString(10, 30, "ESCキー: 終了", GetColor(255, 255, 255));
//
//        ScreenFlip();
//    }
//
//    DxLib_End();
//    return 0;
//}
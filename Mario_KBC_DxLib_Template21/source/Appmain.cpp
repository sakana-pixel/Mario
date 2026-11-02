#include"DxLib.h"

#include"Input/InputManager.h"
#include"Scene/SceneManager.h"

//#include"Scene/SceneManager.h"

int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int)
{
	
	//ウインドウモードで起動
	ChangeWindowMode(TRUE);
	//画面サイズの設定（X軸MAX：1280　Y軸MAX：720）
	SetGraphMode(1024, 768, 32);
	//Dxライブラリの初期化処理
	if (DxLib_Init() == -1)
	{
		return -1;
	}
	//裏画面からウインドウを表示する
	SetDrawScreen(DX_SCREEN_BACK);
	SceneManager scenemanagaer;
	float delta_second(0.0f);

	while (ProcessMessage() != -1)
	{

		InputManager::Update();

		scenemanagaer.Update(delta_second);


		//画面の初期化
		ClearDrawScreen();

		//この下に処理を書いていく

		scenemanagaer.Draw();





		//裏画面を表画面にする
		ScreenFlip();

	}






	//Dxライブラリの終了処理
	DxLib_End();
	return 0;




}



#include"DxLib.h"

#define D_KEYCODE_MAX (256)

enum eInputState
{
	eNone,
	ePress,
	eRelease,
	eHold,

};

int CechKeycodeRange(int kecode);
eInputState GetKeyInputState(int keycode);

char now_key[D_KEYCODE_MAX];
char old_key[D_KEYCODE_MAX];

int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int)
{
	//ウインドウモードで起動
	ChangeWindowMode(TRUE);
	//画面サイズの設定（X軸MAX：1280　Y軸MAX：720）
	SetGraphMode(1280, 720, 32);
	//Dxライブラリの初期化処理
	if (DxLib_Init() == -1)
	{
		return -1;
	}
	//裏画面からウインドウを表示する
	SetDrawScreen(DX_SCREEN_BACK);

	//変数宣言場所
	int x = 10;
	int y = 10;

	while (ProcessMessage() != -1)
	{
		//画面の初期化
		ClearDrawScreen();
		//キーボードからの入力状況の確認
		memcpy(old_key, now_key, (sizeof(char) * D_KEYCODE_MAX));
		GetHitKeyStateAll(now_key);

		//この下に処理を書いていく
		DrawCircle(x, y, 10, GetColor(255, 255, 255), TRUE);
		if (GetKeyInputState(KEY_INPUT_RIGHT) == eHold)
		{
			x += 5;
		}
		if (GetKeyInputState(KEY_INPUT_DOWN) == eHold)
		{
			y += 5;
		}
		
		
		//この上に処理を書いていく
		 
		
		//裏画面を表画面にする
		ScreenFlip();
		//エスケープキーが押されたら描画終了する
		if (CheckHitKey(KEY_INPUT_ESCAPE) == ePress)
		{
			break;
		}
	}
	
	


	

	//Dxライブラリの終了処理
	DxLib_End();
	return 0;


	

}

int CechKeycodeRange(int keycode)
{
	if (0 <= keycode && keycode < D_KEYCODE_MAX)
	{
		return TRUE;
	}
	return FALSE;
	
}

eInputState GetKeyInputState(int keycode)
{
	if (old_key[keycode] == TRUE)
	{
		if (now_key[keycode] == TRUE)
		{
			return eHold;
		}
		else
		{
			return eRelease;
		}
	}
	else
	{
		if (now_key[keycode] == TRUE)
		{
			return ePress;
		}
	}

	return eNone;
}

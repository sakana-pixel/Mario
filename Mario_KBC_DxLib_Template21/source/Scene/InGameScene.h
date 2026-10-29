#pragma once

#include"SceneBase.h"
#include"../Actor/Actor.h"
#include"../File/Sprite.h"

#include<vector>
#include<string>
#include<stdexcept>

/// <summary>
/// インゲーム画面
/// </summary>
class InGameScene :public SceneBase
{
private:
	/// <summary>
	/// ゲームの状態設定
	/// </summary>
	enum eGameState :unsigned char
	{
		ePlay,//待機
		ePause,//遊ぶ
		eResult,//リザルト遷移
	};

private:
    int score;//スコア
	std::vector<Actor*>owned_actors;//所有するアクタ
	class Player* player;//プレイヤー情報
	class Enemy* enemy;//敵情報
	int bgm;//BGM
	int font_handle;//フォントハンドル
	eGameState state;//ゲームの状態

	std::vector<std::vector<std::string>>bg_data;//背景データ

	int floor;//床
	DivSprite* hatena;//ハテナブロック
	int block;//レンガブロック
	int hard_block;//固いブロック
	int dokan_lu;//土管　左上
	int dokan_ru;//土管　右上
	int dokan_ld;//土管　左下
	int dokan_rd;//土管　右下

	int cloud0, cloud1, cloud2, cloud3, cloud4, cloud5;//雲画像達
	int ha0, ha1, ha2;//葉っぱ画像達
	int Mt0, Mt1, Mt2, Mt3, Mt4, Mt5;//山画像達
	int sky;//空画像

public:
	InGameScene();
	virtual ~InGameScene();

public:
	virtual void Initialize() override;//初期化
	virtual eSceneType Update(float delta_second) override;//更新
	virtual void Draw() const override;//描画
	virtual void Finalize() override;//終了時処理

public:
	virtual eSceneType GetNowSceneType() const override;

private:
	void LoadStageData();//ステージ読み込み
	void LoadBackgroundData();//背景画像読み込み
	void ChangeGameState(eGameState new_state);//ゲーム状態の変更
	void PlayUpdate(float delta_second);//遊んでいる最中の更新処理
	void CheckCollision();//当たり判定を行う

public:
	
	
};

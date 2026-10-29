#pragma once

#include "../Utility/Math/Vector2.h"

/// <summary>
/// アクタの状態
/// </summary>
enum class eActorState : unsigned char
{
	eActive = 0,
	ePaused,
	eDead,
};

/// <summary>
/// アクタのタグ
/// </summary>
enum class eActorTag : unsigned char
{
	eNone,
	ePlayer,
	eEnemy,
	eWall,
	eItem,
	eCoin,
};

/// <summary>
/// 画面上に出てくるオブジェクトの基底クラス
/// </summary>
class Actor
{
protected:
	Vector2 location;//位置情報
	float radius;//半径情報
	int image;//画像情報
	double scale;//大きさ
	unsigned char z_layer;//Zレイヤー
	bool is_destroy;//死亡状態
	eActorState actor_state;//アクタの状態

public:
	Actor();
	virtual ~Actor();

public:
	//初期化処理
	virtual void Initialize();
	//更新処理
	virtual void Update(float delta_second);
	//描画処理
	virtual void Draw() const;
	//終了時処理
	virtual void Finalize();

public:
	//当たり判定通知処理
	virtual void OnHitCollisionEnter(Actor* actor);
	//タグの処理
	virtual eActorTag GetActorTag() const = 0;

public:
	//位置情報処理
	const Vector2& GetLocation() const;
	//半径情報処理
	float GetRadius() const;
	//アクトの状態取得
	eActorState GetState() const;
	//レイヤー情報の取得
	unsigned char GetZLayer() const;
	//位置情報の設定
	void SetLocation(const Vector2& location);

protected:
	//アクタの破棄
	void DestroyActor(Actor* target = nullptr);

};

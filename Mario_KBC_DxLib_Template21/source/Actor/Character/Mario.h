#pragma once
#include "Character.h"
#include <algorithm>
#include <vector>

enum eState
{
	tibi,
	deka,
	fire,
};

class Mario : public Character
{
private:
	Vector2 previousLocation;
	DivSprite move_animation;
	float animation_time;
	int animation_num;
	eState state;
	int level;
	float walkAcceleration;		//歩き加速度
	float dashAcceleration;		//ダッシュ加速度
	float walkMaxSpeed;			//歩き最大速度
	float dashMaxSpeed;			//ダッシュ最大速度
	float friction;				//慣性
	float airFriction;			//空中慣性
	float acceleration;			//加速度
	float maxSpeed;				//最大速度
	float jump;					//ジャンプ初速
	float jumpBoost;			//ジャンプ加速
	float jumpheldtime;			//ジャンプ加速時間
	float maxjumpheldtime;		//ジャンプ加速最大時間

	float collisionWidth;		//衝突判定幅
	float collisionHeight;		//衝突判定高さ

	float collisionLeft;		//衝突判定左端
	float collisionRight;		//衝突判定右端
	float collisionTop;			//衝突判定上端
	float collisionBottom;		//衝突判定下端

	float gravity;				//重力加速度

	float flag;
	bool star_mode;
	bool is_Ground;
	bool is_animation;
	bool is_jumptrigger;
	bool is_jumpheld;
	bool is_dash;
	bool animation_flag;

public:
	Mario();
	virtual ~Mario();

public:
	virtual void Initialize() override;
	virtual void Update(float delta_second) override;
	virtual void Finalize() override;

public:
	virtual void OnHitCollisionEnter(Actor* actor) override;
	eActorTag GetActorTag() const override;

public:
	void SetGround(bool ground);
	void SetVelocityY(float value);
	void SetVelocityX(float value);
	Vector2 GetPreviousLocation() const;

	void GetCollisionRect(float& left, float& top, float& right, float& bottom) const;		// 当たり判定範囲を取得
	void OnStompEnemy();		// 敵を踏んだとき
	void OnDamage();			// 敵にぶつかったとき

private:
	void InputCheck(float delta_second);
	void MoveAnimation(float delta_second);
	void UpdateCollision();
	void Tibi();
	void Deka();
	void Fire();
	void Jump(float delta_second);
	void Dash(float delta_second);
	bool isStar();

};


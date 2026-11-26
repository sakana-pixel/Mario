#include "Mario.h"
#include "../../File/AssetContainer.h"
#include "../../Input/InputManager.h"
#include <DxLib.h>

Mario::Mario()
	: Character()
	, animation_time()
	, animation_num()
	, state(tibi)
	, level(0)
	, move_animation("Mario/mario.png", 9, 1)
	, is_animation(false)
	, is_Ground(true)
	, is_jumptrigger(false)
	, is_jumpheld(false)
	, is_dash(false)
	, animation_flag(true)
{

}

Mario::~Mario()
{

}

void Mario::Initialize()
{
	AssetContainer* container = AssetContainer::Get();
	location = Vector2(155.0f, 626.0f);
	previousLocation;
	scale = 2.0f;
	speed = 1.0f;
	gravity = 1000.0f;
	walkAcceleration = 500.0f;
	dashAcceleration = 800.0f;
	walkMaxSpeed = 150.0f;
	dashMaxSpeed = 250.0f;
	friction = 500.0f;
	airFriction = 100.0f;
	jump = 400.0f;
	jumpBoost = 1500.0f;
	jumpheldtime = 0.0f;
	maxjumpheldtime = 0.3f;
	radius = 10.0f;
	collisionWidth = 24.0f;
	collisionHeight = 32.0f;
	flag = 0.0f;
	star_mode = false;
	image = move_animation[0];
}

void Mario::Update(float delta_second)
{
	InputCheck(delta_second);
	Jump(delta_second);
	

	// 移動前の座標を保存
	previousLocation = location;

	////重力
	velocity.y += gravity * delta_second;


	

	switch (state)
	{
	case tibi:
		Tibi();
		break;
	case deka:
		Deka();
		break;
	case fire:
		Fire();
		break;
	default:
		break;
	}


	Movement(delta_second);

	////仮地面
	//if (location.y >= 626.0f)
	//{
	//	location.y = 626.0f;
	//	velocity.y = 0.0f;
	//	is_Ground = true;
	//}

	UpdateCollision();
	MoveAnimation(delta_second);
}

void Mario::Finalize()
{

}

void Mario::OnHitCollisionEnter(Actor* actor)
{
	if (actor == nullptr) return;

	eActorTag tag = actor->GetActorTag();

	if (tag == eActorTag::eEnemy)
	{

	}
	else if (tag == eActorTag::eItem_Mushroom)
	{

	}
	else if (tag == eActorTag::eWall)
	{

	}
}

eActorTag Mario::GetActorTag() const
{
	return eActorTag::ePlayer;
}

Vector2 Mario::GetPreviousLocation() const
{
	return previousLocation;
}

void Mario::SetGround(bool ground)
{
	is_Ground = ground;
}

void Mario::SetVelocityY(float value)
{
	velocity.y = value;
}

void Mario::SetVelocityX(float value)
{
	velocity.x = value;
}


void Mario::GetCollisionRect(float& left, float& top, float& right, float& bottom) const
{
	left = collisionLeft;
	top = collisionTop;
	right = collisionRight;
	bottom = collisionBottom;
}

void Mario::OnStompEnemy()
{
	velocity.y = -250.0f;
	is_Ground = false;
}

void Mario::OnDamage()
{

}

void Mario::InputCheck(float delta_second)
{

	if (InputManager::GetButtonState(XINPUT_BUTTON_DPAD_LEFT) == eInputState::eHeld || InputManager::GetKeyState(KEY_INPUT_LEFT) == eInputState::eHeld)
	{
		flag = -1;
		direction = TRUE;
		is_animation = true;
		if (InputManager::GetButtonState(XINPUT_BUTTON_B) == eInputState::eHeld)
		{
			is_dash = true;
		}
	}
	else if (InputManager::GetButtonState(XINPUT_BUTTON_DPAD_RIGHT) == eInputState::eHeld || InputManager::GetKeyState(KEY_INPUT_RIGHT) == eInputState::eHeld)
	{
		flag = 1;
		direction = FALSE;
		is_animation = true;
		if (InputManager::GetButtonState(XINPUT_BUTTON_B) == eInputState::eHeld)
		{
			is_dash = true;
		}
		else
		{
			is_dash = false;
		}
	}
	else
	{
		flag = 0;
	}

	Dash(delta_second);

	if (flag!= 0)
	{
		velocity.x += flag * acceleration * delta_second;
	}
	else
	{
		is_animation = false;

		float currentFriction;

		if (is_Ground)
		{
			currentFriction = friction;
		}
		else
		{
			currentFriction = airFriction;
		}

		if (velocity.x > 0.0f)
		{
			velocity.x -= currentFriction * delta_second;

			if (velocity.x < 0.0f)
			{
				velocity.x = 0.0f;
			}
		}
		else if (velocity.x < 0.0f)
		{
			velocity.x += currentFriction * delta_second;

			if (velocity.x > 0.0f)
			{
				velocity.x = 0.0f;
			}
		}
	}

	if (!is_dash)
	{
		Dash(delta_second);
		if (velocity.x > maxSpeed)
		{
			velocity.x -= friction * delta_second;

			if (velocity.x < maxSpeed)
			{
				velocity.x = maxSpeed;
			}
		}
		else if (velocity.x < -maxSpeed)
		{
			velocity.x += friction * delta_second;

			if (velocity.x > -maxSpeed)
			{
				velocity.x = -maxSpeed;
			}
		}
	}

	is_jumptrigger =
		InputManager::GetButtonState(XINPUT_BUTTON_A) == eInputState::ePressed ||
		InputManager::GetKeyState(KEY_INPUT_SPACE) == eInputState::ePressed;

	is_jumpheld =
		InputManager::GetButtonState(XINPUT_BUTTON_A) == eInputState::eHeld ||
		InputManager::GetKeyState(KEY_INPUT_SPACE) == eInputState::eHeld;
}

void Mario::MoveAnimation(float delta_second)
{
	if (is_animation)
	{
		animation_time += delta_second;
		if (animation_time >= 0.3f)
		{
			if (animation_flag == true)
			{
				animation_num++;
				if (animation_num >= 4)
				{
					animation_flag = false;
					animation_num--;
				}
			}
			if (animation_flag == false)
			{
				animation_num--;
				if (animation_num <= 1)
				{
					animation_flag = true;
				}
			}
			animation_time = 0.0f;
			image = move_animation[animation_num];
		}
	}
	else
	{
		image = move_animation[0];
	}
}

void Mario::UpdateCollision()
{
	collisionLeft = location.x - collisionWidth / 2;
	collisionRight = location.x + collisionWidth / 2;

	collisionTop = location.y - collisionHeight / 2;
	collisionBottom = location.y + collisionHeight / 2;
}

void Mario::Tibi()
{

}

void Mario::Deka()
{

}

void Mario::Fire()
{

}

void Mario::Jump(float delta_second)
{
 	if (is_jumptrigger && is_Ground)
	{
		velocity.y = -jump;
		is_Ground = false;
		jumpheldtime = 0.0f;

		is_jumptrigger = false;
	}
	if (is_jumpheld && !is_Ground && velocity.y < 0.0f && jumpheldtime < maxjumpheldtime)
	{
		velocity.y -= jumpBoost * delta_second;
		jumpheldtime += delta_second;
	}
}

void Mario::Dash(float delta_second)
{
	if (is_dash)
	{
		acceleration = dashAcceleration;
		maxSpeed = dashMaxSpeed;
	}
	else
	{
		acceleration = walkAcceleration;
		maxSpeed = walkMaxSpeed;
	}
}

bool Mario::isStar()
{
	return star_mode = false;
}

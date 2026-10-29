#include "Mario.h"
#include "../../Scene/IngameScene.h"
#include "../../Input/InputManager.h"
#include "../../File/AssetContainer.h"
#include "../Item/FireFlower.h"
#include "../Item/Mushroom.h"
#include "../Item/OneUpMushroom.h"
#include "../Item/SuperStar.h"
#include <DxLib.h>

#define D_GRAVITY 1000.0f

Mario::Mario()
	: Character()
	, animation_time()
	, animation_num()
{
	
}

Mario::~Mario()
{

}

void Mario::Initialize()
{
	AssetContainer* container = AssetContainer::Get();
	state = tibi;
	speed = 1.0f;
	jump = 300.0f;
	jumpBoost = 400.0f;
	radius = 10.0f;
	star_mode = false;
	IsGround = true;
	
}

void Mario::Update(float delta_second)
{
	InputCheck(delta_second);
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

	//èdóÕ
	velocity.y += D_GRAVITY * delta_second;
	if (velocity.y < 0.05)
	{
		velocity.y = 0;
		IsGround = true;
	}
}

void Mario::Finalize()
{

}

void Mario::OnHitCollisionEnter(Actor* actor)
{
	eActorTag tag = actor->GetActorTag();

	if (tag == eActorTag::eEnemy)
	{

	}
	else if (tag == eActorTag::eItem)
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

void Mario::InputCheck(float delta_second)
{
	if (InputManager::GetButtonState(XINPUT_BUTTON_DPAD_LEFT) == eInputState::ePressed)
	{
		velocity.x = -speed;
	}
	else if (InputManager::GetButtonState(XINPUT_BUTTON_DPAD_RIGHT) == eInputState::ePressed)
	{
		velocity.x = speed;
	}
	else if (InputManager::GetButtonState(XINPUT_BUTTON_B) == eInputState::ePressed && InputManager::GetButtonState(XINPUT_BUTTON_DPAD_LEFT) == eInputState::ePressed || InputManager::GetButtonState(XINPUT_BUTTON_DPAD_RIGHT) == eInputState::ePressed)
	{
		speed = 2.0f;
	}
	else
	{
		velocity.x = 0;
		speed = 1.0f;
	}
	if (InputManager::GetButtonState(XINPUT_BUTTON_A) == eInputState::ePressed && IsGround == true)
	{
		velocity.y = -jump;
		IsGround = false;
	}
	if (InputManager::GetButtonState(XINPUT_BUTTON_A) == eInputState::eHeld && velocity.y < 0)
	{
		velocity.y -= jumpBoost * delta_second;
	}
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

bool Mario::isStar()
{
	return star_mode = false;
}

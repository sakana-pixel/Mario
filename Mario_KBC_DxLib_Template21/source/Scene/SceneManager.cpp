#include "SceneManager.h"
#include "TitleScene.h"
#include "InGameScene.h"
#include "CoffeeBreakScene.h"
#include "ResultScene.h"

SceneManager::SceneManager()
	: current_scene(nullptr)
{
	ChangeScene(eSceneType::eTitle);
}

SceneManager::~SceneManager()
{
	if (current_scene != nullptr)
	{
		current_scene->Finalize();
		delete current_scene;
		current_scene = nullptr;
	}
}

void SceneManager::Update(float delta_second)
{
	eSceneType next = current_scene->Update(delta_second);

	if (next != current_scene->GetNowSceneType())
	{
		ChangeScene(next);
	}
}

void SceneManager::Draw() const
{
	current_scene->Draw();
}

void SceneManager::ChangeScene(eSceneType new_scene_type)
{
	if (current_scene != nullptr)
	{
		current_scene->Finalize();
		delete current_scene;
	}

	current_scene = CreateScene(new_scene_type);
	current_scene->Initialize();
}

SceneBase* SceneManager::CreateScene(eSceneType new_scene_type)
{
	switch (new_scene_type)
	{
	case eSceneType::eTitle:
		return dynamic_cast<SceneBase*>(new TitleScene());
	case eSceneType::eInGame:
	case eSceneType::eRestart:
		return dynamic_cast<SceneBase*>(new InGameScene());
	case eSceneType::eCoffeeBreak:
		return dynamic_cast<SceneBase*>(new CoffeeBreakScene());
	case eSceneType::eResult:
		return dynamic_cast<SceneBase*>(new ResultScene());
	default:
		return nullptr;
	}
}

#pragma once

#include "SceneBase.h"

class SceneManager
{
private:
	SceneBase* current_scene;

public:
	SceneManager();
	~SceneManager();

public:
	void Update(float delta_second);
	void Draw() const;

private:
	void ChangeScene(eSceneType new_scene_type);
	SceneBase* CreateScene(eSceneType new_scene_type);
};

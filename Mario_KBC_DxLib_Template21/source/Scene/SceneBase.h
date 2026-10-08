#pragma once

#include "SceneType.h"

class SceneBase
{
private:

public:
	SceneBase() = default;
	virtual ~SceneBase() = default;

public:
	virtual void Initialize() {}
	virtual eSceneType Update(float delta_second) = 0;
	virtual void Draw() const {}
	virtual void Finalize() {}

public:
	virtual eSceneType GetNowSceneType() const = 0;

};

#pragma once
#include "Game/Object/Object.h"
#include "SCENE/Scene/Scene.h"

class Stage : public Object, Scene
{
public:
	Stage(Camera* camera);
	~Stage();

private:
	std::vector<class Enemy*> emy;

public:
	void BeginProcess()override;
	void Update() override;
	void Draw() override;
	void Reset() override;
};


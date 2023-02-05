#pragma once
#include "Game/Object/Object.h"
#include "SCENE/Scene/Scene.h"
#include "Game/Easing/Easing.h"

class Stage : public Object, Scene
{
public:
	Stage(Camera* camera);
	~Stage();

private:
	std::vector<class Enemy*> emy;

	Easing staging;
	int count;
	float easeSpd;

	class Goal* goal;

public:
	void Update() override;
	void Draw() override;
	void Reset() override;
};


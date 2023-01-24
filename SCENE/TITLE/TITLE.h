#pragma once
#include "Game/Object/Object.h"
#include "SCENE/Scene/Scene.h"

class Title : public Object, Scene
{
public:
	Title(Camera *camera);
	~Title();

private:

public:
	//
	void Update() override;

	void Reset() override;

	void Draw() override;

};


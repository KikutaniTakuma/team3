#pragma once
#include "Game/Object/Object.h"
#include "SCENE/Scene/Scene.h"

class Game_Clear : public Object, Scene
{
public:
	Game_Clear(Camera* camera);
	~Game_Clear();

private:
	//	�V�[���؂�ւ��p�t���O
	bool sceneFlag;
	//	�V�[���؂�ւ�
	void SceneChange();

	Texture BG;

public:
	void Update() override;

	void Reset() override;

	void Draw() override;

};


#pragma once
#include "Game/Object/Object.h"
#include "SCENE/Scene/Scene.h"

class Game_Over : public Object, Scene
{
public:
	Game_Over(Camera* camera);
	~Game_Over();

private:
	//	�V�[���؂�ւ��p�t���O
	bool sceneFlag;
	//	�V�[���؂�ւ�
	void SceneChange();

	Texture BG;

public:
	//	
	void BeginProcess() override;

	void Update() override;

	void Reset() override;

	void Draw() override;

};


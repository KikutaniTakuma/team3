#pragma once
#include "Game/Object/Object.h"
#include "SCENE/Scene/Scene.h"

class Title : public Object, Scene
{
public:
	Title(Camera *camera);
	~Title();

private:
	//	�V�[���؂�ւ��p�t���O
	bool sceneFlag;
	//	�V�[���؂�ւ�
	void SceneChange();

	Texture BG;
	unsigned int color;

	Quad testPos;
	Quad drawTestPos;

public:
	//	
	void BeginProcess() override;

	void Update() override;

	void Reset() override;

	void Draw() override;

	
};


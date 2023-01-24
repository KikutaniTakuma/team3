#pragma once
#include "Game/Object/Object.h"
#include "SCENE/Scene/Scene.h"

class Title : public Object, Scene
{
public:
	Title(Camera *camera);
	~Title();

private:
	//	シーン切り替え用フラグ
	bool sceneFlag;
	//	シーン切り替え
	void SceneChange();

	Texture BG;
	unsigned int color;
public:
	//	
	void Update() override;

	void Reset() override;

	void Draw() override;

	
};


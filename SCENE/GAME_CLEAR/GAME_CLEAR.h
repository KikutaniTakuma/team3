#pragma once
#include "Game/Object/Object.h"
#include "SCENE/Scene/Scene.h"
#include "Game/Easing/Easing.h"

class Game_Clear : public Object, Scene
{
public:
	Game_Clear(Camera* camera);
	~Game_Clear();

private:
	//	シーン切り替え用フラグ
	bool sceneFlag;
	//	シーン切り替え
	void SceneChange();

	Texture BG;

	Texture number[10];
	int score;

	Quad linePos[2];
	Easing easeLine[2];

	Quad charaPos;
	Easing easeNum;
	Quad gagePos;
	Easing gageEase;

public:
	void Update() override;

	void Reset() override;

	void Draw() override;

};


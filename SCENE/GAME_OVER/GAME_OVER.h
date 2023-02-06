#pragma once
#include "Game/Object/Object.h"
#include "SCENE/Scene/Scene.h"
#include "Game/Easing/Easing.h"

class Game_Over : public Object, Scene
{
public:
	Game_Over(Camera* camera);
	~Game_Over();

private:
	//	シーン切り替え用フラグ
	bool sceneFlag;
	//	シーン切り替え
	void SceneChange();

	Texture BG;

	Easing text;

public:

	void Update() override;

	void Reset() override;

	void Draw() override;

};


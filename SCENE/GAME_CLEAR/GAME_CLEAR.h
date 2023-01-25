#pragma once
#include "Game/Object/Object.h"
#include "SCENE/Scene/Scene.h"

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

public:
	//	
	void BeginProcess() override;

	void Update() override;

	void Reset() override;

	void Draw() override;

};


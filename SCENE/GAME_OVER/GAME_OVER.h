#pragma once
#include "Game/Object/Object.h"
#include "SCENE/Scene/Scene.h"
#include "Game/Easing/Easing.h"
#include "Game/Frame/Frame.h"

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

	const int kMaxText;
	Vector2D size;
	Texture gameoverText[8];
	Quad gameoverPos[8];
	Vector2D endPos[8];
	Easing text[8];

	int index;
	Frame easeFrame;

	bool select;
	Texture title;
	Quad titlePos;
	Texture restart;
	Quad restartPos;

	void EaseSet();

public:

	void Update() override;

	void Reset() override;

	void Draw() override;

};


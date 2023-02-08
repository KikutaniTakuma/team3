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

	//	損壊率関係
	Texture number[10];
	int score;
	int oneNum;
	int twoNum;

	//	左右からくるやつ
	Quad linePos[2];
	Easing easeLine[2];

	//	％
	Texture percent;
	Quad percentPos;

	//	損壊率
	Quad charaPos;
	Easing easeNum;
	//	損壊率の描画
	Quad gagePos[2];
	Easing gageEase[2];

	int getDigits(int value, int num);

	void SetScore();

public:
	void Update() override;

	void Reset() override;

	void Draw() override;

};


#pragma once
#include "Game/Object/Object.h"
#include "SCENE/Scene/Scene.h"
#include "Game/Easing/Easing.h"
#include "Game/Sound/Sound.h"

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

	bool select;

	//	損壊率関係
	Texture number[10];
	Texture text;
	int score;
	int oneNum;
	int twoNum;

	//	左右からくるやつ
	Quad linePos[2];
	Easing easeLine[2];

	//	％
	Texture percent;
	Quad percentPos;
	unsigned int perColor;

	//	損壊率
	Quad charaPos;
	Easing easeNum;
	//	損壊率の描画
	Quad gagePos[2];
	Easing gageEase[2];

	//	
	Texture title;
	Quad titlePos;
	Texture retry;
	Quad retryPos;

	//	コメント
	Texture comment[3];
	int commentNum;
	Quad commentPos;
	Easing comEase;

	int getDigits(int value, int num);

	void SetScore();

	Sound bgm;
	Sound se;
	Sound sceneSe;
	Sound selection;

public:
	void Update() override;

	void Reset() override;

	void Draw() override;

};


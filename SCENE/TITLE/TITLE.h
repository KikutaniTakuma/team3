#pragma once
#include "Game/Object/Object.h"
#include "SCENE/Scene/Scene.h"

#include <map>

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
	//	背景用
	Texture BG;
	unsigned int color;
	//	フェードアウト用
	Quad testPos;

	//	タイトルロゴ
	Texture titleText;
	Quad titleTextPos;

	//	キャラクター
	//	向き
	enum Direction {
		FRONT = 0,
		BACK,
		RIGHT,
		LEFT,
	};
	//	5人分
	const int kMaxChara;
	std::array<Direction, 5> dir;
	Vector2D size;

	//	std::map 連想配列クラス
	//	player = 0
	//	追跡型 = 1
	//	突進型 = 2
	//	徘徊型 = 3
	//	待伏型 = 4
	std::map<Direction, Texture> charaText[5];
	Quad charaTextPos[5];

	//	移動用
	Vector2D speed;
	Vector2D vel;
	void Move();

public:

	void Update() override;

	void Reset() override;

	void Draw() override;

	
};


#pragma once
#include "Game/Vector2D/Vector2D.h"
#include "Button/Button.h"
#include "Game/Object/Object.h"
#include <array>
#include "SCENE/Scene/Scene.h"
#include "Game/GoalUI/GoalUI.h"
#include "Game/Fade/Fade.h"

class Goal : public Object, Scene
{
public:
	Goal(Camera* camera, class Player* player);
	~Goal();

private:
	//	ボタン最大数
	const int kMaxButton;
	std::array<Button*, 4> button;
	std::array<GoalUI*, 4> buttonUI;


	GoalUI goalUI;
	
	//	ゴールが開いたならtrue
	bool goalAdvent;
	//	
	int count;
	//
	Vector2D rnd;
	//	シーン切り替え用フラグ
	bool gameClear;

	Player* player;

	unsigned int color;
	Fade goalAlpha;
	bool inout;

private:
	//
	Texture goalTexture;
	Texture buttonUITex;


public:
	//	ボタンの状態確認
	void StateUpdate();
	//	ボタンのセット
	void setBottonPos();
	//	ゴール座標の取得
	Vector2D getPos();
	//	ゴール座標の設定
	void setGoalPos(Vector2D pos);
	//
	bool getGameClear();

	bool getAdvent() const;

	//
	void Update() override;

	void Reset() override;

	void Draw() override;

	int GetButtonNum() const;

	Vector2D getButtonPos(size_t index) const;

	int getMaxButtonNum() const;

	void setSize(Vector2D size);
};

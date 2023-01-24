#pragma once
#include "Game/Vector2D/Vector2D.h"
#include "Button/Button.h"
#include "Game/Object/Object.h"
#include <array>

class Goal : public Object
{
public:
	Goal(Camera* camera);
	~Goal();

private:
	//	ボタン最大数
	const int kMaxButton;
	std::array<Button*, 4>button;
	
	//	ゴールが開いたならtrue
	bool goalAdvent;
	//	
	int count;
	//
	Vector2D rnd;
	

public:
	//	ボタンの状態確認
	void StateUpdate();
	//	ボタンのセット
	void setBottonPos();
	//	ゴール座標の取得
	Vector2D getPos();

	//
	void Update() override;

	void Reset() override;

	void Draw() override;

};

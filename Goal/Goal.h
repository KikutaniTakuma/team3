#pragma once
#include "Game/Vector2D/Vector2D.h"
#include "Button/Button.h"

class Goal
{
public:
	Goal();
	~Goal();

private:
	//	ボタン最大数
	const int kMaxButton;
	Button* button;
	
	//	ゴールが開いたならtrue
	bool goalAdvent;
	//	
	int count;
	//
	Vector2D ram;
	
	Vector2D pos;
	Vector2D size;

public:
	//	ボタンの状態確認
	void StateUpdate();
	//	ボタンのセット
	void setBottonPos();
	//	ゴール座標の取得
	Vector2D getPos();

	//
	void Update();

	void Draw();

};

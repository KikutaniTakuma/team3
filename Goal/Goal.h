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

public:
	//	ボタンの状態確認
	void StateUpdate();
	
	//
	void Update();

	void Draw();

};

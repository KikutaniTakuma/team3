#pragma once
#include "Game/MyMath/MyMath.h"
#include "Game/Vector2D/Vector2D.h"

class Button
{
public:
	Button();

private:
	//	押されたらtrue
	bool isPushButton;
	//
	Vector2D pos;
	Vector2D size;

public:
	//	プレイヤーとの衝突用の関数
	void Collision(Vector2D playerPos, Vector2D playerSize);

	//	ボタンの状態取得
	bool getPushButton();

	//	ボタンの座標の設定
	void setPos(Vector2D pos);

};


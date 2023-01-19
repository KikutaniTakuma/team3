#pragma once
#include "Game/MyMath/MyMath.h"
#include "Game/Vector2D/Vector2D.h"
#include "Game/Object/Object.h"

class Button : public Object
{
public:
	Button(Camera* camera);

private:
	//	押されたらtrue
	bool isPushButton;
	

public:
	//	プレイヤーとの衝突用の関数
	void Collision(Vector2D playerPos, Vector2D playerSize);

	//	ボタンの状態取得
	bool getPushButton();

	//	ボタンの座標の設定
	void setPos(Vector2D pos);
	Vector2D getPos();

	void Update() override;

	void Reset() override;

	void Draw(class Texture& tex) override;

};


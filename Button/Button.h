#pragma once
#include "Game/MyMath/MyMath.h"
#include "Game/Vector2D/Vector2D.h"
#include "Game/Object/Object.h"
#include "Game/Sound/Sound.h"

class Button : public Object
{
public:
	Button(Camera* camera);

private:
	//	押されたらtrue
	bool isPushButton;

	Sound buttonSE;
	float seVolum;
	bool seFlg;

	//	
	Texture onButtonTexture;
	Texture offButtonTexture;
public:
	//	プレイヤーとの衝突用の関数
	void Collision(Quad playerPos);

	//	ボタンの状態取得
	bool getPushButton();

	//	ボタンの座標の設定
	void setPos(Vector2D pos);
	Vector2D getPos();

	void Update() override;

	void Reset() override;

	void Draw() override;

};


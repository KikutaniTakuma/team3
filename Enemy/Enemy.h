#pragma once

#include "Game/Object/Object.h"
#include "Game/Frame/Frame.h"
#include "Game/Sound/Sound.h"
#include "SCENE/Scene/Scene.h"

class Enemy : public Object, public Scene {
protected:
	enum class Direction : short {
		LEFT = 0,
		RIGHT,
		FRONT,
		BACK
	};

public:
	static const int kMaxEmyNum;

public:
	Enemy() = delete;
	Enemy(Camera* cameraPointa, class Player* player);

protected:
	Vector2D moveVec;

	Vector2D tentativPos;

	float spd;

	float nmlSpd;
	float lowSpd;

	Vector2D shakeScale;
	bool stopFlg;

	Frame frm;
	unsigned int lowTime;

	float rndLen;

	Sound blockBrk;
	bool blockBrkFlg;

	// テクスチャ
	Texture front;
	Texture back;
	Texture right;
	Texture left;

	// 方向
	Direction dir;

	// フレーム管理クラスのインスタンス
	Frame frame;

	int rndTime;

	float lowArea;
	float nmlArea;
	float area;

public:
	const class Player* player;

protected:
	void Collision();


public:
	virtual void Update() override;

	virtual void Draw() override;
	
	virtual void Reset() override;
};
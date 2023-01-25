#pragma once

#include "Game/Object/Object.h"
#include "Game/Astar/Astar.h"
#include "Game/Frame/Frame.h"

class Enemy : public Object {
public:
	enum Dirextion {
		LEFT = 0,
		RIGHT,
		UP,
		DOWN
	};

	static const int kMaxEmyNum;

public:
	Enemy() = delete;
	Enemy(Camera* cameraPointa, class Player* player);

private:
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

public:
	const class Player* player;

private:
	void Collision();


public:
	void Update() override;

	void Draw() override;
	
	void Reset() override;
};
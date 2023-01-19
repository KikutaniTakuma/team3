#pragma once

#include "Game/Object/Object.h"
#include "Game/Astar/Astar.h"

class Enemy : public Object {
public:
	enum Dirextion {
		LEFT = 0,
		RIGHT,
		UP,
		DOWN
	};

public:
	Enemy() = delete;
	Enemy(Camera* cameraPointa, class Player* player);

private:
	Vector2D moveVec;

	Vector2D tentativPos;

	float spd;

public:
	const class Player* player;

private:
	void Collision();

//private:
//	// A*ƒAƒ‹ƒSƒŠƒYƒ€—pŠÖ”
	Astar astr;


public:
	void Update() override;

	void Draw(Texture& tex) override;
	
	void Reset() override;
};
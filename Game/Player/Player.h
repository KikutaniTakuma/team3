#pragma once
#include "Game/Object/Object.h"
#include "SCENE/Scene/Scene.h"
#include <map>

class Player final : public Object, Scene {
public:
	struct State {
		float hp;
		float attck;
		float spd;
	};

	enum Direction {
		LEFT = 0,
		RIGHT,
		FRONT,
		BACK
	};

public:
	Player() = delete;
	Player(Camera* camera);
	~Player();

private:
	Vector2D* tentativPos;
	Vector2D* size;
	Vector2D* moveVec;

	float nmlSpd;

	bool flgJump;
	bool flgJumpSecond;

	float jumpValue;
	float jumpSeconsdValue;

	bool flgGravity;
	float gravity;

	unsigned short deadZone;

	// èdóÕÇ»ÇµÇ©Ç«Ç§Ç©
	bool flgZeroGravity;

	Direction dir;
	std::map<Direction, Texture> tex;

	float highSpd;
	float spd;

public:
	bool isAlive;

public:
	void Update() override;

	void Draw() override;

	void Reset() override;

private:
	void Move();

	void Jump();

	void Collision();

public:
	// getter
	Vector2D getWorldPos() const;
	float getWorldPosX() const;
	float getWorldPosY() const;
	float getSize()const;

	Vector2D getMoveVec() const;

	// setter
	void setWorldPosX(const float& num);
	void setWorldPosY(const float& num);
	void setWorldPos(Vector2D pos);
};
#pragma once
#include "Game/Object/Object.h"
#include "SCENE/Scene/Scene.h"

class Vector2D;
class Matrix3x3;

class Player final : public Object, Scene {
public:
	struct State {
		float hp;
		float attck;
		float spd;
	};

	enum Dirextion {
		LEFT = 0,
		RIGHT,
		UP,
		DOWN
	};

public:
	Player() = delete;
	Player(Camera* camera);
	~Player();

private:
	Vector2D* tentativPos;
	Vector2D* size;
	Vector2D* moveVec;

	float spd;

	bool flgJump;
	bool flgJumpSecond;

	float jumpValue;
	float jumpSeconsdValue;

	bool flgGravity;
	float gravity;

	unsigned short deadZone;

	// èdóÕÇ»ÇµÇ©Ç«Ç§Ç©
	bool flgZeroGravity;

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

	// setter
	void setWorldPosX(const float& num);
	void setWorldPosY(const float& num);
	void setWorldPos(Vector2D pos);
};
#pragma once

#include "Enemy/Enemy.h"
#include "Game/Easing/Easing.h"

class Heavy : public Enemy {
public:
	Heavy() = delete;
	Heavy(Camera* camera, class Player* player);
	Heavy(Camera* camera, class Player* player, Vector2D pos);

private:
	bool rushFlg;
	float rushSpd;
	float rushLen;
	Easing rushEase;
	float maxSpd;

public:
	void Update() override;
	void Draw() override;
	void Reset() override;
};
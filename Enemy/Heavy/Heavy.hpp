#pragma once

#include "Enemy/Enemy.h"
#include "Game/Easing/Easing.h"

class Heavy : public Enemy {
public:
	Heavy() = delete;
	Heavy(Camera* camera, class Player* player);

private:
	bool rushFlg;
	float rushSpd;
	float rushLen;
	Easing rushEase;

public:
	void Update() override;
	void Draw() override;
	void Reset() override;
};
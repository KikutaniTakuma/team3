#pragma once

#include "Enemy/Enemy.h"

class Brave final : public Enemy {
public:
	Brave() = delete;
	Brave(Camera* camera, class Player* player, class Goal* goal);

private:
	Goal* goal;
	size_t goalNum;

public:
	void Update() override;
	void Draw() override;
};
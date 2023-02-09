#pragma once

#include "Enemy/Enemy.h"

class Assassin final : public Enemy {
public:
	Assassin() = delete;
	Assassin(Camera* camera, class Player* player);
	Assassin(Camera* camera, class Player* player, Vector2D pos);

public:
	void Update() override;
	void Draw() override;
};
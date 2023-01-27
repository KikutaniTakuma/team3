#pragma once

#include "Enemy/Enemy.h"

class Wizard final : public Enemy {
public:
	Wizard() = delete;
	Wizard(Camera* camera, class Player* player);

public:
	void Update() override;
	void Draw() override;
	void Reset() override;
};
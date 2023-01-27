#pragma once

#include "Enemy/Enemy.h"

class Wizard final : public Enemy {
public:
	Wizard() = delete;
	Wizard(Camera* camera);

public:
	void Update() override;
	void Draw() override;
	void Reset() override;
};
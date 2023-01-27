#pragma once

#include "Enemy/Enemy.h"

class Brave final : public Enemy {
public:
	Brave() = delete;
	Brave(Camera* camera);

public:
	void Update() override;
	void Draw() override;
	void Reset() override;
};
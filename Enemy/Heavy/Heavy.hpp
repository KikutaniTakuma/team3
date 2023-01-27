#pragma once

#include "Enemy/Enemy.h"

class Heavy final : public Enemy {
public:
	Heavy() = delete;
	Heavy(Camera* camera);

public:
	void Update() override;
	void Draw() override;
	void Reset() override;
};
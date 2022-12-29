#pragma once

#include "Game/Object/Object.h"

class Enemy : public Object {
public:
	Enemy() = delete;
	Enemy(class Camera* cameraPointa);

public:
	void Update() override;

	void Draw(Texture& tex) override;
	
	void Reset() override;
};
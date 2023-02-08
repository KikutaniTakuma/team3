#pragma once

#include "Game/Object/Object.h"
#include <map>

class Hud : public Object {
public:
	Hud(Camera* camera);

private:
	unsigned int nmlColor;
	unsigned int pushColor;

	std::map<int, Texture> tex;

	std::map<int, Quad> wasdPos;

public:
	void Update() override;

	void Draw() override;

	inline void Reset()override{}
};
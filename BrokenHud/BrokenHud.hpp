#pragma once

#include "Game/Object/Object.h"
#include <map>

class BrokenHud : public Object {
public:
	BrokenHud(Camera* camera);


private:
	std::map<int, Texture> tex;

	float deadline;
	unsigned int color;
	unsigned int lowColor;

public:
	static float broknePer;

public:
	void Update() override;
	void Draw() override;
	inline void Reset() override {}
};
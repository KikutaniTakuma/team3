#pragma once

#include <Novice.h>

#include "SCENE/SceneManager/SceneManager.hpp"

class World {
public:
	World();
	~World();

private:
	void Input();
	void Reset();

public:
	void MainLoop();

private:
	class Camera* camera;

	std::unique_ptr<SceneManager> game;

	WindowMode winMode;
};
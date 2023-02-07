#pragma once

#include <vector>
#include <map>

#include <Novice.h>
#include "SCENE/Scene/Scene.h"

class World {
public:
	World();
	~World();

private:
	void Input();
	void Reset();
	void Update();
	void Draw();

public:
	void MainLoop();

private:
	class Camera* camera;

	std::map<Scene::Situation, class Object*> object;

	WindowMode winMode;

private:
	Scene scene;

	//Title title;
	//Stage stage;
	//Game_Clear game_clear;
	//Game_Over game_over;
};
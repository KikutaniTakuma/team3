#pragma once

#include <vector>
#include <map>

#include "SCENE/TITLE/TITLE.h"
#include "SCENE/STAGE/STAGE.h"
#include "SCENE/GAME_CLEAR/GAME_CLEAR.h"
#include "SCENE/GAME_OVER/GAME_OVER.h"
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


private:
	Scene scene;

	//Title title;
	//Stage stage;
	//Game_Clear game_clear;
	//Game_Over game_over;
};
#pragma once

#include <vector>

#include "Goal/Goal.h"
#include "SCENE/TITLE/TITLE.h"
#include "SCENE/STAGE/STAGE.h"
#include "SCENE/GAME_CLEAR/GAME_CLEAR.h"
#include "SCENE/GAME_OVER/GAME_OVER.h"

class World {
private:
	//	ÉVÅ[Éìenum
	enum class Scene
	{
		TITLE, // 0
		STAGE,
		GAME_CLEAR,
		GAME_OVER,

		MAX_SCENE
	};

public:
	World();
	World(int screenSizeX, int screenSizeY);
	~World();

private:
	void BeginProcess();
	void Input();
	void Reset();
	void Update();
	void Draw();

public:
	void MainLoop();

private:
	class Camera* camera;

	std::vector<class Object*> object;

	class Texture* whiteBox;

	Goal goal;

private:
	Scene scene = Scene::TITLE;

	Title title;
	Stage stage;
	Game_Clear game_clear;
	Game_Over game_over;
};
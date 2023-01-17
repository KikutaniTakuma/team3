#pragma once

#include <vector>
#include "Goal/Goal.h"

class World {
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
	//	ÉVÅ[Éìenum
	enum class SCENE
	{
		TITLE, // 0
		STAGE,
		GAME_CLEAR,
		GAME_OVER,

		MAX_SCENE
	}scene = SCENE::STAGE;
};
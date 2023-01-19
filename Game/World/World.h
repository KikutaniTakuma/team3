#pragma once

#include <vector>
#include <map>


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

	void AddObj(Scene scene, class Object* obj);

public:
	void MainLoop();

private:
	class Camera* camera;

	std::map<Scene, std::vector<Object*>> object;

	class Texture* whiteBox;


private:
	Scene scene;

	Title title;
	Stage stage;
	Game_Clear game_clear;
	Game_Over game_over;
};
#pragma once

#include <vector>

class Scene {
public:
	enum class Situation {
		TITLE = 0, // 0
		STAGE,
		GAME_CLEAR,
		GAME_OVER,

		MAX_SCENE
	};
public:
	Scene();

protected:
	static Situation scene;
	static Situation preScene;

	bool IsChange() const;

	std::vector<class Object*> obj;

public:
	void Update();
	Situation getScene();
};
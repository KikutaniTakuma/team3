#pragma once

class Scene {
public:
	enum class Situation {
		TITLE = 0, // 0
		STAGE,
		GAME_CLEAR,
		GAME_OVER,

		MAX_SCENE
	};

protected:
	static Situation scene;

public:
	Situation getScene();
};
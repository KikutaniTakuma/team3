#pragma once

#include "SCENE/Scene/Scene.h"
#include "Game/Object/Object.h"
#include <map>
#include <memory>

class SceneManager {
public:
	SceneManager(class Camera* camera);
	~SceneManager();

private:
	std::map<Scene::Situation, std::unique_ptr<Object>> gameScene;

	Camera* camera;

	Scene scene;

private:
	bool Manager();

public:
	void Update();

	void Draw();
};
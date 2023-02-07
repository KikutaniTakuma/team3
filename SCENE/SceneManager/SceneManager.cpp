#include "SceneManager.hpp"
#include "Game/Camera/Camera.h"

#include "SCENE/TITLE/TITLE.h"
#include "SCENE/STAGE/STAGE.h"
#include "SCENE/GAME_CLEAR/GAME_CLEAR.h"
#include "SCENE/GAME_OVER/GAME_OVER.h"
#include "Goal/Goal.h"
#include "Game/Player/Player.h"

SceneManager::SceneManager(Camera* camera) :
	camera(camera)
{
	gameScene.insert(std::make_pair(Scene::Situation::STAGE, new Stage(camera)));
	gameScene.insert(std::make_pair(Scene::Situation::TITLE, new Title(camera)));
	gameScene.insert(std::make_pair(Scene::Situation::GAME_CLEAR, new Game_Clear(camera)));
	gameScene.insert(std::make_pair(Scene::Situation::GAME_OVER, new Game_Over(camera)));
}

SceneManager::~SceneManager() {

}

bool SceneManager::Manager() {
	if (scene.getPreSituation() == Scene::Situation::STAGE && scene.getSituation() != Scene::Situation::STAGE) {
		gameScene[Scene::Situation::STAGE].reset(new Stage(camera));
		camera->shakeFlg = false;
		return true;
	}
	else if (scene.getPreSituation() == Scene::Situation::GAME_CLEAR && scene.getSituation() != Scene::Situation::GAME_CLEAR) {
		gameScene[Scene::Situation::GAME_CLEAR].reset(new Game_Clear(camera));
		camera->shakeFlg = false;
		return true;
	}
	else if (scene.getPreSituation() == Scene::Situation::GAME_OVER && scene.getSituation() != Scene::Situation::GAME_OVER) {
		gameScene[Scene::Situation::GAME_OVER].reset(new Game_Over(camera));
		camera->shakeFlg = false;
		return true;
	}
	else if (scene.getPreSituation() == Scene::Situation::TITLE && scene.getSituation() != Scene::Situation::TITLE) {
		gameScene[Scene::Situation::TITLE].reset(new Title(camera));
		camera->shakeFlg = false;
		return true;
	}
	else {
		return false;
	}
}

void SceneManager::Update() {
	scene.Update();
	gameScene[scene.getSituation()]->Update();
	if (Manager()) {
		gameScene[scene.getSituation()]->Update();
	}
}

void SceneManager::Draw() {
	gameScene[scene.getSituation()]->Draw();
}
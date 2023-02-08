#include "SceneManager.hpp"
#include "Game/Camera/Camera.h"

#include "SCENE/TITLE/TITLE.h"
#include "SCENE/STAGE/STAGE.h"
#include "SCENE/GAME_CLEAR/GAME_CLEAR.h"
#include "SCENE/GAME_OVER/GAME_OVER.h"
#include "Goal/Goal.h"
#include "Game/Player/Player.h"
#include "Game/MapChip/MapChip.h"
#include "BrokenHud/BrokenHud.hpp"

SceneManager::SceneManager(Camera* camera) :
	camera(camera)
{
	gameScene.insert(std::make_pair(Scene::Situation::STAGE, std::make_unique<Stage>(camera)));
	gameScene.insert(std::make_pair(Scene::Situation::TITLE, std::make_unique <Title>(camera)));
	gameScene.insert(std::make_pair(Scene::Situation::GAME_CLEAR, std::make_unique<Game_Clear>(camera)));
	gameScene.insert(std::make_pair(Scene::Situation::GAME_OVER, std::make_unique<Game_Over>(camera)));
}

SceneManager::~SceneManager() {

}

bool SceneManager::ChangeProc() {
	if (scene.getPreSituation() == Scene::Situation::STAGE && scene.getSituation() != Scene::Situation::STAGE) {
		gameScene[Scene::Situation::STAGE].reset();
		gameScene[Scene::Situation::STAGE] = std::make_unique<Stage>(camera);
		camera->shakeFlg = false;
		return true;
	}
	else if (scene.getPreSituation() == Scene::Situation::GAME_CLEAR && scene.getSituation() != Scene::Situation::GAME_CLEAR) {
		gameScene[Scene::Situation::GAME_CLEAR].reset();
		gameScene[Scene::Situation::GAME_CLEAR] = std::make_unique<Game_Clear>(camera);
		camera->shakeFlg = false;
		BrokenHud::broknePer = 100.0f;
		return true;
	}
	else if (scene.getPreSituation() == Scene::Situation::GAME_OVER && scene.getSituation() != Scene::Situation::GAME_OVER) {
		gameScene[Scene::Situation::GAME_OVER].reset();
		gameScene[Scene::Situation::GAME_OVER] = std::make_unique<Game_Over>(camera);
		camera->shakeFlg = false;
		BrokenHud::broknePer = 100.0f;
		return true;
	}
	else if (scene.getPreSituation() == Scene::Situation::TITLE && scene.getSituation() != Scene::Situation::TITLE) {
		gameScene[Scene::Situation::TITLE].reset();
		gameScene[Scene::Situation::TITLE] = std::make_unique<Title>(camera);
		camera->shakeFlg = false;
		BrokenHud::broknePer = 100.0f;
		return true;
	}
	else {
		return false;
	}
}

void SceneManager::Update() {
	scene.Update();
	gameScene[scene.getSituation()]->Update();
}

void SceneManager::Draw() {
	if (!ChangeProc()) {
		gameScene[scene.getSituation()]->Draw();
	}
	else {
		MapChip::Reset();
	}
}
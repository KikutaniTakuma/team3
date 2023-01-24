#include "Scene.h"

Scene::Situation Scene::scene = Scene::Situation::STAGE;

Scene::Situation Scene::getScene() {
	return scene;
}
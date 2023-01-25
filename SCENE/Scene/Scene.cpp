#include "Scene.h"

Scene::Situation Scene::scene = Scene::Situation::TITLE;

Scene::Situation Scene::getScene() {
	return scene;
}
#include "Scene.h"

Scene::Situation Scene::scene = Scene::Situation::TITLE;
Scene::Situation Scene::preScene = scene;

Scene::Scene():
	obj(0)
{}

Scene::Situation Scene::getScene() {
	return scene;
}

void Scene::Update() {
	preScene = scene;
}

bool Scene::IsChange() const{
	return scene != preScene;
}
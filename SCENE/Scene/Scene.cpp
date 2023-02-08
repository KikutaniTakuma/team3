#include "SCENE/Scene/Scene.h"

Scene::Situation Scene::situation = Scene::Situation::GAME_CLEAR;
Scene::Situation Scene::preSituation = situation;

Scene::Scene():
	obj(0)
{}

Scene::Situation Scene::getSituation() const{
	return situation;
}

Scene::Situation Scene::getPreSituation()const {
	return preSituation;
}

void Scene::Update() {
	preSituation = situation;
}

bool Scene::IsChange() {
	return situation != preSituation;
}
#include "SCENE/STAGE/STAGE.h"
#include "Game/Player/Player.h"
#include "Enemy/Enemy.h"
#include "Game/GoalUI/GoalUI.h"
#include "Goal/Goal.h"
#include "Game/MapChip/MapChip.h"
#include "Game/MyMath/MyMath.h"
#include "Enemy/Heavy/Heavy.hpp"
#include "Enemy/Assassin/Assassin.hpp"
#include "Enemy/Brave/Brave.hpp"

Stage::Stage(Camera* camera) :
	Object(camera),
	emy(0),
	count(0),
	easeSpd(0.008f)
{
	Player* player = new Player(camera);
	goal = new Goal(camera, player);
	obj.push_back(player);

	emy.push_back(new Enemy(camera, player));
	emy.push_back(new Heavy(camera, player));
	emy.push_back(new Assassin(camera, player));
	emy.push_back(new Brave(camera, player, goal));

	obj.push_back(goal);

	staging.Set(MapChip::getPlyPos(), goal->getButtonPos(count), easeSpd, Easing::EaseInOutQuart);
}

Stage::~Stage() {
	for (auto& i : obj) {
		delete i;
	}
	for (auto& i : emy) {
		delete i;
	}
}

void Stage::Update() {
	camera->scale = 1.3f;

	if (count < goal->getMaxButtonNum()) {
		camera->worldPos = staging.Update();

		if (!staging) {
			staging.Set(goal->getButtonPos(count), goal->getButtonPos(count + 1), easeSpd, Easing::EaseInOutQuart);
			count++;
			if (count == goal->getMaxButtonNum()) {
				staging.Set(goal->getButtonPos(count - 1), MapChip::getPlyPos(), easeSpd, Easing::EaseInOutQuart);
			}
		}
	}
	else if (count >= goal->getMaxButtonNum() - 1) {
		camera->worldPos = staging.Update();
	}

	if(!staging && count == goal->getMaxButtonNum()){
		for (auto& i : obj) {
			i->Update();
		}
		for (auto& i : emy) {
			i->Update();
		}
	}
}

void Stage::Draw() {
	MapChip::Draw(whiteBox);

	for (auto& i : obj) {
		i->Draw();
	}
	for (auto& i : emy) {
		i->Draw();
	}
}

void Stage::Reset() {
	for (auto& i : obj) {
		MyMath::SafeDelete(i);
	}
	obj.resize(0);
	for (auto& i : emy) {
		MyMath::SafeDelete(i);
	}
	emy.resize(0);

	Player* player = new Player(camera);
	goal = new Goal(camera, player);
	obj.push_back(player);

	emy.push_back(new Enemy(camera, player));
	emy.push_back(new Heavy(camera, player));
	emy.push_back(new Assassin(camera, player));
	emy.push_back(new Brave(camera, player, goal));

	obj.push_back(goal);

	count = 0;

	staging.Set(MapChip::getPlyPos(), goal->getButtonPos(count), easeSpd, Easing::EaseInOutQuart);
}
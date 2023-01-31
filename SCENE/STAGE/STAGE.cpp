#include "SCENE/STAGE/STAGE.h"
#include "Game/Player/Player.h"
#include "Enemy/Enemy.h"
#include "Game/GoalUI/GoalUI.h"
#include "Goal/Goal.h"
#include "Game/MapChip/MapChip.h"
#include "Enemy/Heavy/Heavy.hpp"

Stage::Stage(Camera* camera) :
	Object(camera),
	emy(0)
{
	Player* player = new Player(camera);
	Goal* goal = new Goal(camera, player);
	obj.push_back(player);

	for (int i = 0; i < Enemy::kMaxEmyNum - 1; i++) {
		obj.push_back(new Enemy(camera, player));
	}

	emy.push_back(new Heavy(camera, player));

	obj.push_back(new GoalUI(camera, goal));

	obj.push_back(goal);
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
	for (auto& i : obj) {
		i->Update();
	}
	for (auto& i : emy) {
		i->Update();
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
		delete i;
	}
	obj.resize(0);
	for (auto& i : emy) {
		delete i;
	}
	emy.resize(0);

	Player* player = new Player(camera);
	Goal* goal = new Goal(camera, player);

	/*obj.push_back(goal);*/

	for (int i = 0; i < Enemy::kMaxEmyNum -1; i++) {
		obj.push_back(new Enemy(camera, player));
	}
	emy.push_back(new Heavy(camera, player));

	obj.push_back(new GoalUI(camera, goal));

	obj.push_back(goal);

	obj.push_back(player);
}
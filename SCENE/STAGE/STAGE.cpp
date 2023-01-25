#include "SCENE/STAGE/STAGE.h"
#include "Game/Player/Player.h"
#include "Game/Enemy/Enemy.h"
#include "Game/GoalUI/GoalUI.h"
#include "Goal/Goal.h"
#include "Game/MapChip/MapChip.h"

Stage::Stage(Camera* camera) :
	Object(camera)
{
	Player* player = new Player(camera);
	Goal* goal = new Goal(camera);

	obj.push_back(player);

	for (int i = 0; i < Enemy::kMaxEmyNum; i++) {
		obj.push_back(new Enemy(camera, player));
	}

	obj.push_back(goal);

	obj.push_back(new GoalUI(camera, goal));
}

Stage::~Stage() {
	for (auto& i : obj) {
		delete i;
	}
}

void Stage::BeginProcess() {
	for (auto& i : obj) {
		i->BeginProcess();
	}
}

void Stage::Update() {
	for (auto& i : obj) {
		i->Update();
	}
}

void Stage::Draw() {
	MapChip::Draw(whiteBox);

	for (auto& i : obj) {
		i->Draw();
	}
}

void Stage::Reset() {
	for (auto& i : obj) {
		delete i;
	}
	obj.resize(0);

	Player* player = new Player(camera);
	Goal* goal = new Goal(camera);

	obj.push_back(player);

	for (int i = 0; i < Enemy::kMaxEmyNum; i++) {
		obj.push_back(new Enemy(camera, player));
	}

	obj.push_back(goal);

	obj.push_back(new GoalUI(camera, goal));
}
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
#include "Game/KeyInput/KeyInput.h"

Stage::Stage(Camera* camera) :
	Object(camera),
	emy(0),
	count(0),
	easeSpd(0.008f),
	flgSkip(false),
	flgSkipSecond(false),
	tex(Texture("./Resources/startText.png",800,800,150)),
	ButtonTex(Texture("./Resources/ButtonOff.png", 32, 32, 32))
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
	start.Set(Vector2D(), Vector2D(static_cast<float>(tex.width), static_cast<float>(tex.height)), easeSpd, Easing::EaseOutQuint);
	alpha.Set(Vector2D(255.0f, 0.0f), Vector2D(), easeSpd, Easing::EaseOutQuint);

	pos.Set(MapChip::getPlyPos(), Vector2D());

	for (int i = 0; i < 4; i++)
	{
		ButtonPos[i].Set({ 40.0f + 40.0f * i, 680.0f }, { 32.0f,32.0f });
	}
	
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
	for (int i = 0; i < 4; i++){
		ButtonPos[i].worldMatrix.Translate(ButtonPos[i].worldPos);
	}

	if (!flgSkipSecond) {
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
	}

	if (!staging && count == goal->getMaxButtonNum() || flgSkipSecond) {
		pos.setSize(start.Update());
	}

	if (!flgSkip) {
		if (KeyInput::Released(DIK_SPACE)) {
			flgSkip = true;
		}
	}
	else {
		if (KeyInput::Released(DIK_SPACE)) {
			flgSkipSecond = true;
			camera->worldPos = MapChip::getPlyPos();
		}
	}

	if(!start){
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

	if (!start) {
		camera->DrawQuad(pos, tex, 0, MyMath::GetRGB(255, 255, 255, static_cast<unsigned int>(alpha.Update().x)));
		for (int i = 0; i < 4; i++){
			camera->DrawUI(ButtonPos[i], ButtonTex, 0, MyMath::GetRGB(255, 255, 255, 255));
		}

	}
	else {
		camera->DrawQuad(pos, tex, 0, MyMath::GetRGB(255, 255, 255, 255));
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

	flgSkip = false;
	flgSkipSecond = false;

	start.Set(Vector2D(), Vector2D(static_cast<float>(tex.width), static_cast<float>(tex.height)), easeSpd, Easing::EaseOutQuint);
	alpha.Set(Vector2D(255.0f, 0.0f), Vector2D(), easeSpd, Easing::EaseOutQuint);

	pos.Set(MapChip::getPlyPos(), Vector2D());
}
#include"GoalUI.h"
#include"Goal/Goal.h"
#include<Novice.h>
#include "Game/MyMath/MyMath.h"

GoalUI::GoalUI(Camera* camera, Goal* goal)
	:Object(camera),
	width(1280.0f),
	height(720.0f),
	color(0x00ff00ff),
	positionGoal(goal)
{
	pos.Set({ 0.0f,0.0f }, {64.0f,64.0f});
	tex.Set("./Resources/GoalUIType1.png", 64, 64, 64);
}

GoalUI::~GoalUI() {
}

void GoalUI::Update() {

	//ゴールの位置とUIの位置を合わせる
	pos.worldPos = positionGoal->getPos();
	//画面の外に出ないようにする処理

	if (pos.worldPos.x < pos.getSize().x / 2.0f) {
		pos.worldPos.x = pos.getSize().x / 2.0f;
	}
	else if (pos.worldPos.x > camera->getDrawSize().x - pos.getSize().x / 2.0f) {
		pos.worldPos.x = camera->getDrawSize().x - pos.getSize().x / 2.0f;
	}
	if (pos.worldPos.y > camera->getDrawSize().y - pos.getSize().y / 2.0f) {
		pos.worldPos.y = camera->getDrawSize().y - pos.getSize().y / 2.0f;
	}
	else if (pos.worldPos.y < pos.getSize().y / 2.0f) {
		pos.worldPos.y = pos.getSize().y / 2.0f;
	}

	pos.worldMatrix.Translate(pos.worldPos);
}

void GoalUI::Draw() {
	//画面の中にゴールがあるかを判別
	////存在する場合ゴールを表示し、ない場合UIを表示する
	if (positionGoal->getPos().x > 0 && positionGoal->getPos().x < width - pos.getSize().x / 2.0f) {
		if (positionGoal->getPos().y > 0 && positionGoal->getPos().y < height - pos.getSize().y / 2.0f) {
			//こっちがゴールを表示
			//camera->DrawUI(drawPos, tex, 0, 0, color);
		}
		else {
			//こっちがUIを表示
			camera->DrawUI(drawPos, whiteBox, 6, false, color);}
	}
	else {
		camera->DrawUI(drawPos, whiteBox, 0, false, color);
	}
	Novice::ScreenPrintf(0, 20, "GoalPos %0.1f", positionGoal->getPos().x);
	Novice::ScreenPrintf(0, 40, "GoalPos %0.1f", positionGoal->getPos().y);
}

void GoalUI::Reset() {

}
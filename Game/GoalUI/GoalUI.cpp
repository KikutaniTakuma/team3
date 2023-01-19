#include"GoalUI.h"
#include"Goal/Goal.h"
GoalUI::GoalUI(Camera* camera)
	:Object(camera),
	UIsize(20.0f),
	width(1280.0f),
	height(720.0f),
	color(0xffffffff)
{
	positionGoal = new Goal;
}

GoalUI::~GoalUI() {
	delete positionGoal;
}

void GoalUI::Update() {
	//ゴールの位置とUIの位置を合わせる
	positionUI = positionGoal->getPos();
	//画面の外に出ないようにする処理
	
	if (positionUI.x < UIsize) {
		positionUI.x = UIsize;
	}
	else if (positionUI.x > width-UIsize) {
		positionUI.x = width - UIsize;
	}
	if (positionUI.y > height - UIsize) {
		positionUI.y = height - UIsize;
	}
	else if (positionUI.y < UIsize) {
		positionUI.y = UIsize;
	}
	pos.worldPos = positionUI;
}

void GoalUI::Draw(class Texture& tex) {
	//画面の中にゴールがあるかを判別
	//存在する場合ゴールを表示し、ない場合UIを表示する
	if (positionGoal->getPos().x > 0 && positionGoal->getPos().x < width - UIsize) {
		if (positionGoal->getPos().y > 0 && positionGoal->getPos().y < height - UIsize) {
			//こっちがゴールを表示
			camera->DrawUI(drawPos, tex, 0, 0, color);
		}
		else {
			//こっちがUIを表示
			camera->DrawUI(drawPos, tex, 0, 0, color);		}
	}
	else {
		camera->DrawUI(drawPos, tex, 0, 0, color);
	}
}

void GoalUI::Reset() {

}
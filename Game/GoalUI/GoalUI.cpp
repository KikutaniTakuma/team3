#include"GoalUI.h"

GoalUI::GoalUI(Camera* camera)
	:Object(camera),
	UIsize(20),
	Width(1280),
	height(720),
	color(0xffffffff)
{}

void GoalUI::Update() {
	//ゴールの位置とUIの位置を合わせる
	positionUI = positionGoal;
	//画面の外に出ないようにする処理
	
	if (positionUI.x < UIsize) {
		positionUI.x = UIsize;
	}
	else if (positionUI.x > Width-UIsize) {
		positionUI.x = Width - UIsize;
	}
	if (positionUI.y > height - UIsize) {
		positionUI.y = UIsize;
	}
	else if (positionUI.y < UIsize) {
		positionUI.y = UIsize;
	}
}

void GoalUI::Draw(class Texture& tex) {
	//画面の中にゴールがあるかを判別
	//存在する場合ゴールを表示し、ない場合UIを表示する
	if (positionGoal.x > 0 && positionGoal.x < Width - UIsize) {
		if (positionGoal.y > 0 && positionGoal.y < height - UIsize) {
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
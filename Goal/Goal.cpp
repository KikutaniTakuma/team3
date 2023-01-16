#include "Goal/Goal.h"
#include <Novice.h>

Goal::Goal() : kMaxButton(4) {
	button = new Button[kMaxButton];
	goalAdvent = false;
	count = 0;
}

Goal::~Goal() {
	delete[] button;
}

/*	メモぽにゃ

	ボタンが押されたらそのボタンをtrueにする
	trueになっているボタンの数（num）を記録し、num = 4でゴールをtrueにする
	ゴールがtrueになったら、マップ数字（ゴール = 2）を壁から空気へ、
	ゴール座標をpos.x = 0としたとき、x座標が0以下ならクリアフラグをtrueにし、シーンを切り替える

*/

void Goal::StateUpdate() {
	count = 0;
	//	状態を確認
	for (int num = 0; num < kMaxButton; num++)
	{
		if (button[num].getPushButton())
		{
			count++;
		}
	}
	//	4つのボタンが押されていたならゴールを開く
	if (count == kMaxButton)
	{
		goalAdvent = true;
	}
}

void Goal::Update() {
	//	ゴールが開いたら
	if (goalAdvent)
	{
		/*ゴール座標をpos.x = 0としたとき、x座標が0以下ならクリアフラグをtrueにし、シーンを切り替える*/
	}
	//	それ以外
	else
	{
		StateUpdate();
	}
}

void Goal::Draw() {
	Novice::ScreenPrintf(50, 100, "good");
}
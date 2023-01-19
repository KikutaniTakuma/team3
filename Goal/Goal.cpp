#include "Goal/Goal.h"
#include <Novice.h>
#include "Game/MapChip/MapChip.h"

Goal::Goal() : kMaxButton(4) {
	button = new Button[kMaxButton];
	goalAdvent = false;
	count = 0;
	ram = { 0.0f,0.0f };

	pos = { 0.0f,0.0f };
	size = { (float)MapChip::kMapSize,(float)MapChip::kMapSize };
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

void Goal::setBottonPos() {
	for (int i = 0; i < kMaxButton; i++)
	{		
		do {
			//	乱数で生成して当てはめる
			ram = { static_cast<float>(MyMath::Random(0,(MapChip::kMapWidth / 2)) * MapChip::kMapSize),
				static_cast<float>(MyMath::Random(0,100) * MapChip::kMapSize) };

		} while (MapChip::GetType(ram) != static_cast<int>(MapChip::Type::NONE));

		button[i].setPos(ram);
	}
}

Vector2D Goal::getPos() {
	return this->pos;
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

	for (int i = 0; i < kMaxButton; i++)
	{
	//	Vector2D ram = { MyMath::Random(0,100),MyMath::Random(0,100) };
	//	button[i].setPos(ram); 
		Novice::ScreenPrintf(50, 100 + (i * 20), "%f",button[i].getPos().x);
		Novice::ScreenPrintf(50, 200 + (i * 20), "%f",button[i].getPos().y);
	}

}

void Goal::Draw() {

}
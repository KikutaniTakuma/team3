#include "Goal/Goal.h"
#include <Novice.h>
#include "Game/MapChip/MapChip.h"
#include "Game/Texture/Texture.h"

Goal::Goal(Camera* camera) :Object(camera), kMaxButton(4) {
	for (auto& i:button)
	{
		i = new Button(camera);
	}
	goalAdvent = false;
	count = 0;
	rnd = { 0.0f,0.0f };
	

	pos.Set({ 1800.0f,4800.0f }, { (float)MapChip::kMapSize,(float)MapChip::kMapSize });
}

Goal::~Goal() {
	for (auto& i : button)
	{
		delete i;
	}
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
		if (button[num]->getPushButton())
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
			
			switch (i)
			{
			case 0:	//	左上
				rnd = { static_cast<float>((MyMath::Random(0, 100) * MapChip::kMapSize) + (MapChip::kMapSize / 2)),
					static_cast<float>((MyMath::Random(0, 100) * MapChip::kMapSize) + (MapChip::kMapSize / 2)) };
				break;
			case 1:	//	右上
				rnd = { static_cast<float>((MyMath::Random(101, MapChip::kMapWidth) * MapChip::kMapSize) + (MapChip::kMapSize / 2)),
					static_cast<float>((MyMath::Random(0, 100) * MapChip::kMapSize) + (MapChip::kMapSize / 2)) };
				break;
			case 2:	//	左下
				rnd = { static_cast<float>((MyMath::Random(0, 100) * MapChip::kMapSize) + (MapChip::kMapSize / 2)),
					static_cast<float>((MyMath::Random(101, MapChip::kMapHeight) * MapChip::kMapSize) + (MapChip::kMapSize / 2)) };
				break;
			case 3:	//	右下
				rnd = { static_cast<float>((MyMath::Random(101, MapChip::kMapWidth) * MapChip::kMapSize) + (MapChip::kMapSize / 2)),
					static_cast<float>((MyMath::Random(101, MapChip::kMapHeight) * MapChip::kMapSize) + (MapChip::kMapSize / 2)) };
				break;
			}

		} while (MapChip::GetType(rnd) != static_cast<int>(MapChip::Type::NONE));

		button[i]->setPos(rnd);
	}
}

Vector2D Goal::getPos() {
	return pos.worldPos;
}

void Goal::setGoalPos(Vector2D pos) {
	this->pos.worldPos = pos;
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

//	for (int i = 0; i < kMaxButton; i++)
//	{
//	//	Vector2D rnd = { MyMath::Random(0,100),MyMath::Random(0,100) };
//	//	button[i].setPos(rnd); 
//		/*Novice::ScreenPrintf(50, 100 + (i * 20), "%f",button[i]->getPos().x);
//		Novice::ScreenPrintf(50, 200 + (i * 20), "%f",button[i]->getPos().y);*/
//	}

	pos.worldMatrix.Translate(pos.worldPos);
}

void Goal::Reset() {

}

void Goal::Draw() {

}
#include "Goal/Goal.h"
#include <Novice.h>
#include "Game/MapChip/MapChip.h"
#include "Game/Texture/Texture.h"
#include "Game/Player/Player.h"


Goal::Goal(Camera* camera,Player* player) :Object(camera), kMaxButton(4) {
	for (auto& i:button)
	{
		i = new Button(camera);
	}
	goalAdvent = true;
	count = 0;
	rnd = { 0.0f,0.0f };
	gameClear = false;

	this->player = player;

	pos.Set(MapChip::getGoalPos(), { (float)MapChip::kMapSize,(float)MapChip::kMapSize });
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
	ゴール座標とプレイヤーの衝突判定をとり、trueになればシーン切り替え

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

bool Goal::getGameClear() {
	return gameClear;
}

void Goal::Update() {
	//	ゴールが開いたら
	if (goalAdvent)
	{
		/*ゴール座標をpos.x = 0としたとき、x座標が0以下ならクリアフラグをtrueにし、シーンを切り替える*/
		//	プレイヤーとの衝突判定
		if (pos.Collision(player->getQuad()))
		{
			//	クリアフラグを立てる
		//	gameClear = true;
			scene = Situation::GAME_CLEAR;
		}

		Novice::ScreenPrintf(0, 200, "%f : %f", pos.worldPos.x, pos.worldPos.y);
	}
	//	それ以外
	else
	{
		StateUpdate();
	}
	
//	//	ボタンとプレイヤーの衝突判定
//	for (auto& i : button)
//	{
//		i->Collision(player->getQuad());
//	}

	pos.worldMatrix.Translate(pos.worldPos);
}

void Goal::Reset() {

}

void Goal::Draw() {
	
}
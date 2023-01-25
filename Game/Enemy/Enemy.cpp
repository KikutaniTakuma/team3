#include "Game/Enemy/Enemy.h"
#include "Game/Camera/Camera.h"
#include "Game/IOcsv/IOcsv.h"
#include "Game/KeyInput/KeyInput.h"
#include "Game/MapChip/MapChip.h"
#include "Game/Player/Player.h"
#include "Game/MyMath/MyMath.h"
#include <cmath>

const int Enemy::kMaxEmyNum = 4;

Enemy::Enemy(Camera* cameraPointa, Player* player)
	:Object(cameraPointa),
	player(player),
	spd(4.0f),
	nmlSpd(spd),
	lowSpd(0.0f),
	shakeScale(Vector2D(10.0f,10.0f)),
	stopFlg(false),
	lowTime(6),
	rndLen(400.0f)
{
	std::vector<float> data;
	if(IOcsv::Input("./Data/EnemyData.csv", data))
	{
		pos.Set(MapChip::getEmyPos(), {32.0f, 32.0f});
	}
	else {
		pos.Set({ data[0], data[1] }, { data[2], data[3] });
	}

	tentativPos = pos.worldPos;

	frm.Restart();
}

void Enemy::Update() {
	if (player) {
		moveVec = { 0.0f };
		tentativPos = pos.worldPos;

		if (stopFlg) {
			spd = lowSpd;
		}
		if (spd == lowSpd) {
			frm.Start(camera->getDelta());
		}
		if(frm.frame > lowTime){
			stopFlg = false;
			spd = nmlSpd;
			frm.Stop();
			frm.Restart();
		}

		// ランダム範囲内にいないときはプレイヤーに向かう
		if (!camera->isDraw(pos.worldPos, rndLen + camera->drawLength) && camera->isDraw(pos.worldPos, rndLen)) {
			int rnd = MyMath::Random(1, 4);

			if (rnd == 1) {
				moveVec.y -= spd;
			}
			else if (rnd == 2) {
				moveVec.y += spd;
			}
			else if (rnd == 3) {
				moveVec.x -= spd;
			}
			else if (rnd == 4) {
				moveVec.x += spd;
			}

			tentativPos += moveVec * camera->getDelta();
		}

		else {
			/// プレイヤーの位置を見て徐々に近づいて行く
			/// 速度は一定
			/// 斜め走行はなし
			/// 縦と横で長いほうを移動する(縦<横の場合横方向に動く)
			/*if (abs(player->getWorldPosX() - pos.worldPos.x) < abs(player->getWorldPosY() - pos.worldPos.y)) {
				if (player->getWorldPosY() < pos.worldPos.y) {
					moveVec.y -= spd;
				}
				else {
					moveVec.y += spd;
				}
			}
			else {
				if (player->getWorldPosX() < pos.worldPos.x) {
					moveVec.x -= spd;
				}
				else {
					moveVec.x += spd;
				}
			}
			tentativPos += moveVec * camera->getDelta();*/

			// 上の逆バージョン
			if (abs(player->getWorldPosX() - pos.worldPos.x) > abs(player->getWorldPosY() - pos.worldPos.y)) {
				if (MapChip::GetNum(pos.worldPos).y == MapChip::GetNum(player->getWorldPos()).y) {
					if (player->getWorldPosX() < pos.worldPos.x) {
						moveVec.x -= spd;
					}
					else {
						moveVec.x += spd;
					}
				}
				else if (player->getWorldPosY() < pos.worldPos.y) {
					moveVec.y -= spd;
				}
				else if (player->getWorldPosY() >= pos.worldPos.y) {
					moveVec.y += spd;
				}
			}
			else {
				if (MapChip::GetNum(pos.worldPos).x == MapChip::GetNum(player->getWorldPos()).x) {
					if (player->getWorldPosY() < pos.worldPos.y) {
						moveVec.y -= spd;
					}
					else if (player->getWorldPosY() >= pos.worldPos.y) {
						moveVec.y += spd;
					}
				}
				else if (player->getWorldPosX() < pos.worldPos.x) {
					moveVec.x -= spd;
				}
				else if(player->getWorldPosX() >= pos.worldPos.x){
					moveVec.x += spd;
				}
			}
			tentativPos += moveVec * camera->getDelta();

		}

	}
	// 移動したところがブロックだったら
	// 移動ベクトルとは逆方向に移動(後で実装)
	// 衝突
	// 衝突したらブロックは空白にする

	if (MapChip::GetType(pos.getSizeLeftTop() + tentativPos) == 1 ||
		MapChip::GetType({ pos.getSizeLeftUnder().x + tentativPos.x, pos.getSizeLeftUnder().y + tentativPos.y + 1.0f }) == 1 ||
		MapChip::GetType(pos.getSizeRightTop() + tentativPos) == 1||
		MapChip::GetType({ pos.getSizeRightUnder().x + tentativPos.x,pos.getSizeRightUnder().y + tentativPos.y + 1.0f }) == 1) {

		Vector2D mapNum = MapChip::GetNum(pos.getSizeLeftTop() + tentativPos);
		MapChip::setData(static_cast<int>(MapChip::Type::NONE), static_cast<int>(mapNum.x), static_cast<int>(mapNum.y));

		mapNum = MapChip::GetNum(pos.getSizeLeftUnder() + tentativPos);
		MapChip::setData(static_cast<int>(MapChip::Type::NONE), static_cast<int>(mapNum.x), static_cast<int>(mapNum.y));

		mapNum = MapChip::GetNum(pos.getSizeRightTop() + tentativPos);
		MapChip::setData(static_cast<int>(MapChip::Type::NONE), static_cast<int>(mapNum.x), static_cast<int>(mapNum.y));

		mapNum = MapChip::GetNum(pos.getSizeRightUnder() + tentativPos);
		MapChip::setData(static_cast<int>(MapChip::Type::NONE), static_cast<int>(mapNum.x), static_cast<int>(mapNum.y));

		stopFlg = true;
		if (camera->isDraw(pos.worldPos)) {
			camera->shakeFlg = true;
		}
	}
	else {
		if (camera->isDraw(pos.worldPos)) {
			camera->shakeFlg = false;
		}
	}

	if (camera->shakeFlg) {
		camera->shakeScale = shakeScale;
	}

	pos.worldPos = tentativPos;

	pos.Translate();
}

void Enemy::Draw() {
	camera->DrawQuad(drawPos, whiteBox, 0, false, MyMath::GetRGB(255,0,0,255));
}

void Enemy::Reset() {
	std::vector<float> data;
	if (IOcsv::Input("./Data/EnemyData.csv", data))
	{
		pos.Set({ 640.0f, 360.0f }, { 32.0f, 32.0f });
	}
	else {
		pos.Set({ data[0], data[1] }, { data[2], data[3] });
	}
}

void Enemy::Collision() {
	Vector2D LeftTop = { pos.getSizeLeftTop().x + tentativPos.x, pos.getSizeLeftTop().y + tentativPos.y };

	Vector2D RightTop = { pos.getSizeRightTop().x + tentativPos.x - 1.0f, pos.getSizeRightTop().y + tentativPos.y };

	Vector2D LeftUnder = { pos.getSizeLeftUnder().x + tentativPos.x , pos.getSizeLeftUnder().y + tentativPos.y + 1.0f };

	Vector2D RightUnder = { pos.getSizeRightUnder().x + tentativPos.x - 1.0f, pos.getSizeRightUnder().y + tentativPos.y + 1.0f };

	// もし上に向かっていたら
	if (moveVec.y > 0.0f) {
		// もし右移動していたら
		if (moveVec.x > 0.0f) {
			// 右上にのみブロックがある
			if (MapChip::Collision(RightTop) && !MapChip::Collision(LeftTop) && !MapChip::Collision(RightUnder)) {
				Vector2D mapPos = MapChip::GetPos(RightTop);

				if (RightTop.x - mapPos.x < RightTop.y - mapPos.y) {
					mapPos.x -= MapChip::kMapSize;

					tentativPos.x = mapPos.x + pos.getSize().x / 2.0f;
				}
				else if (RightTop.x - mapPos.x > RightTop.y - mapPos.y) {
					mapPos.y -= MapChip::kMapSize;

					tentativPos.y = mapPos.y + pos.getSize().y / 2.0f;

					moveVec.y = 0.0f;
				}
				else if (RightTop.x - mapPos.x == RightTop.y - mapPos.y) {
					mapPos.y -= MapChip::kMapSize;
					tentativPos.y = mapPos.y + pos.getSize().y / 2.0f;

					moveVec.y = 0.0f;
				}
			}
			// 左上にのみブロックがある
			else if (!MapChip::Collision(RightTop) && MapChip::Collision(LeftTop) && !MapChip::Collision(RightUnder)) {
				Vector2D mapPos = MapChip::GetPos(LeftTop);
				mapPos.y -= MapChip::kMapSize;

				tentativPos.y = mapPos.y + pos.getSize().y / 2.0f;

				moveVec.y = 0.0f;
			}
			// 右下にのみブロックがある
			else if (!MapChip::Collision(RightTop) && !MapChip::Collision(LeftTop) && MapChip::Collision(RightUnder)) {
				Vector2D mapPos = MapChip::GetPos(RightUnder);
				mapPos.x -= MapChip::kMapSize;

				tentativPos.x = mapPos.x + pos.getSize().x / 2.0f;
			}

			// 上にブロックがある
			else if (MapChip::Collision(RightTop) && MapChip::Collision(LeftTop) && !MapChip::Collision(RightUnder)) {
				Vector2D mapPos = MapChip::GetPos(RightTop);
				mapPos.y -= MapChip::kMapSize;

				tentativPos.y = mapPos.y + pos.getSize().y / 2.0f;

				moveVec.y = 0.0f;
			}
			// 右側にブロックがある
			else if (MapChip::Collision(RightTop) && !MapChip::Collision(LeftTop) && MapChip::Collision(RightUnder)) {
				Vector2D mapPos = MapChip::GetPos(RightTop);
				mapPos.x -= MapChip::kMapSize;

				tentativPos.x = mapPos.x + pos.getSize().x / 2.0f;
			}
			// 右上に進めない
			else if (MapChip::Collision(RightTop) && MapChip::Collision(LeftTop) && MapChip::Collision(RightUnder)) {
				Vector2D mapPos = MapChip::GetPos(RightTop);
				mapPos.y -= MapChip::kMapSize;

				tentativPos.y = mapPos.y + pos.getSize().y / 2.0f;

				mapPos = MapChip::GetPos(RightTop);
				mapPos.x -= MapChip::kMapSize;

				tentativPos.x = mapPos.x + pos.getSize().x / 2.0f;

				moveVec.y = 0.0f;
			}
		}

		// もし左移動していたら
		else if ((moveVec.x < 0.0f)) {
			// 左上にのみブロックがある
			if (MapChip::Collision(LeftTop) && !MapChip::Collision(RightTop) && !MapChip::Collision(LeftUnder)) {
				Vector2D mapPos = MapChip::GetPos(LeftTop);

				if ((mapPos.x + MapChip::kMapSize) - LeftTop.x < LeftTop.y - mapPos.y) {
					mapPos.x += MapChip::kMapSize;

					tentativPos.x = mapPos.x + pos.getSize().x / 2.0f;
				}
				else if ((mapPos.x + MapChip::kMapSize) - LeftTop.x > LeftTop.y - mapPos.y) {
					mapPos.y -= MapChip::kMapSize;
					tentativPos.y = mapPos.y + pos.getSize().y / 2.0f;

					moveVec.y = 0.0f;
				}
				else if ((mapPos.x + MapChip::kMapSize) - LeftTop.x == LeftTop.y - mapPos.y) {
					mapPos.y -= MapChip::kMapSize;
					tentativPos.y = mapPos.y + pos.getSize().y / 2.0f;

					moveVec.y = 0.0f;
				}
			}
			// 右上にのみブロックがある
			else if (!MapChip::Collision(LeftTop) && MapChip::Collision(RightTop) && !MapChip::Collision(LeftUnder)) {
				Vector2D mapPos = MapChip::GetPos(LeftTop);
				mapPos.y -= MapChip::kMapSize;

				tentativPos.y = mapPos.y + pos.getSize().y / 2.0f;

				moveVec.y = 0.0f;
			}
			// 左下にのみブロックがある
			else if (!MapChip::Collision(LeftTop) && !MapChip::Collision(RightTop) && MapChip::Collision(LeftUnder)) {
				Vector2D mapPos = MapChip::GetPos(LeftTop);
				mapPos.x += MapChip::kMapSize;

				tentativPos.x = mapPos.x + pos.getSize().x / 2.0f;
			}

			// 上にブロックがある
			else if (MapChip::Collision(LeftTop) && MapChip::Collision(RightTop) && !MapChip::Collision(LeftUnder)) {
				Vector2D mapPos = MapChip::GetPos(LeftTop);
				mapPos.y -= MapChip::kMapSize;

				tentativPos.y = mapPos.y + pos.getSize().y / 2.0f;

				moveVec.y = 0.0f;
			}
			// 左側にブロックがある
			else if (MapChip::Collision(LeftTop) && !MapChip::Collision(RightTop) && MapChip::Collision(LeftUnder)) {
				Vector2D mapPos = MapChip::GetPos(LeftTop);
				mapPos.x += MapChip::kMapSize;

				tentativPos.x = mapPos.x + pos.getSize().x / 2.0f;
			}
			// 左上に進めない
			else if (MapChip::Collision(LeftTop) && MapChip::Collision(RightTop) && MapChip::Collision(LeftUnder)) {
				Vector2D mapPos = MapChip::GetPos(LeftTop);
				mapPos.y -= MapChip::kMapSize;

				tentativPos.y = mapPos.y + pos.getSize().y / 2.0f;

				mapPos = MapChip::GetPos(LeftTop);
				mapPos.x += MapChip::kMapSize;

				tentativPos.x = mapPos.x + pos.getSize().x / 2.0f;

				moveVec.y = 0.0f;
			}
		}

		else if (MapChip::Collision(LeftTop) || MapChip::Collision(RightTop)) {
			Vector2D mapPos = MapChip::GetPos(LeftTop);
			mapPos.y -= MapChip::kMapSize;

			tentativPos.y = mapPos.y + pos.getSize().y / 2.0f;

			moveVec.y = 0.0f;
		}
	}

	// もし下移動していたら
	else if (moveVec.y < 0.0f) {
		// 右移動
		if (moveVec.x > 0.0f) {
			// 右下にのみブロックがある
			if (!MapChip::Collision(LeftUnder) && MapChip::Collision(RightUnder) && !MapChip::Collision(RightTop)) {
				Vector2D mapPos = MapChip::GetPos(RightUnder);

				if (static_cast<int>(mapPos.y) % MapChip::kMapSize == 0) {
					RightUnder.y -= 1.0f;
				}
				mapPos = MapChip::GetPos(RightUnder);

				if (RightUnder.x - mapPos.x < (mapPos.y + MapChip::kMapSize) - RightUnder.y) {
					mapPos.x -= MapChip::kMapSize;
					tentativPos.x = mapPos.x + pos.getSize().x / 2.0f;
				}
				else if (RightUnder.x - mapPos.x > (mapPos.y + MapChip::kMapSize) - RightUnder.y) {
					mapPos.y += MapChip::kMapSize;

					tentativPos.y = mapPos.y + pos.getSize().y / 2.0f;

					moveVec.y = 0.0f;
				}
				else if (RightUnder.x - mapPos.x == (mapPos.y + MapChip::kMapSize) - RightUnder.y) {
					mapPos.y += MapChip::kMapSize;

					tentativPos.y = mapPos.y + pos.getSize().y / 2.0f;

					moveVec.y = 0.0f;
				}
			}
			// 左下にのみブロックがある
			else if (MapChip::Collision(LeftUnder) && !MapChip::Collision(RightUnder) && !MapChip::Collision(RightTop)) {
				Vector2D mapPos = MapChip::GetPos(LeftUnder);
				if (static_cast<int>(mapPos.y) % MapChip::kMapSize == 0) {
					LeftUnder.y -= 1.0f;
				}
				mapPos = MapChip::GetPos(LeftUnder);
				mapPos.y += MapChip::kMapSize;

				tentativPos.y = mapPos.y + pos.getSize().y / 2.0f;

				moveVec.y = 0.0f;
			}
			// 右上のみにブロックがある
			else if (!MapChip::Collision(LeftUnder) && !MapChip::Collision(RightUnder) && MapChip::Collision(RightTop)) {
				Vector2D mapPos = MapChip::GetPos(RightTop);

				mapPos.x -= MapChip::kMapSize;
				tentativPos.x = mapPos.x + pos.getSize().x / 2.0f;
			}

			// 下にブロックがある
			else if (MapChip::Collision(LeftUnder) && MapChip::Collision(RightUnder) && !MapChip::Collision(RightTop)) {
				Vector2D mapPos = MapChip::GetPos(RightUnder);
				if (static_cast<int>(mapPos.y) % MapChip::kMapSize == 0) {
					LeftUnder.y -= 1.0f;
				}
				mapPos = MapChip::GetPos(LeftUnder);
				mapPos.y += MapChip::kMapSize;

				tentativPos.y = mapPos.y + pos.getSize().y / 2.0f;

				moveVec.y = 0.0f;
			}
			// 右にブロックがある
			else if (!MapChip::Collision(LeftUnder) && MapChip::Collision(RightUnder) && MapChip::Collision(RightTop)) {
				Vector2D mapPos = MapChip::GetPos(RightTop);

				mapPos.x -= MapChip::kMapSize;
				tentativPos.x = mapPos.x + pos.getSize().x / 2.0f;
			}
			// 右下に進めない
			else if (MapChip::Collision(LeftUnder) && MapChip::Collision(RightUnder) && MapChip::Collision(RightTop)) {
				Vector2D mapPos = MapChip::GetPos(RightUnder);
				if (static_cast<int>(mapPos.y) % MapChip::kMapSize == 0) {
					RightUnder.y -= 1.0f;
				}
				mapPos = MapChip::GetPos(RightUnder);

				mapPos.y += MapChip::kMapSize;

				tentativPos.y = mapPos.y + pos.getSize().y / 2.0f;

				mapPos.x -= MapChip::kMapSize;
				tentativPos.x = mapPos.x + pos.getSize().x / 2.0f;

				moveVec.y = 0.0f;
			}
		}
		// 左移動してたら
		else if (moveVec.x < 0.0f) {
			// 左下にしかブロックがない
			if (MapChip::Collision(LeftUnder) && !MapChip::Collision(RightUnder) && !MapChip::Collision(LeftTop)) {
				Vector2D mapPos = MapChip::GetPos(LeftUnder);

				if (static_cast<int>(mapPos.y) % MapChip::kMapSize == 0) {
					LeftUnder.y -= 1.0f;
				}
				mapPos = MapChip::GetPos(LeftUnder);

				if ((mapPos.x + MapChip::kMapSize) - LeftUnder.x < (mapPos.y + MapChip::kMapSize) - LeftUnder.y) {
					mapPos.x += MapChip::kMapSize;

					tentativPos.x = mapPos.x + pos.getSize().x / 2.0f;
				}
				else if ((mapPos.x + MapChip::kMapSize) - LeftUnder.x > (mapPos.y + MapChip::kMapSize) - LeftUnder.y) {
					mapPos.y += MapChip::kMapSize;

					tentativPos.y = mapPos.y + pos.getSize().y / 2.0f;

					moveVec.y = 0.0f;
				}
				else if ((mapPos.x + MapChip::kMapSize) - LeftUnder.x == (mapPos.y + MapChip::kMapSize) - LeftUnder.y) {
					mapPos.y += MapChip::kMapSize;

					tentativPos.y = mapPos.y + pos.getSize().y / 2.0f;

					moveVec.y = 0.0f;
				}
			}
			// 右下にのみブロックがある
			else if (!MapChip::Collision(LeftUnder) && MapChip::Collision(RightUnder) && !MapChip::Collision(LeftTop)) {
				Vector2D mapPos = MapChip::GetPos(RightUnder);
				if (static_cast<int>(mapPos.y) % MapChip::kMapSize == 0) {
					RightUnder.y -= 1.0f;
				}
				mapPos = MapChip::GetPos(RightUnder);

				mapPos.y += MapChip::kMapSize;

				tentativPos.y = mapPos.y + pos.getSize().y / 2.0f;

				moveVec.y = 0.0f;
			}
			// 左上にのみブロックがある
			else if (!MapChip::Collision(LeftUnder) && !MapChip::Collision(RightUnder) && MapChip::Collision(LeftTop)) {
				Vector2D mapPos = MapChip::GetPos(LeftTop);
				mapPos.x += MapChip::kMapSize;

				tentativPos.x = mapPos.x + pos.getSize().x / 2.0f;
			}

			// 下にブロックがある
			else if (MapChip::Collision(LeftUnder) && MapChip::Collision(RightUnder) && !MapChip::Collision(LeftTop)) {
				Vector2D mapPos = MapChip::GetPos(LeftUnder);
				if (static_cast<int>(mapPos.y) % MapChip::kMapSize == 0) {
					LeftUnder.y -= 1.0f;
				}
				mapPos = MapChip::GetPos(LeftUnder);

				mapPos.y += MapChip::kMapSize;

				tentativPos.y = mapPos.y + pos.getSize().y / 2.0f;

				moveVec.y = 0.0f;
			}
			// 左にブロックがある
			else if (MapChip::Collision(LeftUnder) && !MapChip::Collision(RightUnder) && MapChip::Collision(LeftTop)) {
				Vector2D mapPos = MapChip::GetPos(LeftTop);
				mapPos.x += MapChip::kMapSize;

				tentativPos.x = mapPos.x + pos.getSize().x / 2.0f;
			}
			// 左下に進めない
			else if (MapChip::Collision(LeftUnder) && MapChip::Collision(RightUnder) && MapChip::Collision(LeftTop)) {
				Vector2D mapPos = MapChip::GetPos(LeftUnder);
				if (static_cast<int>(mapPos.y) % MapChip::kMapSize == 0) {
					LeftUnder.y -= 1.0f;
				}
				mapPos = MapChip::GetPos(LeftUnder);

				mapPos.y += MapChip::kMapSize;

				tentativPos.y = mapPos.y + pos.getSize().y / 2.0f;

				mapPos = MapChip::GetPos(LeftTop);
				mapPos.x += MapChip::kMapSize;

				tentativPos.x = mapPos.x + pos.getSize().x / 2.0f;

				moveVec.y = 0.0f;
			}
		}

		else if (MapChip::Collision(LeftUnder) || MapChip::Collision(RightUnder)) {
			Vector2D mapPos = MapChip::GetPos(LeftUnder);
			if (static_cast<int>(mapPos.y) % MapChip::kMapSize == 0) {
				LeftUnder.y -= 1.0f;
			}
			mapPos = MapChip::GetPos(LeftUnder);

			mapPos.y += MapChip::kMapSize;
			tentativPos.y = mapPos.y + pos.getSize().y / 2.0f;

			moveVec.y = 0.0f;
		}
	}
	else if (moveVec.x > 0.0f) {
		if (MapChip::Collision(RightTop) || MapChip::Collision(RightUnder)) {
			Vector2D mapPos = MapChip::GetPos(RightTop);
			mapPos.x -= MapChip::kMapSize;

			tentativPos.x = mapPos.x + pos.getSize().x / 2.0f;
		}
	}
	else if (moveVec.x < 0.0f) {
		if (MapChip::Collision(LeftTop) || MapChip::Collision(LeftUnder)) {
			Vector2D mapPos = MapChip::GetPos(LeftTop);
			mapPos.x += MapChip::kMapSize;

			tentativPos.x = mapPos.x + pos.getSize().x / 2.0f;
		}
	}
	else {
		if (MapChip::Collision(LeftTop) || MapChip::Collision(RightTop)) {
			Vector2D mapPos = MapChip::GetPos(LeftTop);
			mapPos.y -= MapChip::kMapSize;

			tentativPos.y = mapPos.y + pos.getSize().y / 2.0f;
		}
		if (MapChip::Collision(LeftUnder) || MapChip::Collision(RightUnder)) {
			Vector2D mapPos = MapChip::GetPos(LeftUnder);
			mapPos.y += MapChip::kMapSize;
			tentativPos.y = mapPos.y + pos.getSize().y / 2.0f;
		}
		if (MapChip::Collision(RightTop) || MapChip::Collision(RightUnder)) {
			Vector2D mapPos = MapChip::GetPos(RightTop);
			mapPos.x -= MapChip::kMapSize;

			tentativPos.x = mapPos.x + pos.getSize().x / 2.0f;
		}
		if (MapChip::Collision(LeftTop) || MapChip::Collision(LeftUnder)) {
			Vector2D mapPos = MapChip::GetPos(LeftTop);
			mapPos.x += MapChip::kMapSize;

			tentativPos.x = mapPos.x + pos.getSize().x / 2.0f;
		}
	}

	LeftTop = { pos.getSizeLeftTop().x + tentativPos.x, pos.getSizeLeftTop().y + tentativPos.y };

	RightTop = { pos.getSizeRightTop().x + tentativPos.x - 1.0f, pos.getSizeRightTop().y + tentativPos.y };

	LeftUnder = { pos.getSizeLeftUnder().x + tentativPos.x , pos.getSizeLeftUnder().y + tentativPos.y + 1.0f };

	RightUnder = { pos.getSizeRightUnder().x + tentativPos.x - 1.0f, pos.getSizeRightUnder().y + tentativPos.y + 1.0f };

	if (!MapChip::Collision(RightTop) && !MapChip::Collision(LeftTop) && !MapChip::Collision(RightUnder) && !MapChip::Collision(LeftUnder)) {
		pos.worldPos = tentativPos;
	}
}
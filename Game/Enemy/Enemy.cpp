#include "Game/Enemy/Enemy.h"
#include "Game/Camera/Camera.h"
#include "Game/IOcsv/IOcsv.h"
#include "Game/KeyInput/KeyInput.h"
#include "Game/MapChip/MapChip.h"
#include "Game/Player/Player.h"
#include <cmath>

Enemy::Enemy(Camera* cameraPointa, Player* player)
	:Object(cameraPointa),
	player(player),
	spd(10.0f)
{
	std::vector<float> data;
	if(IOcsv::Input("./Data/EnemyData.csv", data))
	{
		pos.Set({ 640.0f, 360.0f }, { 32.0f, 32.0f });
	}
	else {
		pos.Set({ data[0], data[1] }, { data[2], data[3] });
	}
}

void Enemy::Update() {
	if (player) {
		moveVec = { 0.0f };

		/// プレイヤーの位置を見て徐々に近づいて行く
		/// 速度は一定
		/// 斜め走行はなし
		/// 縦と横で長いほうを移動する(縦<横の場合横方向に動く)
		if (abs(player->getWorldPosX() - pos.worldPos.x) < abs(player->getWorldPosY() - pos.worldPos.y)) {
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
		tentativPos += moveVec;
	}

	this->Collision();

	pos.worldMatrix.Translate(pos.worldPos);
}

int Enemy::Heuristic() {
	int width = abs(static_cast<int>(MapChip::GetNum(pos.worldPos).x - MapChip::GetNum(player->getWorldPos()).x));
	int height = abs(static_cast<int>(MapChip::GetNum(pos.worldPos).y - MapChip::GetNum(player->getWorldPos()).y));

	return width + height;
}

void Enemy::Astar() {
	int cost = 0;

	// 探索する方向を決める
}

void Enemy::Draw(Texture& tex) {
	camera->DrawQuad(drawPos, tex, 0, false);
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
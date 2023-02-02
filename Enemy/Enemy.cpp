#include "Enemy/Enemy.h"
#include "Game/Camera/Camera.h"
#include "Game/IOcsv/IOcsv.h"
#include "Game/KeyInput/KeyInput.h"
#include "Game/MapChip/MapChip.h"
#include "Game/Player/Player.h"
#include "Game/MyMath/MyMath.h"
#include <cmath>
#include <assert.h>

const int Enemy::kMaxEmyNum = 4;

Enemy::Enemy(Camera* cameraPointa, Player* player)
	:Object(cameraPointa),
	player(player),
	spd(4.0f),
	nmlSpd(spd),
	lowSpd(0.0f),
	shakeScale(Vector2D(10.0f, 10.0f)),
	stopFlg(false),
	lowTime(12),
	rndLen(100.0f),
	blockBrk(Sound("./Resources/BlockBreak.wav", false)),
	blockBrkFlg(false),
	front(Texture("./Resources/Enemy/BraveFront.png",128,32,32)),
	back(Texture("./Resources/Enemy/BraveBack.png", 128, 32, 32)),
	right(Texture("./Resources/Enemy/BraveRight.png", 128, 32, 32)),
	left(Texture("./Resources/Enemy/BraveLeft.png", 128, 32, 32)),
	dir(Direction::FRONT)
{
	// テクスチャーが正常に読み込まれているか
	assert(front);
	assert(back);
	assert(right);
	assert(left);

	pos.Set(MapChip::getEmyPos(), { 32.0f, 32.0f });

	tentativPos = pos.worldPos;

	frm.Restart();
}

void Enemy::Update() {
	assert(player);
	moveVec = { 0.0f };
	tentativPos = pos.worldPos;

	if (stopFlg) {
		spd = lowSpd;
		frm.Start();
	}
	if (frm.getFrame() > lowTime) {
		stopFlg = false;
		spd = nmlSpd;
		frm.Stop();
		frm.Restart();
	}

	// ランダム範囲内にいないときはプレイヤーに向かう
	if (!camera->isDraw(pos.worldPos) && camera->isDraw(pos.worldPos, rndLen)) {
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
			else if (player->getWorldPosX() >= pos.worldPos.x) {
				moveVec.x += spd;
			}
		}
		tentativPos += moveVec * camera->getDelta();

	}

	this->Collision();

	if (moveVec.x > 0.0f) {
		dir = Direction::RIGHT;
		if (moveVec.y > 0.0f && moveVec.y > moveVec.x) {
			dir = Direction::BACK;
		}
		else if (moveVec.y < 0.0f && -moveVec.y > moveVec.x) {
			dir = Direction::FRONT;
		}
	}
	else if (moveVec.x < 0.0f) {
		dir = Direction::LEFT;
		if (moveVec.y > 0.0f && -moveVec.y < moveVec.x) {
			dir = Direction::BACK;
		}
		else if (moveVec.y < 0.0f && moveVec.y < moveVec.x) {
			dir = Direction::FRONT;
		}
	}
	else if (moveVec.y > 0.0f) {
		dir = Direction::BACK;
	}
	else if (moveVec.y < 0.0f) {
		dir = Direction::FRONT;
	}

	pos.worldPos = tentativPos;

	// 移動したところがブロックだったら
	// 移動ベクトルとは逆方向に移動(後で実装)
	// 衝突
	// 衝突したらブロックは空白にする

	if (!stopFlg) {
		if (MapChip::GetType(pos.getPosLeftTop()) == 1 ||
			MapChip::GetType({ pos.getPosLeftUnder().x, pos.getPosLeftUnder().y + 1.0f }) == 1 ||
			MapChip::GetType({ pos.getPosRightTop().x - 1.0f, pos.getPosRightTop().y }) == 1 ||
			MapChip::GetType({ pos.getPosRightUnder().x - 1.0f, pos.getPosRightUnder().y + 1.0f }) == 1) {

			Vector2D mapNum = MapChip::GetNum(pos.getPosLeftTop());
			MapChip::setData(static_cast<int>(MapChip::Type::NONE), static_cast<int>(mapNum.x), static_cast<int>(mapNum.y));

			mapNum = MapChip::GetNum({ pos.getPosLeftUnder().x, pos.getPosLeftUnder().y + 1.0f });
			MapChip::setData(static_cast<int>(MapChip::Type::NONE), static_cast<int>(mapNum.x), static_cast<int>(mapNum.y));

			mapNum = MapChip::GetNum({ pos.getPosRightTop().x - 1.0f, pos.getPosRightTop().y });
			MapChip::setData(static_cast<int>(MapChip::Type::NONE), static_cast<int>(mapNum.x), static_cast<int>(mapNum.y));

			mapNum = MapChip::GetNum({ pos.getPosRightUnder().x - 1.0f, pos.getPosRightUnder().y + 1.0f });
			MapChip::setData(static_cast<int>(MapChip::Type::NONE), static_cast<int>(mapNum.x), static_cast<int>(mapNum.y));

			stopFlg = true;
			if (camera->isDraw(pos.worldPos)) {
				camera->shakeFlg = true;
				blockBrkFlg = true;
			}
		}
	}
	else {
		camera->shakeFlg = false;
		blockBrkFlg = false;
	}

	if (camera->shakeFlg) {
		camera->shakeScale = shakeScale;
		if (!camera->isDraw(pos.worldPos)) {
			camera->shakeFlg = false;
		}
	}

	if (pos.Collision(player->getQuad())) {
		scene = Situation::GAME_OVER;
	}

	pos.Translate();
}

void Enemy::Draw() {
	switch (dir)
	{
	case Enemy::Direction::LEFT:
		camera->DrawQuad(pos, left, 12.0f, MyMath::GetRGB(255, 255, 255, 255));
		break;
	case Enemy::Direction::RIGHT:
		camera->DrawQuad(pos, right, 12.0f, MyMath::GetRGB(255, 255, 255, 255));
		break;
	case Enemy::Direction::FRONT:
		camera->DrawQuad(pos, front, 12.0f, MyMath::GetRGB(255, 255, 255, 255));
		break;
	case Enemy::Direction::BACK:
		camera->DrawQuad(pos, back, 12.0f, MyMath::GetRGB(255, 255, 255, 255));
		break;
	default:
		assert(!"Enemy Direction Exception Error");
		break;
	}

	if (camera->isDraw(pos.worldPos)) {
		if (blockBrkFlg) {
			blockBrk.SoundEffect(0.5f);
		}
	}
}

void Enemy::Reset() {
}

void Enemy::Collision() {
	if (tentativPos.x > MapChip::getMapMaxPosX() - pos.getSize().x / 2.0f) {
		tentativPos.x = MapChip::getMapMaxPosX() - pos.getSize().x / 2.0f;
	}
	if (tentativPos.x < MapChip::getMapMinPosX() + pos.getSize().x / 2.0f) {
		tentativPos.x = MapChip::getMapMinPosX() + pos.getSize().x / 2.0f;
	}
	if (tentativPos.y > MapChip::getMapMaxPosY() - pos.getSize().y / 2.0f) {
		tentativPos.y = MapChip::getMapMaxPosY() - pos.getSize().y / 2.0f;
	}
	if (tentativPos.y < MapChip::getMapMinPosY() + pos.getSize().y / 2.0f) {
		tentativPos.y = MapChip::getMapMinPosY() + pos.getSize().y / 2.0f;
	}
}
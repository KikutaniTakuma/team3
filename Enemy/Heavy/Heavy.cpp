#include "Heavy.hpp"
#include "Game/Player/Player.h"
#include "Game/MyMath/MyMath.h"
#include <assert.h>

Heavy::Heavy(Camera* camera, Player* player):
	Enemy(camera, player),
	rushFlg(false),
	rushSpd(0.012f),
	rushLen(50.0f),
	rushEase(Easing(pos.worldPos, pos.worldPos, rushSpd, Easing::EaseInOutQuint))
{
	this->spd = 2.0f;
	this->lowTime = 45;

	front.Set("./Resources/Enemy/FighterFront.png", 128, 32, 32);
	back.Set("./Resources/Enemy/FighterBack.png", 128, 32, 32);
	right.Set("./Resources/Enemy/FighterRight.png", 128, 32, 32);
	left.Set("./Resources/Enemy/FighterLeft.png", 128, 32, 32);

	// テクスチャーが正常に読み込まれているか
	assert(front);
	assert(back);
	assert(right);
	assert(left);

	dir = Direction::FRONT;

	shakeScale = { 5.0f, 5.0f };
}

void Heavy::Update() {
	assert(player);
	tentativPos = pos.worldPos;
	moveVec = { 0.0f,0.0f };

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
	}
	else if (!camera->isDraw(pos.worldPos, rndLen)) {
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
	}
	else {
		if (!rushFlg && !stopFlg) {
			rushFlg = true;
			rushEase.Set(pos.worldPos, player->getWorldPos() + (player->getWorldPos() - pos.worldPos), rushSpd, Easing::EaseInBack);
		}
	}

	if (rushFlg) {
		moveVec = rushEase.Update() - pos.worldPos;
	}

	if (moveVec.x > static_cast<float>(MapChip::kMapSize)) {
		moveVec.x = static_cast<float>(MapChip::kMapSize);
	}
	if (moveVec.x < -static_cast<float>(MapChip::kMapSize)) {
		moveVec.x = -static_cast<float>(MapChip::kMapSize);
	}
	if (moveVec.y > static_cast<float>(MapChip::kMapSize)) {
		moveVec.y = static_cast<float>(MapChip::kMapSize);
	}
	if (moveVec.y < -static_cast<float>(MapChip::kMapSize)) {
		moveVec.y = -static_cast<float>(MapChip::kMapSize);
	}

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
	
	tentativPos += moveVec * camera->getDelta();
	

	this->Collision();

	if (!rushEase) {
		rushFlg = false;
		stopFlg = true;
	}

	Vector2D leftTop = MapChip::GetNum(pos.getSizeLeftTop() + tentativPos);
	Vector2D leftUnder = MapChip::GetNum({ pos.getSizeLeftUnder().x + tentativPos.x, pos.getSizeLeftUnder().y + tentativPos.y + 1.0f });
	Vector2D rightTop = MapChip::GetNum({ pos.getSizeRightTop().x + tentativPos.x - 1.0f,pos.getSizeRightTop().y + tentativPos.y });
	Vector2D rightUnder = MapChip::GetNum({ pos.getSizeRightUnder().x + tentativPos.x - 1.0f, pos.getSizeRightUnder().y + tentativPos.y + 1.0f });


	if (leftTop != 0.0f &&
		leftUnder != 0.0f &&
		rightTop != 0.0f &&
		rightUnder != 0.0f &&

		leftTop.x != static_cast<float>(MapChip::kMapWidth -1) &&
		leftUnder.x != static_cast<float>(MapChip::kMapWidth - 1) &&
		rightTop.x != static_cast<float>(MapChip::kMapWidth - 1) &&
		rightUnder.x != static_cast<float>(MapChip::kMapWidth - 1) &&

		leftTop.y != static_cast<float>(MapChip::kMapHeight - 1) &&
		leftUnder.y != static_cast<float>(MapChip::kMapHeight - 1) &&
		rightTop.y != static_cast<float>(MapChip::kMapHeight - 1) &&
		rightUnder.y != static_cast<float>(MapChip::kMapHeight - 1))
	{
		pos.worldPos = tentativPos;

	// 移動したところがブロックだったら
	// 衝突
	// 衝突したらブロックは空白にする

		if (camera->isDraw(pos.worldPos, rndLen + camera->drawLength) && camera->isDraw(pos.worldPos, rndLen)) {
			if (MapChip::GetType(pos.getSizeLeftTop() + tentativPos) == 1 ||
				MapChip::GetType({ pos.getSizeLeftUnder().x + tentativPos.x, pos.getSizeLeftUnder().y + tentativPos.y + 1.0f }) == 1 ||
				MapChip::GetType({ pos.getSizeRightTop().x + tentativPos.x - 1.0f, pos.getSizeRightTop().y + tentativPos.y }) == 1 ||
				MapChip::GetType({ pos.getSizeRightUnder().x + tentativPos.x -1.0f, pos.getSizeRightUnder().y + tentativPos.y + 1.0f }) == 1) {

				Vector2D mapNum = MapChip::GetNum(pos.getSizeLeftTop() + tentativPos);
				MapChip::setData(static_cast<int>(MapChip::Type::NONE), static_cast<int>(mapNum.x), static_cast<int>(mapNum.y));

				mapNum = MapChip::GetNum({ pos.getSizeLeftUnder().x + tentativPos.x, pos.getSizeLeftUnder().y + tentativPos.y + 1.0f });
				MapChip::setData(static_cast<int>(MapChip::Type::NONE), static_cast<int>(mapNum.x), static_cast<int>(mapNum.y));

				mapNum = MapChip::GetNum({ pos.getSizeRightTop().x + tentativPos.x - 1.0f, pos.getSizeRightTop().y + tentativPos.y });
				MapChip::setData(static_cast<int>(MapChip::Type::NONE), static_cast<int>(mapNum.x), static_cast<int>(mapNum.y));

				mapNum = MapChip::GetNum({ pos.getSizeRightUnder().x + tentativPos.x - 1.0f, pos.getSizeRightUnder().y + tentativPos.y + 1.0f });
				MapChip::setData(static_cast<int>(MapChip::Type::NONE), static_cast<int>(mapNum.x), static_cast<int>(mapNum.y));

				if (camera->isDraw(pos.worldPos)) {
					camera->shakeFlg = true;
					blockBrkFlg = true;
				}
			}
			else {
				camera->shakeFlg = false;
				blockBrkFlg = false;
			}
		}
	}
	else {
		camera->shakeFlg = false;
		rushFlg = false;
	}

	if (!camera->isDraw(pos.worldPos) && camera->shakeFlg) {
		camera->shakeFlg = false;
	}

	if (pos.Collision(player->getQuad())) {
		scene = Situation::GAME_OVER;
	}
}

void Heavy::Draw() {
	Vector2D tmp = pos.worldPos;
	if (!rushEase) {
		pos.worldPos.x += static_cast<float>(MyMath::Random(-static_cast<int>(shakeScale.x), static_cast<int>(shakeScale.x)));
		pos.worldPos.y += static_cast<float>(MyMath::Random(-static_cast<int>(shakeScale.y), static_cast<int>(shakeScale.y)));
	}

	pos.Translate();

	switch (dir)
	{
	case Enemy::Direction::LEFT:
		camera->DrawQuad(pos, left, 12, MyMath::GetRGB(255, 255, 255, 255));
		break;
	case Enemy::Direction::RIGHT:
		camera->DrawQuad(pos, right, 12, MyMath::GetRGB(255, 255, 255, 255));
		break;
	case Enemy::Direction::FRONT:
		camera->DrawQuad(pos, front, 12, MyMath::GetRGB(255, 255, 255, 255));
		break;
	case Enemy::Direction::BACK:
		camera->DrawQuad(pos, back, 12, MyMath::GetRGB(255, 255, 255, 255));
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

	pos.worldPos = tmp;
}

void Heavy::Reset() {

}
#include "Heavy.hpp"
#include "Game/Player/Player.h"
#include "Game/MyMath/MyMath.h"
#include "Game/MapChip/MapChip.h"
#include <assert.h>

Heavy::Heavy(Camera* camera, Player* player):
	Enemy(camera, player),
	rushFlg(false),
	rushSpd(0.012f),
	rushLen(800.0f),
	rushEase(Easing(pos.worldPos, pos.worldPos, rushSpd, Easing::EaseInOutQuint)),
	maxSpd(10.0f)
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

	pos.worldPos = MapChip::getEmyPos(1);
}

Heavy::Heavy(Camera* camera, class Player* player, Vector2D pos) :
	Enemy(camera, player),
	rushFlg(false),
	rushSpd(0.012f),
	rushLen(800.0f),
	rushEase(Easing(pos, this->pos.worldPos, rushSpd, Easing::EaseInOutQuint)),
	maxSpd(10.0f)
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

	this->pos.worldPos = pos;
}

void Heavy::Update() {
	assert(player);
	tentativPos = pos.worldPos;

	if (MapChip::GetType(tentativPos) == static_cast<int>(MapChip::Type::SACRED)) {
		area = lowArea;
	}
	else {
		area = nmlArea;
	}

	if (stopFlg) {
		spd = lowSpd;
		frm.Start();
	}
	if (frm() > lowTime) {
		stopFlg = false;
		spd = nmlSpd;
		frm.Stop();
		frm.Restart();
	}

	frame.Start();

	// ランダム範囲内にいないときはプレイヤーに向かう
	if (!camera->isDraw(pos.worldPos, rushLen)) {
		int rnd = 0;
		if (frame() % rndTime == 0) {
			rnd = MyMath::Random(1, 4);
			moveVec = { 0.0f,0.0f };
		}

		if (rnd == 1) {
			moveVec.y = -nmlSpd;
		}
		else if (rnd == 2) {
			moveVec.y = nmlSpd;
		}
		else if (rnd == 3) {
			moveVec.x = -nmlSpd;
		}
		else if (rnd == 4) {
			moveVec.x = nmlSpd;
		}
		else {
			if (rnd != 0) {
				assert(!"rnd err");
			}
		}
	}
	else {
		moveVec = { 0.0f,0.0f };
	}
	if (camera->isDraw(pos.worldPos, rushLen)) {
		if (!rushFlg && !stopFlg) {
			rushFlg = true;
			rushEase.Set(pos.worldPos, player->getWorldPos() + (player->getWorldPos() - pos.worldPos) + player->getMoveVec(), rushSpd, Easing::EaseInBack);
		}
	}

	if (rushFlg) {
		moveVec = rushEase.Update() - pos.worldPos;
	}

	if (moveVec.x > maxSpd) {
		moveVec.x = maxSpd;
	}
	if (moveVec.x < -maxSpd) {
		moveVec.x = -maxSpd;
	}
	if (moveVec.y > maxSpd) {
		moveVec.y = maxSpd;
	}
	if (moveVec.y < -maxSpd) {
		moveVec.y = -maxSpd;
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

	tentativPos += moveVec * camera->getDelta() * area * static_cast<float>(Camera::getHitStop());


	this->Collision();

	pos.worldPos = tentativPos;

	// 移動したところがブロックだったら
	// 衝突
	// 衝突したらブロックは空白にする

	this->BlockBreak();

	//ラッシュが終わったら各種状態フラグを設定
	if (!rushEase) {
		rushFlg = false;
		stopFlg = true;
		blockBrkFlg = false;
	}

	// もしカメラに映ってないかつシェイクしていたらシェイクを止める
	if (!camera->isDraw(pos.worldPos) && camera->shakeFlg && Camera::getHitStop()) {
		camera->shakeFlg = false;
	}

	this->Dead();
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
		camera->DrawQuad(pos, left, 12.0f, MyMath::GetRGB(255, 255, 0, 255));
		break;
	case Enemy::Direction::RIGHT:
		camera->DrawQuad(pos, right, 12.0f, MyMath::GetRGB(255, 255, 0, 255));
		break;
	case Enemy::Direction::FRONT:
		camera->DrawQuad(pos, front, 12.0f, MyMath::GetRGB(255, 255, 0, 255));
		break;
	case Enemy::Direction::BACK:
		camera->DrawQuad(pos, back, 12.0f, MyMath::GetRGB(255, 255, 0, 255));
		break;
	default:
		assert(!"Enemy Direction Exception Error");
		break;
	}

	if (camera->isDraw(pos.worldPos)) {
		if (blockBrkFlg && allEnemySound) {
			blockBrk.SoundEffect(0.5f);
		}
	}

	if (seFlg) {
		deadSE.StartMusic(seVolum);
	}

	pos.worldPos = tmp;
}

void Heavy::Reset() {

}
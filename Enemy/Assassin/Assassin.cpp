#include "Assassin.hpp"
#include "Game/MapChip/MapChip.h"
#include "Game/MyMath/MyMath.h"
#include "Game/Player/Player.h"
#include <assert.h>

Assassin::Assassin(Camera* camera, class Player* player) :
	Enemy(camera, player)
{
	pos.worldPos = MapChip::getEmyPos(3);
}

void Assassin::Update() {
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
	if (!camera->isDraw(pos.worldPos)) {
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
		moveVec = { 0.0f };

		Vector2D predict = player->getWorldPos() + player->getMoveVec();

		moveVec = { spd,spd };

		moveVec.Rotate(MyMath::GetAngle(predict, pos.worldPos));

		moveVec *= spd;
	}

	tentativPos += moveVec * camera->getDelta() * area * static_cast<float>(Camera::getHitStop());

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

	this->BlockBreak();

	// もしカメラに映ってないかつシェイクしていたらシェイクを止める
	if (!camera->isDraw(pos.worldPos) && camera->shakeFlg && Camera::getHitStop()) {
		camera->shakeFlg = false;
	}

	this->Dead();
}

void Assassin::Draw() {
	switch (dir)
	{
	case Enemy::Direction::LEFT:
		camera->DrawQuad(pos, left, 12.0f, MyMath::GetRGB(255, 100, 100, 255));
		break;
	case Enemy::Direction::RIGHT:
		camera->DrawQuad(pos, right, 12.0f, MyMath::GetRGB(255, 100, 100, 255));
		break;
	case Enemy::Direction::FRONT:
		camera->DrawQuad(pos, front, 12.0f, MyMath::GetRGB(255, 100, 100, 255));
		break;
	case Enemy::Direction::BACK:
		camera->DrawQuad(pos, back, 12.0f, MyMath::GetRGB(255, 100, 100, 255));
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
}
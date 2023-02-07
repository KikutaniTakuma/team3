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

	// �e�N�X�`���[������ɓǂݍ��܂�Ă��邩
	assert(front);
	assert(back);
	assert(right);
	assert(left);

	dir = Direction::FRONT;

	shakeScale = { 5.0f, 5.0f };

	pos.worldPos = MapChip::getEmyPos(1);
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

	// �����_���͈͓��ɂ��Ȃ��Ƃ��̓v���C���[�Ɍ�����
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

	tentativPos += moveVec * camera->getDelta() * area;


	this->Collision();

	pos.worldPos = tentativPos;

	// �ړ������Ƃ��낪�u���b�N��������
	// �Փ�
	// �Փ˂�����u���b�N�͋󔒂ɂ���

	if (MapChip::GetType(pos.getPosLeftTop()) == 1 ||
		MapChip::GetType({ pos.getPosLeftUnder().x, pos.getPosLeftUnder().y + 2.0f }) == 1 ||
		MapChip::GetType({ pos.getPosRightTop().x - 2.0f, pos.getPosRightTop().y }) == 1 ||
		MapChip::GetType({ pos.getPosRightUnder().x - 2.0f, pos.getPosRightUnder().y + 2.0f }) == 1) {

		Vector2D mapNum;

		if (MapChip::GetType(pos.getPosLeftTop()) == 1) {
			mapNum = MapChip::GetNum(pos.getPosLeftTop());
			if (mapNum.x != 0.0f && mapNum.y != 0.0f && mapNum.x != static_cast<float>(MapChip::getMapWidth() - 1) && mapNum.y != static_cast<float>(MapChip::getMapHeight() - 1)) {
				MapChip::setData(static_cast<int>(MapChip::Type::BREAK), static_cast<int>(mapNum.x), static_cast<int>(mapNum.y));
			}
		}

		if (MapChip::GetType({ pos.getPosLeftUnder().x, pos.getPosLeftUnder().y + 2.0f }) == 1) {
			mapNum = MapChip::GetNum({ pos.getPosLeftUnder().x, pos.getPosLeftUnder().y + 1.0f });
			if (mapNum.x != 0.0f && mapNum.y != 0.0f && mapNum.x != static_cast<float>(MapChip::getMapWidth() - 1) && mapNum.y != static_cast<float>(MapChip::getMapHeight() - 1)) {
				MapChip::setData(static_cast<int>(MapChip::Type::BREAK), static_cast<int>(mapNum.x), static_cast<int>(mapNum.y));
			}
		}

		if (MapChip::GetType({ pos.getPosRightTop().x - 1.0f, pos.getPosRightTop().y }) == 1) {
			mapNum = MapChip::GetNum({ pos.getPosRightTop().x - 1.0f, pos.getPosRightTop().y });
			if (mapNum.x != 0.0f && mapNum.y != 0.0f && mapNum.x != static_cast<float>(MapChip::getMapWidth() - 1) && mapNum.y != static_cast<float>(MapChip::getMapHeight() - 1)) {
				MapChip::setData(static_cast<int>(MapChip::Type::BREAK), static_cast<int>(mapNum.x), static_cast<int>(mapNum.y));
			}
		}

		if (MapChip::GetType({ pos.getPosRightUnder().x - 1.0f, pos.getPosRightUnder().y + 2.0f }) == 1) {
			mapNum = MapChip::GetNum({ pos.getPosRightUnder().x - 1.0f, pos.getPosRightUnder().y + 1.0f });
			if (mapNum.x != 0.0f && mapNum.y != 0.0f && mapNum.x != static_cast<float>(MapChip::getMapWidth() - 1) && mapNum.y != static_cast<float>(MapChip::getMapHeight() - 1)) {
				MapChip::setData(static_cast<int>(MapChip::Type::BREAK), static_cast<int>(mapNum.x), static_cast<int>(mapNum.y));
			}
		}


		if (camera->isDraw(pos.worldPos)) {
			camera->shakeFlg = true;
			blockBrkFlg = true;
		}
	}
	else {
		camera->shakeFlg = false;
		blockBrkFlg = false;
	}

	//���b�V�����I�������e���ԃt���O��ݒ�
	if (!rushEase) {
		rushFlg = false;
		stopFlg = true;
		blockBrkFlg = false;
		camera->shakeFlg = false;
	}

	// �����J�����ɉf���ĂȂ����V�F�C�N���Ă�����V�F�C�N���~�߂�
	if (!camera->isDraw(pos.worldPos) && camera->shakeFlg) {
		camera->shakeFlg = false;
	}

	if (pos.Collision(player->getQuad())) {
		situation = Situation::GAME_OVER;
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
		if (blockBrkFlg && allEnemySound) {
			blockBrk.SoundEffect(0.5f);
		}
	}

	pos.worldPos = tmp;
}

void Heavy::Reset() {

}
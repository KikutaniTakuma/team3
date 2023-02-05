#include "Assassin.hpp"
#include "Game/MapChip/MapChip.h"
#include "Game/MyMath/MyMath.h"
#include "Game/Player/Player.h"
#include <assert.h>

Assassin::Assassin(Camera* camera, class Player* player) :
	Enemy(camera, player)
{
	pos.worldPos = MapChip::getEmyPos();
}

void Assassin::Update() {
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

	// �����_���͈͓��ɂ��Ȃ��Ƃ��̓v���C���[�Ɍ�����
	if (!camera->isDraw(pos.worldPos)) {
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

	else {		
		Vector2D predict = player->getWorldPos() + player->getMoveVec();

		moveVec = { spd,spd };

		moveVec.Rotate(MyMath::GetAngle(predict, pos.worldPos));

		moveVec *= spd;
	}

	tentativPos += moveVec * camera->getDelta();

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

	// �ړ������Ƃ��낪�u���b�N��������
	// �ړ��x�N�g���Ƃ͋t�����Ɉړ�(��Ŏ���)
	// �Փ�
	// �Փ˂�����u���b�N�͋󔒂ɂ���

	if (MapChip::GetType(pos.getPosLeftTop()) == 1 ||
		MapChip::GetType({ pos.getPosLeftUnder().x, pos.getPosLeftUnder().y + 2.0f }) == 1 ||
		MapChip::GetType({ pos.getPosRightTop().x - 1.0f, pos.getPosRightTop().y }) == 1 ||
		MapChip::GetType({ pos.getPosRightUnder().x - 1.0f, pos.getPosRightUnder().y + 2.0f }) == 1) {

		Vector2D mapNum = MapChip::GetNum(pos.getPosLeftTop());
		if (mapNum.x != 0.0f && mapNum.y != 0.0f && mapNum.x != static_cast<float>(MapChip::getMapWidth() - 1) && mapNum.y != static_cast<float>(MapChip::getMapHeight() - 1)) {
			MapChip::setData(static_cast<int>(MapChip::Type::NONE), static_cast<int>(mapNum.x), static_cast<int>(mapNum.y));
		}

		mapNum = MapChip::GetNum({ pos.getPosLeftUnder().x, pos.getPosLeftUnder().y + 1.0f });
		if (mapNum.x != 0.0f && mapNum.y != 0.0f && mapNum.x != static_cast<float>(MapChip::getMapWidth() - 1) && mapNum.y != static_cast<float>(MapChip::getMapHeight() - 1)) {
			MapChip::setData(static_cast<int>(MapChip::Type::NONE), static_cast<int>(mapNum.x), static_cast<int>(mapNum.y));
		}

		mapNum = MapChip::GetNum({ pos.getPosRightTop().x - 1.0f, pos.getPosRightTop().y });
		if (mapNum.x != 0.0f && mapNum.y != 0.0f && mapNum.x != static_cast<float>(MapChip::getMapWidth() - 1) && mapNum.y != static_cast<float>(MapChip::getMapHeight() - 1)) {
			MapChip::setData(static_cast<int>(MapChip::Type::NONE), static_cast<int>(mapNum.x), static_cast<int>(mapNum.y));
		}

		mapNum = MapChip::GetNum({ pos.getPosRightUnder().x - 1.0f, pos.getPosRightUnder().y + 1.0f });
		if (mapNum.x != 0.0f && mapNum.y != 0.0f && mapNum.x != static_cast<float>(MapChip::getMapWidth() - 1) && mapNum.y != static_cast<float>(MapChip::getMapHeight() - 1)) {
			MapChip::setData(static_cast<int>(MapChip::Type::NONE), static_cast<int>(mapNum.x), static_cast<int>(mapNum.y));
		}

		stopFlg = true;
		if (camera->isDraw(pos.worldPos)) {
			camera->shakeFlg = true;
			blockBrkFlg = true;
		}
	}
	else {
		camera->shakeFlg = false;
		blockBrkFlg = false;
	}

	// �����J�����ɉf���ĂȂ����V�F�C�N���Ă�����V�F�C�N���~�߂�
	if (!camera->isDraw(pos.worldPos) && camera->shakeFlg) {
		camera->shakeFlg = false;
	}

	if (pos.Collision(player->getQuad())) {
		scene = Situation::GAME_OVER;
	}

	pos.Translate();
}

void Assassin::Draw() {
	switch (dir)
	{
	case Enemy::Direction::LEFT:
		camera->DrawQuad(pos, left, 12.0f, MyMath::GetRGB(255, 0, 0, 255));
		break;
	case Enemy::Direction::RIGHT:
		camera->DrawQuad(pos, right, 12.0f, MyMath::GetRGB(255, 0, 0, 255));
		break;
	case Enemy::Direction::FRONT:
		camera->DrawQuad(pos, front, 12.0f, MyMath::GetRGB(255, 0, 0, 255));
		break;
	case Enemy::Direction::BACK:
		camera->DrawQuad(pos, back, 12.0f, MyMath::GetRGB(255, 0, 0, 255));
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
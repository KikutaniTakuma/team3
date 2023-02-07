#include "Enemy/Brave/Brave.hpp"
#include "Game/Player/Player.h"
#include "Game/MyMath/MyMath.h"
#include "Game/MapChip/MapChip.h"
#include "Goal/Goal.h"
#include <assert.h>

Brave::Brave(Camera* camera, class Player* player, Goal* goal):
	Enemy(camera, player),
	goal(goal),
	goalNum(0)
{
	pos.worldPos = MapChip::getEmyPos(2);
	spd = 20.0f;
}

void Brave::Update() {
	assert(player);
	moveVec = { 0.0f };
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

	// �J�����O�ɂ���Ƃ��̓{�^�������񂷂�
	if (!camera->isDraw(pos.worldPos) && goal->GetButtonNum() < goal->getMaxButtonNum() - 1) {
		moveVec = { spd, spd };

		moveVec.Rotate(MyMath::GetAngle(goal->getButtonPos(goalNum), pos.worldPos));

		moveVec *= spd;

		if (MyMath::PythagoreanTheorem((pos.worldPos + moveVec), goal->getButtonPos(goalNum)) < MapChip::kMapSize) {
			goalNum++;
			if (goalNum >= goal->getMaxButtonNum()) {
				goalNum = 0;
			}
		}
	}

	else {
		/// �v���C���[�̈ʒu�����ď��X�ɋ߂Â��čs��
		/// ���x�͈��
		/// �΂ߑ��s�͂Ȃ�
		/// �c�Ɖ��Œ����ق����ړ�����(�c<���̏ꍇ�������ɓ���)
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

		// ��̋t�o�[�W����
		/*if (abs(player->getWorldPosX() - pos.worldPos.x) > abs(player->getWorldPosY() - pos.worldPos.y)) {
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
		*/
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

	// �ړ������Ƃ��낪�u���b�N��������
	// �ړ��x�N�g���Ƃ͋t�����Ɉړ�(��Ŏ���)
	// �Փ�
	// �Փ˂�����u���b�N�͋󔒂ɂ���

	this->BlockBreak();

	// �����J�����ɉf���ĂȂ����V�F�C�N���Ă�����V�F�C�N���~�߂�
	if (!camera->isDraw(pos.worldPos) && camera->shakeFlg && Camera::getHitStop()) {
		camera->shakeFlg = false;
	}

	this->Dead();
}

void Brave::Draw() {
	switch (dir)
	{
	case Enemy::Direction::LEFT:
		camera->DrawQuad(pos, left, 12.0f, MyMath::GetRGB(0, 0, 255, 255));
		break;
	case Enemy::Direction::RIGHT:
		camera->DrawQuad(pos, right, 12.0f, MyMath::GetRGB(0, 0, 255, 255));
		break;
	case Enemy::Direction::FRONT:
		camera->DrawQuad(pos, front, 12.0f, MyMath::GetRGB(0, 0, 255, 255));
		break;
	case Enemy::Direction::BACK:
		camera->DrawQuad(pos, back, 12.0f, MyMath::GetRGB(0, 0, 255, 255));
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

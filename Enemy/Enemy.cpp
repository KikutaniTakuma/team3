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
bool Enemy::allEnemySound = true;

Enemy::Enemy(Camera* cameraPointa, Player* player)
	:Object(cameraPointa),
	player(player),
	spd(2.0f),
	nmlSpd(spd),
	lowSpd(0.0f),
	shakeScale(Vector2D(15.0f, 15.0f)),
	stopFlg(false),
	lowTime(24),
	rndLen(100.0f),
	blockBrk(Sound("./Resources/BlockBreak.wav", false)),
	blockBrkFlg(false),
	front(Texture("./Resources/Enemy/BraveFront.png", 128, 32, 32)),
	back(Texture("./Resources/Enemy/BraveBack.png", 128, 32, 32)),
	right(Texture("./Resources/Enemy/BraveRight.png", 128, 32, 32)),
	left(Texture("./Resources/Enemy/BraveLeft.png", 128, 32, 32)),
	dir(Direction::FRONT),
	rndTime(120),
	lowArea(0.5f),
	nmlArea(1.0f),
	area(nmlArea),
	deadSE(Sound("./Resources/DeadSE.wav",false)),
	seVolum(0.5f),
	seFlg(false),
	hitStopTime(60),
	easeSpd(0.016667f),
	up(2.0f),
	shakeTime(0.6f)
{
	// �e�N�X�`���[������ɓǂݍ��܂�Ă��邩
	assert(front);
	assert(back);
	assert(right);
	assert(left);

	pos.Set(MapChip::getEmyPos(0), { 32.0f, 32.0f });

	tentativPos = pos.worldPos;

	frm.Restart();

	frame.Restart();

	hitStopFrm.Restart();

	allEnemySound = true;
}

void Enemy::Update() {
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

		tentativPos += moveVec * camera->getDelta();
	}

	else {
		moveVec = { 0.0f };
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
		tentativPos += moveVec * camera->getDelta() * area * static_cast<float>(Camera::getHitStop());

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
		if (blockBrkFlg && allEnemySound) {
			blockBrk.SoundEffect(0.5f);
		}
	}
	if (seFlg) {
		deadSE.StartMusic(seVolum);
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

void Enemy::BlockBreak() {
	if (MapChip::GetType(pos.getPosLeftTop()) == 1 ||
		MapChip::GetType({ pos.getPosLeftUnder().x, pos.getPosLeftUnder().y + 2.0f }) == 1 ||
		MapChip::GetType({ pos.getPosRightTop().x - 1.0f, pos.getPosRightTop().y }) == 1 ||
		MapChip::GetType({ pos.getPosRightUnder().x - 1.0f, pos.getPosRightUnder().y + 2.0f }) == 1) {

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

		stopFlg = true;
		if (camera->isDraw(pos.worldPos) && Camera::getHitStop()) {
			camera->shakeFlg = true;
			blockBrkFlg = true;
		}
	}
	else if(Camera::getHitStop()) {
		camera->shakeFlg = false;
		blockBrkFlg = false;
	}
}

void Enemy::Dead() {
	if (pos.Collision(player->getQuad())) {
		hitStopFrm.Start();
		Camera::setHitStop(true);
		seFlg = true;
		camera->shakeFlg = true;

		allEnemySound = false;

		camera->scale = cameraUp.Update().x;

		camera->shakeScale = shakeScale;

		if (cameraUp.getT() > shakeTime) {
			camera->shakeFlg = false;
		}

		if (hitStopFrm() > hitStopTime) {
			situation = Situation::GAME_OVER;
			camera->shakeScale = Vector2D(10.0f, 10.0f);
			seFlg = false;
			camera->shakeFlg = false;
			Camera::setHitStop(false);
			allEnemySound = true;
			camera->scale = 1.0f;
		}
	}
	else {
		cameraUp.Set(Vector2D(1.0f, 0.0f), Vector2D(up, 0.0f), easeSpd, Easing::EaseInBack);
		seFlg = false;
	}
}
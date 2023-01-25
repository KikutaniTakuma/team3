#include "Goal/Goal.h"
#include <Novice.h>
#include "Game/MapChip/MapChip.h"
#include "Game/Texture/Texture.h"

Goal::Goal(Camera* camera) :Object(camera), kMaxButton(4) {
	for (auto& i:button)
	{
		i = new Button(camera);
	}
	goalAdvent = false;
	count = 0;
	rnd = { 0.0f,0.0f };

	pos.Set({ 1800.0f,4800.0f }, { (float)MapChip::kMapSize,(float)MapChip::kMapSize });
}

Goal::~Goal() {
	for (auto& i : button)
	{
		delete i;
	}
}

/*	�����ۂɂ�

	�{�^���������ꂽ�炻�̃{�^����true�ɂ���
	true�ɂȂ��Ă���{�^���̐��inum�j���L�^���Anum = 4�ŃS�[����true�ɂ���
	�S�[����true�ɂȂ�����A�}�b�v�����i�S�[�� = 2�j��ǂ����C�ցA
	�S�[�����W��pos.x = 0�Ƃ����Ƃ��Ax���W��0�ȉ��Ȃ�N���A�t���O��true�ɂ��A�V�[����؂�ւ���

*/

void Goal::StateUpdate() {
	count = 0;
	//	��Ԃ��m�F
	for (int num = 0; num < kMaxButton; num++)
	{
		if (button[num]->getPushButton())
		{
			count++;
		}
	}
	//	4�̃{�^����������Ă����Ȃ�S�[�����J��
	if (count == kMaxButton)
	{
		goalAdvent = true;
	}
}

void Goal::setBottonPos() {
	for (int i = 0; i < kMaxButton; i++)
	{		
		do {
			//	�����Ő������ē��Ă͂߂�
			rnd = { static_cast<float>((MyMath::Random((MapChip::kMapWidth / 2),0) * MapChip::kMapSize) + (MapChip::kMapSize / 2)),
				static_cast<float>((MyMath::Random(0,100) * MapChip::kMapSize) + (MapChip::kMapSize / 2)) };

		} while (MapChip::GetType(rnd) != static_cast<int>(MapChip::Type::NONE));

		button[i]->setPos(rnd);
	}
}

Vector2D Goal::getPos() {
	return pos.worldPos;
}

void Goal::Update() {
	//	�S�[�����J������
	if (goalAdvent)
	{
		/*�S�[�����W��pos.x = 0�Ƃ����Ƃ��Ax���W��0�ȉ��Ȃ�N���A�t���O��true�ɂ��A�V�[����؂�ւ���*/
	}
	//	����ȊO
	else
	{
		StateUpdate();
	}

	for (int i = 0; i < kMaxButton; i++)
	{
	//	Vector2D rnd = { MyMath::Random(0,100),MyMath::Random(0,100) };
	//	button[i].setPos(rnd); 
		/*Novice::ScreenPrintf(50, 100 + (i * 20), "%f",button[i]->getPos().x);
		Novice::ScreenPrintf(50, 200 + (i * 20), "%f",button[i]->getPos().y);*/
	}

	pos.worldMatrix.Translate(pos.worldPos);
}

void Goal::Reset() {

}

void Goal::Draw() {

}
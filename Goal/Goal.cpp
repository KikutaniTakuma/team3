#include "Goal/Goal.h"
#include <Novice.h>
#include "Game/MapChip/MapChip.h"

Goal::Goal() : kMaxButton(4) {
	button = new Button[kMaxButton];
	goalAdvent = false;
	count = 0;
	ram = { 0.0f,0.0f };
}

Goal::~Goal() {
	delete[] button;
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
		if (button[num].getPushButton())
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
			ram = { static_cast<float>(MyMath::Random(0,(MapChip::kMapWidth / 2)) * MapChip::kMapSize),
				static_cast<float>(MyMath::Random(0,100) * MapChip::kMapSize) };

		} while (MapChip::GetType(ram) != static_cast<int>(MapChip::Type::NONE));

		button[i].setPos(ram);
	}
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
	//	Vector2D ram = { MyMath::Random(0,100),MyMath::Random(0,100) };
	//	button[i].setPos(ram); 
		Novice::ScreenPrintf(50, 100 + (i * 20), "%f",button[i].getPos().x);
		Novice::ScreenPrintf(50, 200 + (i * 20), "%f",button[i].getPos().y);
	}

}

void Goal::Draw() {

}
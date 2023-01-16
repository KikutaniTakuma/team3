#include "Goal/Goal.h"
#include <Novice.h>

Goal::Goal() : kMaxButton(4) {
	button = new Button[kMaxButton];
	goalAdvent = false;
	count = 0;
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
}

void Goal::Draw() {
	Novice::ScreenPrintf(50, 100, "good");
}
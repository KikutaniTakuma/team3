#include"GoalUI.h"
#include"Goal/Goal.h"
GoalUI::GoalUI(Camera* camera)
	:Object(camera),
	UIsize(20.0f),
	width(1280.0f),
	height(720.0f),
	color(0xffffffff)
{
	positionGoal = new Goal;
}

GoalUI::~GoalUI() {
	delete positionGoal;
}

void GoalUI::Update() {
	//�S�[���̈ʒu��UI�̈ʒu�����킹��
	positionUI = positionGoal->getPos();
	//��ʂ̊O�ɏo�Ȃ��悤�ɂ��鏈��
	
	if (positionUI.x < UIsize) {
		positionUI.x = UIsize;
	}
	else if (positionUI.x > width-UIsize) {
		positionUI.x = width - UIsize;
	}
	if (positionUI.y > height - UIsize) {
		positionUI.y = height - UIsize;
	}
	else if (positionUI.y < UIsize) {
		positionUI.y = UIsize;
	}
	pos.worldPos = positionUI;
}

void GoalUI::Draw(class Texture& tex) {
	//��ʂ̒��ɃS�[�������邩�𔻕�
	//���݂���ꍇ�S�[����\�����A�Ȃ��ꍇUI��\������
	if (positionGoal->getPos().x > 0 && positionGoal->getPos().x < width - UIsize) {
		if (positionGoal->getPos().y > 0 && positionGoal->getPos().y < height - UIsize) {
			//���������S�[����\��
			camera->DrawUI(drawPos, tex, 0, 0, color);
		}
		else {
			//��������UI��\��
			camera->DrawUI(drawPos, tex, 0, 0, color);		}
	}
	else {
		camera->DrawUI(drawPos, tex, 0, 0, color);
	}
}

void GoalUI::Reset() {

}
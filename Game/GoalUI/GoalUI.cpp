#include"GoalUI.h"

GoalUI::GoalUI(Camera* camera)
	:Object(camera),
	UIsize(20),
	Width(1280),
	height(720),
	color(0xffffffff)
{}

void GoalUI::Update() {
	//�S�[���̈ʒu��UI�̈ʒu�����킹��
	positionUI = positionGoal;
	//��ʂ̊O�ɏo�Ȃ��悤�ɂ��鏈��
	
	if (positionUI.x < UIsize) {
		positionUI.x = UIsize;
	}
	else if (positionUI.x > Width-UIsize) {
		positionUI.x = Width - UIsize;
	}
	if (positionUI.y > height - UIsize) {
		positionUI.y = UIsize;
	}
	else if (positionUI.y < UIsize) {
		positionUI.y = UIsize;
	}
}

void GoalUI::Draw(class Texture& tex) {
	//��ʂ̒��ɃS�[�������邩�𔻕�
	//���݂���ꍇ�S�[����\�����A�Ȃ��ꍇUI��\������
	if (positionGoal.x > 0 && positionGoal.x < Width - UIsize) {
		if (positionGoal.y > 0 && positionGoal.y < height - UIsize) {
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
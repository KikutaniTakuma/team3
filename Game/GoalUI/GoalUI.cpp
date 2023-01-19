#include"GoalUI.h"
#include"Goal/Goal.h"
GoalUI::GoalUI(Camera* camera)
	:Object(camera),
	width(1280.0f),
	height(720.0f),
	color(0xffffffff)
{
	positionGoal = new Goal(camera);
}

GoalUI::~GoalUI() {
	delete positionGoal;
}

void GoalUI::Update() {
	//�S�[���̈ʒu��UI�̈ʒu�����킹��
	pos.worldPos = positionGoal->getPos();
	//��ʂ̊O�ɏo�Ȃ��悤�ɂ��鏈��
	
	if (pos.worldPos.x < pos.getSize().x / 2.0f) {
		pos.worldPos.x = pos.getSize().x / 2.0f;
	}
	else if (pos.worldPos.x > width - pos.getSize().x / 2.0f) {
		pos.worldPos.x = width - pos.getSize().x / 2.0f;
	}
	if (pos.worldPos.y > height - pos.getSize().y / 2.0f) {
		pos.worldPos.y = height - pos.getSize().y / 2.0f;
		pos.worldPos.y *= -1;
	}
	else if (pos.worldPos.y < pos.getSize().y / 2.0f) {
		pos.worldPos.y = pos.getSize().y / 2.0f;
		pos.worldPos.y *= -1;
	}
	
	pos.worldMatrix.Translate(pos.worldPos);
}

void GoalUI::Draw(class Texture& tex) {
	//��ʂ̒��ɃS�[�������邩�𔻕�
	//���݂���ꍇ�S�[����\�����A�Ȃ��ꍇUI��\������
	if (positionGoal->getPos().x > 0 && positionGoal->getPos().x < width - pos.getSize().x / 2.0f) {
		if (positionGoal->getPos().y > 0 && positionGoal->getPos().y < height - pos.getSize().y / 2.0f) {
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
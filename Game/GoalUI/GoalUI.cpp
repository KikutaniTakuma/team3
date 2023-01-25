#include"GoalUI.h"
#include"Goal/Goal.h"
#include<Novice.h>
#include "Game/MyMath/MyMath.h"

GoalUI::GoalUI(Camera* camera, Goal* goal)
	:Object(camera),
	width(1280.0f),
	height(720.0f),
	color(0x00ff00ff),
	positionGoal(goal)
{
	pos.Set({ 0.0f,0.0f }, {64.0f,64.0f});
	tex.Set("./Resources/GoalUIType1.png", 64, 64, 64);
}

GoalUI::~GoalUI() {
}

void GoalUI::Update() {

	//�S�[���̈ʒu��UI�̈ʒu�����킹��
	pos.worldPos = positionGoal->getPos() - camera->worldPos + (camera->getDrawSize() / 2.0f);

	//��ʂ̊O�ɏo�Ȃ��悤�ɂ��鏈��
	if (pos.worldPos.x < pos.getSize().x / 2.0f) {
		pos.worldPos.x = pos.getSize().x / 2.0f;
	}
	if (pos.worldPos.x > camera->getDrawSize().x - pos.getSize().x / 2.0f) {
		pos.worldPos.x = camera->getDrawSize().x - pos.getSize().x / 2.0f;
	}
	if (pos.worldPos.y < pos.getSize().y / 2.0f) {
		pos.worldPos.y = pos.getSize().y / 2.0f;
	}
	if (pos.worldPos.y > camera->getDrawSize().y - pos.getSize().y / 2.0f) {
		pos.worldPos.y = camera->getDrawSize().y - pos.getSize().y / 2.0f;
	}

	/*pos.worldPos += camera->worldPos;*/

	pos.worldMatrix.Translate(pos.worldPos);
}

void GoalUI::Draw() {
	//��ʂ̒��ɃS�[�������邩�𔻕�
	////���݂���ꍇ�S�[����\�����A�Ȃ��ꍇUI��\������
	if (!camera->isDraw(positionGoal->getPos())) {
		camera->DrawUI(drawPos, whiteBox, 0, false, color);
	}
	/*Novice::ScreenPrintf(0, 20, "GoalPos %0.1f", positionGoal->getPos().x);
	Novice::ScreenPrintf(0, 40, "GoalPos %0.1f", positionGoal->getPos().y);*/
}

void GoalUI::Reset() {

}
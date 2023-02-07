#include"GoalUI.h"
#include"Goal/Goal.h"
#include<Novice.h>
#include "Game/MyMath/MyMath.h"

GoalUI::GoalUI(Camera* camera)
	:Object(camera),
	width(1280.0f),
	height(720.0f),
	color(0x00ff00ff)
{
	pos.Set({ 0.0f,0.0f }, {64.0f,64.0f});
	tex.Set("./Resources/GoalUIType1.png", 64, 64, 64);

	goalTexture.Set("./Resources/Goal.png", 128, 128, 128);
}

GoalUI::~GoalUI() {
}

void GoalUI::SetPos(Vector2D pos) {
	goalPos = pos;
	this->pos.worldPos = pos;
}

void GoalUI::Update() {
	pos.worldPos = goalPos - camera->worldPos + (camera->getDrawSize() / 2.0f);

	//��ʂ̊O�ɏo�Ȃ��悤�ɂ��鏈��
	if (pos.worldPos.x < (pos.getSize().x / 1.5f)) {
		pos.worldPos.x = (pos.getSize().x / 1.5f);
	}
	if (pos.worldPos.x > (camera->getDrawSize().x - pos.getSize().x / 1.5f)) {
		pos.worldPos.x = (camera->getDrawSize().x - pos.getSize().x / 1.5f);
	}
	if (pos.worldPos.y < pos.getSize().y / 1.5f) {
		pos.worldPos.y = pos.getSize().y / 1.5f;
	}
	if (pos.worldPos.y > (camera->getDrawSize().y - pos.getSize().y / 1.5f)) {
		pos.worldPos.y = (camera->getDrawSize().y - pos.getSize().y / 1.5f);
	}

	/*pos.worldPos += camera->worldPos;*/

	pos.worldMatrix.Translate(pos.worldPos);
}

void GoalUI::Draw() {
	//��ʂ̒��ɃS�[�������邩�𔻕�
	////���݂���ꍇ�S�[����\�����A�Ȃ��ꍇUI��\������
	if (!camera->isDraw(goalPos)) {
		camera->DrawUI(pos, goalTexture, 0.0f, color);
	}
	/*Novice::ScreenPrintf(0, 20, "GoalPos %0.1f", positionGoal->getPos().x);
	Novice::ScreenPrintf(0, 40, "GoalPos %0.1f", positionGoal->getPos().y);*/
}

void GoalUI::Reset() {

}
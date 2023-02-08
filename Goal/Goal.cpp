#include "Goal/Goal.h"
#include <Novice.h>
#include "Game/MapChip/MapChip.h"
#include "Game/Texture/Texture.h"
#include "Game/Player/Player.h"


Goal::Goal(Camera* camera, Player* player) :
	Object(camera), 
	kMaxButton(4),
	goalUI(camera)
{
	for (auto& i : button)
	{
		i = new Button(camera);
	}
	for (auto& i : buttonUI) {
		i = new GoalUI(camera);
	}
	goalAdvent = false;
	count = 0;
	rnd = { 0.0f,0.0f };
	gameClear = false;
	goalTexture.Set("./Resources/Goal.png", 128, 128, 128);
	nGoalTexture.Set("./Resources/NotGoal.png", 128, 128, 128);
	buttonUITex.Set("./Resources/Stage/buttonUI.png", 32, 32, 32);

	this->player = player;

	pos.Set(MapChip::getGoalPos(MapChip::GetArea(pos.worldPos)), { 64.0f,64.0f });
	setBottonPos();

	for (int i = 0; i < button.size(); i++) {
		buttonUI[i]->SetPos(Vector2D(-5000.0f, -5000.0f));
	}
}

Goal::~Goal() {
	for (auto& i : button)
	{
		delete i;
	}
	for (auto& i : buttonUI) {
		delete i;
	}
}

/*	�����ۂɂ�

	�{�^���������ꂽ�炻�̃{�^����true�ɂ���
	true�ɂȂ��Ă���{�^���̐��inum�j���L�^���Anum = 4�ŃS�[����true�ɂ���
	�S�[����true�ɂȂ�����A�}�b�v�����i�S�[�� = 2�j��ǂ����C�ցA
	�S�[�����W�ƃv���C���[�̏Փ˔�����Ƃ�Atrue�ɂȂ�΃V�[���؂�ւ�

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
	if (count == kMaxButton && !goalAdvent)
	{
		goalAdvent = true;
		pos.worldPos = MapChip::getGoalPos(MapChip::GetArea(player->getWorldPos()));
	}
}

void Goal::setBottonPos() {
	for (int i = 0; i < kMaxButton; i++)
	{		
		
		button[i]->setPos(MapChip::getButtonPos(i));
		button[i]->Update();
	}
}

Vector2D Goal::getPos() {
	return pos.worldPos;
}

void Goal::setGoalPos(Vector2D pos) {
	this->pos.worldPos = pos;
}

bool Goal::getGameClear() {
	return gameClear;
}

bool Goal::getAdvent() const {
	return goalAdvent;
}

void Goal::Update() {
	//	�S�[�����J������
	if (goalAdvent)
	{
		/*�S�[�����W��pos.x = 0�Ƃ����Ƃ��Ax���W��0�ȉ��Ȃ�N���A�t���O��true�ɂ��A�V�[����؂�ւ���*/
		//	�v���C���[�Ƃ̏Փ˔���
		if (pos.Collision(player->getQuad()))
		{
			//	�N���A�t���O�𗧂Ă�
		//	gameClear = true;
			situation = Situation::GAME_CLEAR;
		}

	}
	//	����ȊO
	else
	{
		for (int i = 0; i < kMaxButton; i++)
		{
			button[i]->Collision(player->getQuad());
		}
		StateUpdate();
	}
	
//	//	�{�^���ƃv���C���[�̏Փ˔���
//	for (auto& i : button)
//	{
//		i->Collision(player->getQuad());
//	}

	for (int i = 0; i < button.size(); i++) {
		buttonUI[i]->SetPos(button[i]->getPos());
		buttonUI[i]->Update();
	}

	pos.worldMatrix.Translate(pos.worldPos);

	goalUI.SetPos(pos.worldPos);
	goalUI.Update();
}

void Goal::Reset() {
	goalAdvent = true;
	count = 0;
	rnd = { 0.0f,0.0f };
	gameClear = false;
	pos.Set(MapChip::getGoalPos(MapChip::GetArea(pos.worldPos)), { 64.0f,64.0f });
	setBottonPos();
}

void Goal::Draw() {
	if (goalAdvent)
	{
		camera->DrawQuad(pos, goalTexture, 0.0f, 0x00ff00ff);
	}
	else if(!goalAdvent){
		/*camera->DrawQuad(pos, nGoalTexture, 0.0f, 0xffffffff);*/
	}
	for (int i = 0; i < button.size();i++) {
		if (camera->isDraw(button[i]->getPos())) {
			button[i]->Draw();
		}
		else {
			if (!button[i]->getPushButton()) {
				buttonUI[i]->Draw(buttonUITex);
			}
		}
//		Novice::ScreenPrintf(0, 100 + (i * 20), "%0.1f %0.1f", button[i]->getPos().x, button[i]->getPos().y);
//		Novice::ScreenPrintf(0, 200, "%0.1f %0.1f", player->getWorldPosX(), player->getWorldPosY());
	}

	if (goalAdvent) {
		goalUI.Draw();
	}
}

int Goal::GetButtonNum() const {
	return count;
}

Vector2D Goal::getButtonPos(size_t index) const {
	if (index >= button.size()) {
		index = 0;
	}

	return button[index]->getPos();
}

int Goal::getMaxButtonNum() const {
	return kMaxButton;
}

void Goal::setSize(Vector2D size) {
	pos.setSize(size);
}
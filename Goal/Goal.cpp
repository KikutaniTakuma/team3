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

	this->player = player;

	pos.Set(MapChip::getGoalPos(), { 64.0f,64.0f });
	setBottonPos();
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
			
			switch (i)
			{
			case 0:	//	����
				rnd = { static_cast<float>((MyMath::Random(0, 100) * MapChip::kMapSize) + (MapChip::kMapSize / 2)),
					static_cast<float>((MyMath::Random(0, 100) * MapChip::kMapSize) + (MapChip::kMapSize / 2)) };
				break;
			case 1:	//	�E��
				rnd = { static_cast<float>((MyMath::Random(101, MapChip::kMapWidth) * MapChip::kMapSize) + (MapChip::kMapSize / 2)),
					static_cast<float>((MyMath::Random(0, 100) * MapChip::kMapSize) + (MapChip::kMapSize / 2)) };
				break;
			case 2:	//	����
				rnd = { static_cast<float>((MyMath::Random(0, 100) * MapChip::kMapSize) + (MapChip::kMapSize / 2)),
					static_cast<float>((MyMath::Random(101, MapChip::kMapHeight) * MapChip::kMapSize) + (MapChip::kMapSize / 2)) };
				break;
			case 3:	//	�E��
				rnd = { static_cast<float>((MyMath::Random(101, MapChip::kMapWidth) * MapChip::kMapSize) + (MapChip::kMapSize / 2)),
					static_cast<float>((MyMath::Random(101, MapChip::kMapHeight) * MapChip::kMapSize) + (MapChip::kMapSize / 2)) };
				break;
			}

		} while (MapChip::GetType(rnd) == static_cast<int>(MapChip::Type::BLOCK));

		button[i]->setPos(rnd);
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
			scene = Situation::GAME_CLEAR;
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
	pos.Set(MapChip::getGoalPos(), { 64.0f,64.0f });
	setBottonPos();
}

void Goal::Draw() {
	if (goalAdvent)
	{
		camera->DrawQuad(pos, goalTexture, 0, true, 0x00ff00ff);
	}
	else if(!goalAdvent){
		camera->DrawQuad(pos, nGoalTexture, 0, true, 0xffffffff);
	}
	for (int i = 0; i < button.size();i++) {
		if (camera->isDraw(button[i]->getPos())) {
			button[i]->Draw();
		}
		else {
			if (!button[i]->getPushButton()) {
				buttonUI[i]->Draw();
			}
		}
//		Novice::ScreenPrintf(0, 100 + (i * 20), "%0.1f %0.1f", button[i]->getPos().x, button[i]->getPos().y);
//		Novice::ScreenPrintf(0, 200, "%0.1f %0.1f", player->getWorldPosX(), player->getWorldPosY());
	}

	if (goalAdvent) {
		goalUI.Draw();
	}
}
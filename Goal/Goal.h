#pragma once
#include "Game/Vector2D/Vector2D.h"
#include "Button/Button.h"
#include "Game/Object/Object.h"
#include <array>

class Goal : public Object
{
public:
	Goal(Camera* camera, class Player* player);
	~Goal();

private:
	//	�{�^���ő吔
	const int kMaxButton;
	std::array<Button*, 4>button;
	
	//	�S�[�����J�����Ȃ�true
	bool goalAdvent;
	//	
	int count;
	//
	Vector2D rnd;
	//	�V�[���؂�ւ�
	void SceneChange();

	Player* player;

public:
	//	�{�^���̏�Ԋm�F
	void StateUpdate();
	//	�{�^���̃Z�b�g
	void setBottonPos();
	//	�S�[�����W�̎擾
	Vector2D getPos();
	//	�S�[�����W�̐ݒ�
	void setGoalPos(Vector2D pos);

	//
	void Update() override;

	void Reset() override;

	void Draw() override;

};

#pragma once
#include "Game/Vector2D/Vector2D.h"
#include "Button/Button.h"

class Goal
{
public:
	Goal();
	~Goal();

private:
	//	�{�^���ő吔
	const int kMaxButton;
	Button* button;
	
	//	�S�[�����J�����Ȃ�true
	bool goalAdvent;
	//	
	int count;
	//
	Vector2D ram;
	
	Vector2D pos;
	Vector2D size;

public:
	//	�{�^���̏�Ԋm�F
	void StateUpdate();
	//	�{�^���̃Z�b�g
	void setBottonPos();
	//	�S�[�����W�̎擾
	Vector2D getPos();

	//
	void Update();

	void Draw();

};

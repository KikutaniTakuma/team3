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
	

public:
	//	�{�^���̏�Ԋm�F
	void StateUpdate();
	//	�{�^���̃Z�b�g
	void setBottonPos();
	//
	void Update();

	void Draw();

};

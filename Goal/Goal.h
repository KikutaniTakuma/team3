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

public:
	//	�{�^���̏�Ԋm�F
	void StateUpdate();
	
	//
	void Update();

	void Draw();

};

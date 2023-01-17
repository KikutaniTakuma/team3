#pragma once
#include "Game/MyMath/MyMath.h"
#include "Game/Vector2D/Vector2D.h"

class Button
{
public:
	Button();

private:
	//	�����ꂽ��true
	bool isPushButton;
	//
	Vector2D pos;
	Vector2D size;

public:
	//	�v���C���[�Ƃ̏Փ˗p�̊֐�
	void Collision(Vector2D playerPos, Vector2D playerSize);

	//	�{�^���̏�Ԏ擾
	bool getPushButton();

	//	�{�^���̍��W�̐ݒ�
	void setPos(Vector2D pos);
	Vector2D getPos();

	void Draw();

};


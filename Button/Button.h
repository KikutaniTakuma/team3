#pragma once
#include "Game/MyMath/MyMath.h"
#include "Game/Vector2D/Vector2D.h"
#include "Game/Object/Object.h"

class Button : public Object
{
public:
	Button(Camera* camera);

private:
	//	�����ꂽ��true
	bool isPushButton;
	

public:
	//	�v���C���[�Ƃ̏Փ˗p�̊֐�
	void Collision(Vector2D playerPos, Vector2D playerSize);

	//	�{�^���̏�Ԏ擾
	bool getPushButton();

	//	�{�^���̍��W�̐ݒ�
	void setPos(Vector2D pos);
	Vector2D getPos();

	void Update() override;

	void Reset() override;

	void Draw() override;

};


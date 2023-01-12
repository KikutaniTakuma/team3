#pragma once

#include "Game/Object/Object.h"

class GoalUI : public Object {
public:
	GoalUI(Camera* camera);
private:	
	//�S�[���̃|�W�V����
	Vector2D positionGoal;
	//UI�̃|�W�V����
	Vector2D positionUI;
	//UI���̂̑傫��
	int UIsize;
	//��ʂ̑傫��(�p�ӂ��Ă���Ȃ炻����g�p����)
	int Width;
	int height;
	//�F
	unsigned int color;
public:
	void Object::Update()override;
	void Object::Draw(class Texture& tex)override;
	void Object::Reset()override;
};
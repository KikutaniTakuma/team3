#pragma once

#include "Game/Object/Object.h"

class GoalUI : public Object {
public:
	GoalUI(Camera* camera);
	~GoalUI();
private:	
	////�S�[���̃|�W�V����
	Goal *positionGoal;
	//UI�̃|�W�V����
	Vector2D positionUI;
	//UI���̂̑傫��
	float UIsize;
	//��ʂ̑傫��(�p�ӂ��Ă���Ȃ炻����g�p����)
	float width;
	float height;
	//�F
	unsigned int color;
public:
	void Object::Update()override;
	void Object::Draw(class Texture& tex)override;
	void Object::Reset()override;
};
#pragma once

#include "Game/Object/Object.h"

class GoalUI : public Object {
public:
	GoalUI(Camera* camera);
	~GoalUI();
private:	
	////�S�[���̃|�W�V����
	class Goal *positionGoal;
	
	//��ʂ̑傫��(�p�ӂ��Ă���Ȃ炻����g�p����)
	float width;
	float height;
	//�F
	unsigned int color;
public:
	void Update()override;
	void Draw(class Texture& tex)override;
	void Reset()override;
};
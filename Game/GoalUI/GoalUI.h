#pragma once

#include "Game/Object/Object.h"

class GoalUI : public Object {
public:
	GoalUI(Camera* camera, class Goal* goal);
	~GoalUI();
private:	
	////�S�[���̃|�W�V����
	class Goal *positionGoal;
	Texture tex;
	
	//��ʂ̑傫��(�p�ӂ��Ă���Ȃ炻����g�p����)
	float width;
	float height;
	//�F
	unsigned int color;
public:
	void Update()override;
	void Draw()override;
	void Reset()override;
};
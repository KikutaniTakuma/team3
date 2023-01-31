#pragma once

#include "Game/Object/Object.h"

class GoalUI : public Object {
public:
	GoalUI(Camera* camera);
	~GoalUI();
private:	
	Texture tex;
	Vector2D goalPos;

	Texture goalTexture;
	
	//��ʂ̑傫��(�p�ӂ��Ă���Ȃ炻����g�p����)
	float width;
	float height;
	//�F
	unsigned int color;
public:
	void SetPos(Vector2D pos);

	void Update()override;
	void Draw()override;
	void Reset()override;
};
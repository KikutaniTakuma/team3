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
	
	//画面の大きさ(用意しているならそれを使用する)
	float width;
	float height;
	//色
	unsigned int color;
public:
	void SetPos(Vector2D pos);

	void Update()override;
	void Draw()override;
	void Reset()override;
};
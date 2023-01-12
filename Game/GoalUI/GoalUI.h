#pragma once

#include "Game/Object/Object.h"

class GoalUI : public Object {
public:
	GoalUI(Camera* camera);
private:	
	//ゴールのポジション
	Vector2D positionGoal;
	//UIのポジション
	Vector2D positionUI;
	//UI自体の大きさ
	int UIsize;
	//画面の大きさ(用意しているならそれを使用する)
	int Width;
	int height;
	//色
	unsigned int color;
public:
	void Object::Update()override;
	void Object::Draw(class Texture& tex)override;
	void Object::Reset()override;
};
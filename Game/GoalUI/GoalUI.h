#pragma once

#include "Game/Object/Object.h"

class GoalUI : public Object {
public:
	GoalUI(Camera* camera);
	~GoalUI();
private:	
	////ゴールのポジション
	class Goal *positionGoal;
	//UIのポジション
	Vector2D positionUI;
	//UI自体の大きさ
	float UIsize;
	//画面の大きさ(用意しているならそれを使用する)
	float width;
	float height;
	//色
	unsigned int color;
public:
	void Object::Update()override;
	void Object::Draw(class Texture& tex)override;
	void Object::Reset()override;
};
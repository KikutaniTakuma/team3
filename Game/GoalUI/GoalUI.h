#pragma once

#include "Game/Object/Object.h"

class GoalUI : public Object {
public:
	GoalUI(Camera* camera);
	~GoalUI();
private:	
	////ゴールのポジション
	class Goal *positionGoal;
	
	//画面の大きさ(用意しているならそれを使用する)
	float width;
	float height;
	//色
	unsigned int color;
public:
	void Update()override;
	void Draw()override;
	void Reset()override;
};
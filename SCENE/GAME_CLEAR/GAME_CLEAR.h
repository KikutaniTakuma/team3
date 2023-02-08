#pragma once
#include "Game/Object/Object.h"
#include "SCENE/Scene/Scene.h"
#include "Game/Easing/Easing.h"

class Game_Clear : public Object, Scene
{
public:
	Game_Clear(Camera* camera);
	~Game_Clear();

private:
	//	�V�[���؂�ւ��p�t���O
	bool sceneFlag;
	//	�V�[���؂�ւ�
	void SceneChange();

	Texture BG;

	//	���󗦊֌W
	Texture number[10];
	int score;
	int oneNum;
	int twoNum;

	//	���E���炭����
	Quad linePos[2];
	Easing easeLine[2];

	//	��
	Texture percent;
	Quad percentPos;

	//	����
	Quad charaPos;
	Easing easeNum;
	//	���󗦂̕`��
	Quad gagePos[2];
	Easing gageEase[2];

	int getDigits(int value, int num);

	void SetScore();

public:
	void Update() override;

	void Reset() override;

	void Draw() override;

};


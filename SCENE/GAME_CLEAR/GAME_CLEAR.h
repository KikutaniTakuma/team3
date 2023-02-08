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

	bool select;

	//	���󗦊֌W
	Texture number[10];
	Texture text;
	int score;
	int oneNum;
	int twoNum;

	//	���E���炭����
	Quad linePos[2];
	Easing easeLine[2];

	//	��
	Texture percent;
	Quad percentPos;
	unsigned int perColor;

	//	����
	Quad charaPos;
	Easing easeNum;
	//	���󗦂̕`��
	Quad gagePos[2];
	Easing gageEase[2];

	//	
	Texture title;
	Quad titlePos;
	Texture retry;
	Quad retryPos;

	//	�R�����g
	Texture comment[3];
	int commentNum;
	Quad commentPos;
	Easing comEase;

	int getDigits(int value, int num);

	void SetScore();

public:
	void Update() override;

	void Reset() override;

	void Draw() override;

};


#pragma once
#include "Game/Object/Object.h"
#include "SCENE/Scene/Scene.h"
#include "Game/Easing/Easing.h"
#include "Game/Sound/Sound.h"

class Stage : public Object, Scene
{
public:
	Stage(Camera* camera);
	~Stage();

private:
	std::vector<Object*> hud;

	std::vector<class Enemy*> emy;

	Easing staging;
	int count;
	float easeSpd;
	bool flgSkip;
	bool flgSkipSecond;

	class Goal* goal;
	class Player* player;

	Texture tex;
	Easing start;
	Easing alpha;

	////�Q�[������UI�̕ϐ��Q
	//�N���X�^����UI�̕ϐ�
	Quad buttonPos[4];
	Texture buttonTex;

	//���󗦃Q�[�W��UI�̕ϐ�
	Quad gaugePos;
	Texture gaugeTex;

	//���󗦃Q�[�W���̕ϐ�
	Quad gaugeBerPos;
	Texture gaugeBerTex;

	////�Q�[�W���̊ۂ���̕ϐ�
	Quad stageLifePos;
	Texture stageLifeTex;
	////////////////////////
	bool goalFlg;
	Easing easeGoal;

	Sound goalSE;
	float seVolum;
	float seStart;
	bool seFlg;
	
public:
	void Update() override;
	void Draw() override;
	void Reset() override;
};


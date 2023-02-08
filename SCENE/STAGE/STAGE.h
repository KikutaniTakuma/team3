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

	////ゲーム中のUIの変数群
	//クリスタルのUIの変数
	Quad buttonPos[4];
	Texture buttonTex;

	//損壊率ゲージのUIの変数
	Quad gaugePos;
	Texture gaugeTex;

	//損壊率ゲージ内の変数
	Quad gaugeBerPos;
	Texture gaugeBerTex;

	////ゲージ横の丸いやつの変数
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


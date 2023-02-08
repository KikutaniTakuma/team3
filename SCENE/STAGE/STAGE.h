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

	////Q[ÌUIÌÏQ
	//NX^ÌUIÌÏ
	Quad buttonPos[4];
	Texture buttonTex;

	//¹ó¦Q[WÌUIÌÏ
	Quad gaugePos;
	Texture gaugeTex;

	//¹ó¦Q[WàÌÏ
	Quad gaugeBerPos;
	Texture gaugeBerTex;

	////Q[W¡ÌÛ¢âÂÌÏ
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


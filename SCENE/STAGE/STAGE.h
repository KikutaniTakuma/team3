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

	Texture skipTex;
	Quad skipPos;
	bool skipMessFlg;

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


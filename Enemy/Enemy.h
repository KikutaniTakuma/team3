#pragma once

#include "Game/Object/Object.h"
#include "Game/Frame/Frame.h"
#include "Game/Sound/Sound.h"
#include "SCENE/Scene/Scene.h"
#include "Game/Sound/Sound.h"
#include "Game/Easing/Easing.h"

class Enemy : public Object, public Scene {
protected:
	enum class Direction : short {
		LEFT = 0,
		RIGHT,
		FRONT,
		BACK
	};

public:
	static const int kMaxEmyNum;
	static bool allEnemySound;

public:
	Enemy() = delete;
	Enemy(Camera* cameraPointa, class Player* player);

protected:
	Vector2D moveVec;

	Vector2D tentativPos;

	float spd;

	float nmlSpd;
	float lowSpd;

	Vector2D shakeScale;
	bool stopFlg;

	Frame frm;
	unsigned int lowTime;

	float rndLen;

	Sound blockBrk;
	bool blockBrkFlg;

	// �e�N�X�`��
	Texture front;
	Texture back;
	Texture right;
	Texture left;

	// ����
	Direction dir;

	// �t���[���Ǘ��N���X�̃C���X�^���X
	Frame frame;

	int rndTime;

	float lowArea;
	float nmlArea;
	float area;

	Sound deadSE;
	float seVolum;
	bool seFlg;

	Frame hitStopFrm;
	int hitStopTime;

	Easing cameraUp;
	float easeSpd;

	float up;

	float shakeTime;
	

public:
	class Player* player;

protected:
	void Collision();

	void BlockBreak();

	void Dead();

public:
	virtual void Update() override;

	virtual void Draw() override;
	
	virtual void Reset() override;
};
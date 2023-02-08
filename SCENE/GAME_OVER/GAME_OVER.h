#pragma once
#include "Game/Object/Object.h"
#include "SCENE/Scene/Scene.h"
#include "Game/Easing/Easing.h"
#include "Game/Frame/Frame.h"

class Game_Over : public Object, Scene
{
public:
	Game_Over(Camera* camera);
	~Game_Over();

private:
	//	�V�[���؂�ւ��p�t���O
	bool sceneFlag;
	//	�V�[���؂�ւ�
	void SceneChange();

	Texture BG;

	const int kMaxText;
	Vector2D size;
	Texture gameoverText[8];
	Quad gameoverPos[8];
	Vector2D endPos[8];
	Easing text[8];

	int index;
	Frame easeFrame;

	/// <summary>
	/// true�Ȃ烊�X�^�[�g
	/// false�Ȃ�^�C�g��
	/// </summary>
	bool select;

	Texture title;
	Quad titlePos;
	Texture restart;
	Quad restartPos;

	Texture player;
	Quad playerPos;

	void EaseSet();

public:

	void Update() override;

	void Reset() override;

	void Draw() override;

};


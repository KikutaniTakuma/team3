#pragma once
#include "Game/Object/Object.h"
#include "SCENE/Scene/Scene.h"
#include "Game/Easing/Easing.h"
#include "Game/Sound/Sound.h"

#include <map>

class Title : public Object, Scene
{
public:
	Title(Camera *camera);
	~Title();

private:
	//	�V�[���؂�ւ��p�t���O
	bool sceneFlag;
	//	�V�[���؂�ւ�
	void SceneChange();
	//	�w�i�p
	unsigned int color;
	//	�t�F�[�h�A�E�g�p
	Quad testPos;

	//	�^�C�g�����S
	Texture titleText;
	Quad titleTextPos;

	//	�X�y�[�X����
	Texture pushSpace;
	Quad pushSpacePos;
	unsigned int pushSpaceColor;


	//	�L�����N�^�[
	//	����
	enum Direction {
		FRONT = 0,
		BACK,
		RIGHT,
		LEFT,
	};
	//	5�l��
	const int kMaxChara;
	std::array<Direction, 5> dir;
	std::array<Easing, 5> ease;
	Vector2D size;

	//	std::map �A�z�z��N���X
	//	player = 0
	//	�ǐՌ^ = 1
	//	�ːi�^ = 2
	//	�p�j�^ = 3
	//	�ҕ��^ = 4
	std::map<Direction, Texture> charaText[5];
	Quad charaTextPos[5];
	unsigned int charaColor[5];

	//	�ړ��p
	Vector2D speed;
	Vector2D vel;
	void Move();

	// oto
	Sound pushSpaceSE;
	float spaceSEVolum;

	Sound sceneChageSE;
	float sceneChageVolum;

public:

	void Update() override;

	void Reset() override;

	void Draw() override;

	
};


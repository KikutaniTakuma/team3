#pragma once
#include "Game/Object/Object.h"
#include "SCENE/Scene/Scene.h"

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
	Texture BG;
	unsigned int color;
	//	�t�F�[�h�A�E�g�p
	Quad testPos;

	//	�^�C�g�����S
	Texture titleText;
	Quad titleTextPos;

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
	Vector2D size;

	//	std::map �A�z�z��N���X
	//	player = 0
	//	�ǐՌ^ = 1
	//	�ːi�^ = 2
	//	�p�j�^ = 3
	//	�ҕ��^ = 4
	std::map<Direction, Texture> charaText[5];
	Quad charaTextPos[5];

	//	�ړ��p
	Vector2D speed;
	Vector2D vel;
	void Move();

public:

	void Update() override;

	void Reset() override;

	void Draw() override;

	
};


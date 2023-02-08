#pragma once
#include "Game/Vector2D/Vector2D.h"
#include "Button/Button.h"
#include "Game/Object/Object.h"
#include <array>
#include "SCENE/Scene/Scene.h"
#include "Game/GoalUI/GoalUI.h"
#include "Game/Fade/Fade.h"

class Goal : public Object, Scene
{
public:
	Goal(Camera* camera, class Player* player);
	~Goal();

private:
	//	�{�^���ő吔
	const int kMaxButton;
	std::array<Button*, 4> button;
	std::array<GoalUI*, 4> buttonUI;


	GoalUI goalUI;
	
	//	�S�[�����J�����Ȃ�true
	bool goalAdvent;
	//	
	int count;
	//
	Vector2D rnd;
	//	�V�[���؂�ւ��p�t���O
	bool gameClear;

	Player* player;

	unsigned int color;
	Fade goalAlpha;
	bool inout;

private:
	//
	Texture goalTexture;
	Texture nGoalTexture;
	Texture buttonUITex;


public:
	//	�{�^���̏�Ԋm�F
	void StateUpdate();
	//	�{�^���̃Z�b�g
	void setBottonPos();
	//	�S�[�����W�̎擾
	Vector2D getPos();
	//	�S�[�����W�̐ݒ�
	void setGoalPos(Vector2D pos);
	//
	bool getGameClear();

	bool getAdvent() const;

	//
	void Update() override;

	void Reset() override;

	void Draw() override;

	int GetButtonNum() const;

	Vector2D getButtonPos(size_t index) const;

	int getMaxButtonNum() const;

	void setSize(Vector2D size);
};

#pragma once

#include "Game/Object/Object.h"
#include "Game/Frame/Frame.h"
#include "Game/Easing/Easing.h"
#include <vector>
#include <Novice.h>

class Effect : public Object {
protected:
	struct Emitter {
		Vector2D max; // �ő�
		Vector2D min; // �ŏ�
	};

	struct Particle {
		Vector2D pos; // pos
		Vector2D moveVec; // �ړ��x�N�g��
		float spd; // �����X�s�[�h
		float size; // �傫��
		bool flg; // �������Ă��邩�̃t���O
		int alpha; // �A���t�@�l
		Easing ease; // �C�[�W���O�p
	};

public:
	Effect(Camera* camera);

public:
	// Effet�𓮂����t���O(�����false�ɂ���΋����I�ɏI��点����)
	bool flg;
	// �G�~�b�^�[�̃|�W�V����
	Vector2D worldPos;

protected:
	// �G�~�b�^�[
	Emitter emitter;

	// �p�[�e�B�N���pQuad
	Quad particleBuf;
	// �p�[�e�B�N���̉ϒ��z��
	std::vector<Particle> particle;
	// �p�[�e�B�N���̗�
	size_t particleNum;

	// �t���[��
	Frame frame;

	// �p�[�e�B�N�����o���p�x
	int freq;
	// �����p
	float acceleration;

	// �p�[�e�B�N�������̕p�x�ŏo�����߂̒l
	int count;

	// �u�����h���[�h
	BlendMode blend;

public:
	virtual void Update() override;
	virtual void Draw() override;
	virtual void Reset() override;
};
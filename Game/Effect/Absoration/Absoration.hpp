#pragma once

#include "Game/Effect/Effect.h"

// �G�t�F�N�g���C���N���[�h���Čp��
// �R���X�g���N�^�ɂ�Camera�|�C���^��

class Absoration : public Effect {
public:
	Absoration(Camera* camera);

	void Update() override;
	void Reset() override;
};
#pragma once

class Frame {
public:
	Frame(void);

	// �t���[��
	unsigned long long frame;

	// �X�^�[�g�t���O
	bool startFlag;

	// �X�^�[�g�֐�
	void Start(void);

	// ��~
	void Pause(void);

	// �X�g�b�v
	void Stop(void);

	// ���X�^�[�g
	void Restart(void);
};
#pragma once

class Frame {
public:
	Frame(void);

private:
	float add;

public:
	// �t���[��
	unsigned long long frame;

	// �X�^�[�g�t���O
	bool startFlag;

	// �X�^�[�g�֐�
	void Start(float delta = 1.0f);

	// ��~
	void Pause(void);

	// �X�g�b�v
	void Stop(void);

	// ���X�^�[�g
	void Restart(void);
};
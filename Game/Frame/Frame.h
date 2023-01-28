#pragma once

class Frame {
public:
	Frame(void);

private:
	float add;
	long double frame;

public:
	// �t���[��
	unsigned long long getFrame() const;

	// �X�^�[�g�t���O
	bool startFlag;

	// �X�^�[�g�֐�
	void Start();

	// ��~
	void Pause(void);

	// �X�g�b�v
	void Stop(void);

	// ���X�^�[�g
	void Restart(void);
};
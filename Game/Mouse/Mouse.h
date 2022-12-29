#pragma once

class Mouse {
public:
	enum class Button : short {
	LEFT_BUTTON, // ���N���b�N
	RIGHT_BUTTON, // �E�N���b�N
	MIDDLE_BUTTON, // �~�h���N���b�N
	BACK_SIDE_BUTTON, // �g���{�^���P
	FORWARD_SIDE_BUTTON, // �g���{�^���Q

	MOUSE_BUTTON_NUMBER // �{�^���̐� 
	};

private:
	// �{�^���̏�Ԃ��i�[���锠
	static bool isButton[static_cast<short>(Button::MOUSE_BUTTON_NUMBER)];
	// �O�t���[���̃{�^���̏�Ԃ��i�[���锠
	static bool isPreButton[static_cast<short>(Button::MOUSE_BUTTON_NUMBER)];
	// �z�C�[���ʂ��i�[���锠
	static int wheelAmount;

	// �O�t���[���̃{�^�����i�[
	static void CheckPreButton();

	// �}�E�X�̍��W���擾
	static void GetPos();

	// �z�C�[���ʂ��`�F�b�N
	static void Wheel();

public:
	// �}�E�X�̍��W
	static int x;
	static int y;

	// �}�E�X�{�^����������Ă��邩�ǂ���
	static void Input();

	// �������u��
	static bool Pushed(Button buttonNumber);

	// ������
	static bool LongPush(Button buttonNumber);

	// �������u��
	static bool Releaseed(Button buttonNumber);

	// �f�o�b�N�p
	static void Draw();



	///
	/// getter
	///
	
	// �z�C�[���ʂ��擾
	static inline int getWheelAmount() {
		return wheelAmount;
	}

	///
	/// setter
	/// 
	
	// �z�C�[���ʂ�C�ӂɕύX
	static inline void setWheelAmount(int wheel) {
		wheelAmount = wheel;
	}
};

#include "World.h"
#include "Game/KeyInput/KeyInput.h"
#include "Game/Mouse/Mouse.h"
#include "Game/Gamepad/Gamepad.h"
#include "Game/MapChip/MapChip.h"

#include <assert.h>

///==========================================================================================================================================
///=====�^�C�g��=============================================================================================================================
///==========================================================================================================================================

const char* kWindowTitle = "�u���b�N���b�V���[";

///==========================================================================================================================================
///==========================================================================================================================================
///==========================================================================================================================================


World::World()
{
	// ���C�u�����̏�����
	Novice::Initialize(kWindowTitle, MapChip::kWindowWidth, MapChip::kWindowHeight);

	MapChip::Initilize();

	camera = new Camera;

	assert(camera);

	MapChip::SetCamera(camera);

	game = std::make_unique<SceneManager>(camera);

	winMode = WindowMode::kFullscreen;

	Novice::SetWindowMode(winMode);

	Novice::SetMouseCursorVisibility(false);
}

World::~World() {
	delete camera;

	MapChip::Finalize();

	// ���C�u�����̏I��
	Novice::Finalize();
}

void World::Input() {
	// �L�[����
	KeyInput::Input();

	// �}�E�X�̓���
	Mouse::Input();

	// GamePad�̓���
	Gamepad::Input();
}

void World::Reset() {
	if (KeyInput::LongPush(DIK_LSHIFT) || KeyInput::LongPush(DIK_RSHIFT)) {
		if (KeyInput::Released(DIK_R)) {
			MapChip::Reset();

		}
	}
}

void World::MainLoop() {
	Camera::TotalStart();

	// �E�B���h�E�́~�{�^�����������܂Ń��[�v
	while (Novice::ProcessMessage() == 0) {
		Camera::DeltaStart();

		// �t���[���̊J�n
		Novice::BeginFrame();

		this->Input();

		// window�̍ő剻
		if (KeyInput::Released(DIK_F11) ||
			KeyInput::LongPush(DIK_LALT) && KeyInput::Released(DIK_RETURN)) {
			if (winMode == kWindowed) {
				winMode = kFullscreen;
			}
			else if (winMode == kFullscreen) {
				winMode = kWindowed;
			}

			Novice::SetWindowMode(winMode);
		}

		if (KeyInput::LongPush(DIK_LSHIFT) && KeyInput::LongPush(DIK_LCONTROL) && KeyInput::Released(DIK_F)) {
			if (!Camera::fpsDrwFlg) {
				Camera::fpsDrwFlg = true;
			}
			else {
				Camera::fpsDrwFlg = false;
			}
		}

		this->Reset();

		// �X�V����
		game->Update();

		// �Ŕw�ʂɍ��F��`��
		Novice::DrawBox(0, 0, 1280, 720, 0.0f, 0x000000ff, kFillModeSolid);

		camera->Update();

		// �`�揈��
		game->Draw();

		// �t���[���̏I��
		Novice::EndFrame();

		Camera::DeltaEnd();

		Camera::FpsDraw();

		if (KeyInput::Released(DIK_ESCAPE) || 
			Gamepad::LongPush(Gamepad::Button::LEFT_SHOULDER) && Gamepad::LongPush(Gamepad::Button::RIGHT_SHOULDER) && Gamepad::Released(Gamepad::Button::START))
		{ 
			Camera::ToatlEnd();
			break;
		}
	}
}
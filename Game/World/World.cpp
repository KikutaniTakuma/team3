#include "World.h"
#include "Game/KeyInput/KeyInput.h"
#include "Game/Mouse/Mouse.h"
#include "Game/Vector2D/Vector2D.h"
#include "Game/Matrix3x3/Matrix3x3.h"
#include "Game/Object/Object.h"
#include "Game/Player/Player.h"
#include "Game/Gamepad/Gamepad.h"
#include "Game/MapChip/MapChip.h"
#include "Game/Texture/Texture.h"
#include "Game/Camera/Camera.h"
#include "Enemy/Enemy.h"
#include "Game/GoalUI/GoalUI.h"
#include <Novice.h>
#include <assert.h>
#include <time.h>

#include "SCENE/SceneManager/SceneManager.hpp"

///==========================================================================================================================================
///==========================================================================================================================================
///==========================================================================================================================================

const char* kWindowTitle = "�u���b�N���b�V���[";

// �X�V����
void World::Update() {
	game->Update();
}

// �`�揈��
void World::Draw() {
	camera->Update();

	game->Draw();
}



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

	winMode = kWindowed;
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
	/*Camera::TotalStart();*/

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

		this->Reset();

		// �X�V����
		this->Update();

		// �Ŕw�ʂɍ��F��`��
		Novice::DrawBox(0, 0, 1280, 720, 0.0f, 0x000000ff, kFillModeSolid);

		this->Draw();

		// �t���[���̏I��
		Novice::EndFrame();

		Camera::DeltaEnd();

		Camera::FpsDraw();

		if (KeyInput::Released(DIK_ESCAPE) || 
			Gamepad::LongPush(Gamepad::Button::LEFT_SHOULDER) && Gamepad::LongPush(Gamepad::Button::RIGHT_SHOULDER) && Gamepad::Released(Gamepad::Button::START))
		{ 
			/*Camera::ToatlEnd();*/
			break;
		}
	}
}
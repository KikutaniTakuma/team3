#include "World.h"
#include "Game/KeyInput/KeyInput.h"
#include "Game/Mouse/Mouse.h"
#include "Game/Gamepad/Gamepad.h"
#include "Game/MapChip/MapChip.h"

#include <assert.h>

///==========================================================================================================================================
///=====タイトル=============================================================================================================================
///==========================================================================================================================================

const char* kWindowTitle = "ブロックラッシャー";

///==========================================================================================================================================
///==========================================================================================================================================
///==========================================================================================================================================


World::World()
{
	// ライブラリの初期化
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

	// ライブラリの終了
	Novice::Finalize();
}

void World::Input() {
	// キー入力
	KeyInput::Input();

	// マウスの入力
	Mouse::Input();

	// GamePadの入力
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

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		Camera::DeltaStart();

		// フレームの開始
		Novice::BeginFrame();

		this->Input();

		// windowの最大化
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

		// 更新処理
		game->Update();

		// 最背面に黒色を描画
		Novice::DrawBox(0, 0, 1280, 720, 0.0f, 0x000000ff, kFillModeSolid);

		// 描画処理
		game->Draw();

		// フレームの終了
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
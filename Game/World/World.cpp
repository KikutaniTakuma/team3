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

#include "Goal/Goal.h"

#include "SCENE/TITLE/TITLE.h"
#include "SCENE/STAGE/STAGE.h"
#include "SCENE/GAME_CLEAR/GAME_CLEAR.h"
#include "SCENE/GAME_OVER/GAME_OVER.h"

///==========================================================================================================================================
///==========================================================================================================================================
///==========================================================================================================================================

const char* kWindowTitle = "最高に面白いゲームになる予定";

// 更新処理
void World::Update() {
	
	object[scene.getScene()]->Update();
}

// 描画処理
void World::Draw() {
	camera->Update();

	object[scene.getScene()]->Draw();
	
	

}



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

	object.insert(std::make_pair(Scene::Situation::STAGE, new Stage(camera)));
	object.insert(std::make_pair(Scene::Situation::TITLE, new Title(camera)));
	object.insert(std::make_pair(Scene::Situation::GAME_CLEAR, new Game_Clear(camera)));
	object.insert(std::make_pair(Scene::Situation::GAME_OVER, new Game_Over(camera)));

}

World::~World() {
	delete camera;

	for (auto& i : object) {
		delete i.second;
	}

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
			for (auto& i : object) {
				i.second->Reset();
			}
		}
	}
}

void World::MainLoop() {
	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		Camera::DeltaStart();

		// フレームの開始
		Novice::BeginFrame();

		scene.Update();

		this->Input();

		this->Reset();

		this->Update();

		this->Draw();

		//-----
		if (scene.IsChange())
		{
			MapChip::Reset();
			object[Scene::Situation::TITLE]->Reset();
			object[Scene::Situation::STAGE]->Reset();
			object[Scene::Situation::GAME_CLEAR]->Reset();
			object[Scene::Situation::GAME_OVER]->Reset();
		}

		// フレームの終了
		Novice::EndFrame();

		Camera::DeltaEnd();

		Camera::FpsDraw();

		if (KeyInput::Released(DIK_ESCAPE) || 
			Gamepad::LongPush(Gamepad::Button::LEFT_SHOULDER) && Gamepad::LongPush(Gamepad::Button::RIGHT_SHOULDER) && Gamepad::Released(Gamepad::Button::START))
		{ break; }
	}
}
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
#include "Game/Enemy/Enemy.h"
#include <Novice.h>
#include <assert.h>
#include <thread>

///==========================================================================================================================================
///==========================================================================================================================================
///==========================================================================================================================================

const char* kWindowTitle = "LC1A_08_キクタニタクマ_タイトル";

// 更新処理
void World::Update() {
	switch (scene)
	{
	case SCENE::TITLE:
		title.Update();
		break;
	case SCENE::STAGE:
		for (auto& i : object) {
			i->Update();
		}

		goal.Update();

		break;
	case SCENE::GAME_CLEAR:
		break;
	case SCENE::GAME_OVER:
		break;
	case SCENE::MAX_SCENE:
		break;
	}
	
}

// 描画処理
void World::Draw() {
	
	switch (scene)
	{
	case SCENE::TITLE:
		title.Draw();
		break;
	case SCENE::STAGE:

		camera->Update();

		MapChip::Draw(*whiteBox);

		for (auto& i : object) {
			i->Draw(*whiteBox);
		}

		break;
	case SCENE::GAME_CLEAR:
		break;
	case SCENE::GAME_OVER:
		break;
	case SCENE::MAX_SCENE:
		break;
	}

}



///==========================================================================================================================================
///==========================================================================================================================================
///==========================================================================================================================================



World::World() {
	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, MapChip::kWindowWidth, MapChip::kWindowHeight);

	MapChip::Initilize();

	camera = new Camera;

	assert(camera);

	MapChip::SetCamera(camera);

	object.reserve(0);

	Player* tmp = new Player(camera);

	object.emplace_back(tmp);
	
	object.emplace_back(new Enemy(camera, tmp));

	this->whiteBox = new Texture("./Resources/white1x1.png", 32, 32, 32);

}

World::World(int screenSizeX, int screenSizeY) {
	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, screenSizeX, screenSizeY);

	camera = new Camera;

	assert(camera);

	MapChip::SetCamera(camera);

	object.reserve(0);

	object.emplace_back(new Player(camera));

	this->whiteBox = new Texture("./Resources/white1x1.png", 32, 32, 32);

}

World::~World() {
	delete camera;

	MapChip::Finalize();

	// ライブラリの終了
	Novice::Finalize();
}

void World::BeginProcess() {
	for (auto& i : object) {
		i->BeginProcess();
	}
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
				i->Reset();
			}
		}
	}
}

void World::MainLoop() {
	/// 
	/// 初期フレーム処理
	/// 
	
	// フレームの開始
	Novice::BeginFrame();

	this->Input();

	this->Reset();

	this->Update();

	// フレームの終了
	Novice::EndFrame();

	///
	/// ===============================================
	/// 

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		this->Input();

		this->Reset();

		// 非同期処理のための処理
		this->BeginProcess();

		std::thread update(&World::Update, this);

		std::thread draw(&World::Draw, this);

		update.join();
		draw.join();

		// フレームの終了
		Novice::EndFrame();

		if (KeyInput::Released(DIK_ESCAPE)) { break; }
	}
}
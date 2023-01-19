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
	case Scene::TITLE:
		title.Update();
		break;
	case Scene::STAGE:
		for (auto& i : object[Scene::STAGE]) {
			i->Update();
		}

		goal.Update();

		break;
	case Scene::GAME_CLEAR:
		break;
	case Scene::GAME_OVER:
		break;
	case Scene::MAX_SCENE:
		break;
	}
	
}

// 描画処理
void World::Draw() {
	
	switch (scene)
	{
	case Scene::TITLE:
		title.Draw();
		break;
	case Scene::STAGE:

		camera->Update();

		MapChip::Draw(*whiteBox);

		for (auto& i : object[Scene::STAGE]) {
			i->Draw(*whiteBox);
		}

		break;
	case Scene::GAME_CLEAR:
		break;
	case Scene::GAME_OVER:
		break;
	case Scene::MAX_SCENE:
		break;

	default:

		break;
	}

}



///==========================================================================================================================================
///==========================================================================================================================================
///==========================================================================================================================================



World::World():
	scene(Scene::STAGE)
{
	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, MapChip::kWindowWidth, MapChip::kWindowHeight);

	MapChip::Initilize();

	camera = new Camera;

	assert(camera);

	MapChip::SetCamera(camera);


	object.insert(std::make_pair(Scene::TITLE, std::vector<Object*>(0)));
	object.insert(std::make_pair(Scene::STAGE, std::vector<Object*>(0)));
	object.insert(std::make_pair(Scene::GAME_CLEAR, std::vector<Object*>(0)));
	object.insert(std::make_pair(Scene::GAME_OVER, std::vector<Object*>(0)));
	object.insert(std::make_pair(Scene::MAX_SCENE, std::vector<Object*>(0)));


	Player* tmp = new Player(camera);

	AddObj(Scene::STAGE, tmp);

	AddObj(Scene::STAGE, new Enemy(camera, tmp));

	this->whiteBox = new Texture("./Resources/white1x1.png", 32, 32, 32);

}

World::World(int screenSizeX, int screenSizeY) {
	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, screenSizeX, screenSizeY);

	camera = new Camera;

	assert(camera);

	MapChip::SetCamera(camera);

	object.insert(std::make_pair(Scene::TITLE, std::vector<Object*>(0)));
	object.insert(std::make_pair(Scene::STAGE, std::vector<Object*>(0)));
	object.insert(std::make_pair(Scene::GAME_CLEAR, std::vector<Object*>(0)));
	object.insert(std::make_pair(Scene::GAME_OVER, std::vector<Object*>(0)));
	object.insert(std::make_pair(Scene::MAX_SCENE, std::vector<Object*>(0)));


	Player* tmp = new Player(camera);

	AddObj(Scene::STAGE, tmp);

	AddObj(Scene::STAGE, new Enemy(camera, tmp));

	this->whiteBox = new Texture("./Resources/white1x1.png", 32, 32, 32);

}

World::~World() {
	delete camera;

	delete whiteBox;

	for (auto& i : object) {
		for (auto& j : i.second) {
			delete j;
		}
	}

	MapChip::Finalize();

	// ライブラリの終了
	Novice::Finalize();
}

void World::AddObj(Scene scene, class Object* obj) {
	object[scene].push_back(obj);
}

void World::BeginProcess() {
	for (auto& i : object) {
		for (auto& j : i.second) {
			j->BeginProcess();
		}
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
				for (auto& j : i.second) {
					j->Reset();
				}
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
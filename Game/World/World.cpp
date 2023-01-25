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
#include"Game/GoalUI/GoalUI.h"
#include <Novice.h>
#include <assert.h>
#include <thread>
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
	for (auto& i : object[scene.getScene()]) {
		i->Update();
	}
}

// 描画処理
void World::Draw() {
	
	switch (scene.getScene())
	{
	case Scene::Situation::TITLE:
		/*title.Draw(*whiteBox);*/
		camera->Update();
		for (auto& i : object[Scene::Situation::TITLE]) {
			i->Draw();
		}

		break;
	case Scene::Situation::STAGE:

		camera->Update();

		MapChip::Draw(*whiteBox);

		for (auto& i : object[Scene::Situation::STAGE]) {
			i->Draw();
		}

		break;
	case Scene::Situation::GAME_CLEAR:
		for (auto& i : object[scene.getScene()]) {
			i->Draw();
		}

		break;
	case Scene::Situation::GAME_OVER:
		camera->Update();
		for (auto& i : object[scene.getScene()]) {
			i->Draw();
		}

		break;
	case Scene::Situation::MAX_SCENE:
		break;

	default:

		break;
	}

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


	object.insert(std::make_pair(Scene::Situation::TITLE, std::vector<Object*>(0)));
	object.insert(std::make_pair(Scene::Situation::STAGE, std::vector<Object*>(0)));
	object.insert(std::make_pair(Scene::Situation::GAME_CLEAR, std::vector<Object*>(0)));
	object.insert(std::make_pair(Scene::Situation::GAME_OVER, std::vector<Object*>(0)));
	object.insert(std::make_pair(Scene::Situation::MAX_SCENE, std::vector<Object*>(0)));


	Player* tmp = new Player(camera);

	AddObj(Scene::Situation::STAGE, tmp);

	for (int i = 0; i < Enemy::kMaxEmyNum; i++) {
		AddObj(Scene::Situation::STAGE, new Enemy(camera, tmp));
	}

	Goal* goal = new Goal(camera);

	AddObj(Scene::Situation::STAGE, goal);

	AddObj(Scene::Situation::STAGE, new GoalUI(camera, goal));

	AddObj(Scene::Situation::TITLE, new Title(camera));
	
	

	this->whiteBox = new Texture("./Resources/white1x1.png", 32, 32, 32);

//	Novice::SetWindowMode(kFullscreen);

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

void World::AddObj(Scene::Situation scene, Object* obj) {
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

		camera->TimeStart();

		update = std::thread(&World::Update, this);

		draw = std::thread(&World::Draw, this);

		update.join();
		draw.join();

		/*this->Update();
		this->Draw();*/

		// フレームの終了
		Novice::EndFrame();

		camera->TimeEnd();
		camera->CreateDelta();

		camera->FpsDraw();

		if (KeyInput::Released(DIK_ESCAPE)) { break; }
	}
}
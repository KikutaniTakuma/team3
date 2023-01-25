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

const char* kWindowTitle = "�ō��ɖʔ����Q�[���ɂȂ�\��";

// �X�V����
void World::Update() {
	
	object[scene.getScene()]->Update();
}

// �`�揈��
void World::Draw() {
	camera->Update();

	object[scene.getScene()]->Draw();
	
	//switch (scene.getScene())
	//{
	//case Scene::Situation::TITLE:
	//	/*title.Draw(*whiteBox);*/
	//	camera->Update();
	//	for (auto& i : object[Scene::Situation::TITLE]) {
	//		i->Draw();
	//	}

	//	break;
	//case Scene::Situation::STAGE:

	//	camera->Update();

	//	MapChip::Draw(*whiteBox);

	//	for (auto& i : object[Scene::Situation::STAGE]) {
	//		i->Draw();
	//	}

	//	break;
	//case Scene::Situation::GAME_CLEAR:
	//	camera->Update();
	//	for (auto& i : object[scene.getScene()]) {
	//		i->Draw();
	//	}

	//	break;
	//case Scene::Situation::GAME_OVER:
	//	camera->Update();
	//	for (auto& i : object[scene.getScene()]) {
	//		i->Draw();
	//	}

	//	break;
	//case Scene::Situation::MAX_SCENE:
	//	break;

	//default:

	//	break;
	//}

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

	object.insert(std::make_pair(Scene::Situation::STAGE, new Stage(camera)));
	object.insert(std::make_pair(Scene::Situation::TITLE, new Title(camera)));
	object.insert(std::make_pair(Scene::Situation::GAME_CLEAR, new Game_Clear(camera)));
	object.insert(std::make_pair(Scene::Situation::GAME_OVER, new Game_Over(camera)));
	/*object.insert(std::make_pair(Scene::Situation::GAME_CLEAR, std::vector<Object*>(0)));
	object.insert(std::make_pair(Scene::Situation::GAME_OVER, std::vector<Object*>(0)));
	object.insert(std::make_pair(Scene::Situation::MAX_SCENE, std::vector<Object*>(0)));*/


	/*Player* tmp = new Player(camera);

	AddObj(Scene::Situation::STAGE, tmp);

	for (int i = 0; i < Enemy::kMaxEmyNum; i++) {
		AddObj(Scene::Situation::STAGE, new Enemy(camera, tmp));
	}

	Goal* goal = new Goal(camera);

	AddObj(Scene::Situation::STAGE, goal);

	AddObj(Scene::Situation::STAGE, new GoalUI(camera, goal));*/

	/*AddObj(Scene::Situation::TITLE, new Title(camera));

	AddObj(Scene::Situation::GAME_CLEAR, new Game_Clear(camera));

	AddObj(Scene::Situation::GAME_OVER, new Game_Over(camera));*/

//	Novice::SetWindowMode(kFullscreen);

}

World::~World() {
	delete camera;

	for (auto& i : object) {
		delete i.second;
	}

	MapChip::Finalize();

	// ���C�u�����̏I��
	Novice::Finalize();
}

void World::BeginProcess() {
	for (auto& i : object) {
		i.second->BeginProcess();
	}
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
			for (auto& i : object) {
				i.second->Reset();
			}
		}
	}
}

void World::MainLoop() {
	/// 
	/// �����t���[������
	/// 
	
	// �t���[���̊J�n
	Novice::BeginFrame();

	this->Input();

	this->Reset();

	this->Update();

	// �t���[���̏I��
	Novice::EndFrame();

	///
	/// ===============================================
	/// 

	// �E�B���h�E�́~�{�^�����������܂Ń��[�v
	while (Novice::ProcessMessage() == 0) {
		// �t���[���̊J�n
		Novice::BeginFrame();

		scene.Update();

		this->Input();

		this->Reset();
//-----
		if (scene.IsChange())
		{
			object[Scene::Situation::STAGE]->Reset();
			object[Scene::Situation::TITLE]->Reset();
		}

		// �񓯊������̂��߂̏���
		this->BeginProcess();

		camera->TimeStart();

		update = std::thread(&World::Update, this);

		draw = std::thread(&World::Draw, this);

		update.join();
		draw.join();

		/*this->Update();
		this->Draw();*/

		// �t���[���̏I��
		Novice::EndFrame();

		camera->TimeEnd();
		camera->CreateDelta();

		camera->FpsDraw();

		if (KeyInput::Released(DIK_ESCAPE)) { break; }
	}
}
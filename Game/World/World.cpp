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

#include "Goal/Goal.h"

#include "SCENE/TITLE/TITLE.h"
#include "SCENE/STAGE/STAGE.h"
#include "SCENE/GAME_CLEAR/GAME_CLEAR.h"
#include "SCENE/GAME_OVER/GAME_OVER.h"

///==========================================================================================================================================
///==========================================================================================================================================
///==========================================================================================================================================

const char* kWindowTitle = "LC1A_08_�L�N�^�j�^�N�}_�^�C�g��";

// �X�V����
void World::Update() {

	switch (scene)
	{
	case Scene::TITLE:
		for (auto& i : object[Scene::TITLE]) {
			i->Update();
		}
		break;
	case Scene::STAGE:
		for (auto& i : object[Scene::STAGE]) {
			i->Update();
		}

		break;
	case Scene::GAME_CLEAR:
		break;
	case Scene::GAME_OVER:
		break;
	case Scene::MAX_SCENE:
		break;
	}
	
}

// �`�揈��
void World::Draw() {
	
	switch (scene)
	{
	case Scene::TITLE:

		camera->Update();

		for (auto& i : object[Scene::TITLE]) {
			i->Draw(*whiteBox);
		}

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
	scene(Scene::TITLE)
{
	// ���C�u�����̏�����
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

	AddObj(Scene::STAGE, new Goal(camera));

	AddObj(Scene::TITLE, new Title(camera));

	this->whiteBox = new Texture("./Resources/white1x1.png", 32, 32, 32);

//	Novice::SetWindowMode(kFullscreen);

}

World::World(int screenSizeX, int screenSizeY) {
	// ���C�u�����̏�����
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

	// ���C�u�����̏I��
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
				for (auto& j : i.second) {
					j->Reset();
				}
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

		this->Input();

		this->Reset();

		// �񓯊������̂��߂̏���
		this->BeginProcess();

		std::thread update(&World::Update, this);

		std::thread draw(&World::Draw, this);

		update.join();
		draw.join();

		// �t���[���̏I��
		Novice::EndFrame();

		if (KeyInput::Released(DIK_ESCAPE)) { break; }
	}
}
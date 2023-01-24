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

const char* kWindowTitle = "�ō��ɖʔ����Q�[���ɂȂ�\��";

// �X�V����
void World::Update() {
	for (auto& i : object[scene.getScene()]) {
		i->Update();
	}
}

// �`�揈��
void World::Draw() {
	
	switch (scene.getScene())
	{
	case Scene::Situation::TITLE:
		/*title.Draw(*whiteBox);*/
		break;
	case Scene::Situation::STAGE:

		camera->Update();

		MapChip::Draw(*whiteBox);

		for (auto& i : object[Scene::Situation::STAGE]) {
			i->Draw();
		}

		break;
	case Scene::Situation::GAME_CLEAR:
		break;
	case Scene::Situation::GAME_OVER:
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
	// ���C�u�����̏�����
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

	/*AddObj(Scene::Situation::STAGE, new Enemy(camera, tmp));*/

	AddObj(Scene::Situation::STAGE, new Goal(camera));

	AddObj(Scene::Situation::TITLE, new Title(camera));

	this->whiteBox = new Texture("./Resources/white1x1.png", 32, 32, 32);

//	Novice::SetWindowMode(kFullscreen);

}

World::World(int screenSizeX, int screenSizeY) {
	// ���C�u�����̏�����
	Novice::Initialize(kWindowTitle, screenSizeX, screenSizeY);

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

	AddObj(Scene::Situation::STAGE, new Enemy(camera, tmp));

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
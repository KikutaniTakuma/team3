#include "SCENE/GAME_OVER/GAME_OVER.h"
#include "Game/KeyInput/KeyInput.h"
#include "Game/Gamepad/Gamepad.h"

Game_Over::Game_Over(Camera* camera) :Object(camera) {
	sceneFlag = false;
	pos.Set({ 640.0f,360.0f }, { 1280.0f,720.0f });
	BG.Set("./Resources/Title/gameover.png", 1280, 1280, 720);

//	text.Set()
}

Game_Over::~Game_Over() {

}

void Game_Over::SceneChange() {
	scene = Situation::TITLE;
}

void Game_Over::Update() {
	camera->scale = 1.0f;
	camera->shakeFlg = false;

	//	�V�[���؂�ւ�
	if (KeyInput::Pushed(DIK_SPACE) || Gamepad::Pushed(Gamepad::Button::A))
	{
		sceneFlag = true;
	}
	else if (sceneFlag)
	{
		SceneChange();
	}

	//	���W�ϊ�
	pos.Translate();
}

void Game_Over::Reset() {
	sceneFlag = false;
}

void Game_Over::Draw() {
	camera->DrawUI(pos, BG, 0.0f, 0xbbbbbbff);
}
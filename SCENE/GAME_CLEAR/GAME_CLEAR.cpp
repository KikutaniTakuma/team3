#include "SCENE/GAME_CLEAR/GAME_CLEAR.h"
#include "Game/KeyInput/KeyInput.h"

Game_Clear::Game_Clear(Camera* camera) :Object(camera) {
	sceneFlag = false;
	pos.Set({ 640.0f,360.0f }, { 1280.0f,720.0f });
	BG.Set("./Resources/Title/gameclear.png", 1280, 1280, 720);
}

Game_Clear::~Game_Clear() {

}

void Game_Clear::SceneChange() {
	scene = Situation::TITLE;
}

void Game_Clear::Update() {
	camera->shakeFlg = false;

	//	�V�[���؂�ւ�
	if (KeyInput::Pushed(DIK_SPACE))
	{
		sceneFlag = true;
	}
	else if(sceneFlag)
	{
		SceneChange();
	}

	//	���W�ϊ�
	pos.Translate();
}

void Game_Clear::Reset() {
	sceneFlag = false;
}

void Game_Clear::Draw() {
	camera->DrawUI(pos, BG, 0, false, 0xbbbbbbff);
}
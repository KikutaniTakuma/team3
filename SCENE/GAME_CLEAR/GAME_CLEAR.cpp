#include "SCENE/GAME_CLEAR/GAME_CLEAR.h"
#include "Game/KeyInput/KeyInput.h"
#include "Game/Gamepad/Gamepad.h"

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

	//	シーン切り替え
	if (KeyInput::Pushed(DIK_SPACE) || Gamepad::Pushed(Gamepad::Button::A))
	{
		sceneFlag = true;
	}
	else if(sceneFlag)
	{
		SceneChange();
	}

	//	座標変換
	pos.Translate();
}

void Game_Clear::Reset() {
	sceneFlag = false;
}

void Game_Clear::Draw() {
	camera->DrawUI(pos, BG, 0, 0xbbbbbbff);
}
#include "SCENE/TITLE/TITLE.h"
#include "Game/Fade/Fade.h"
#include "Game/MyMath/MyMath.h"
#include "Game/KeyInput/KeyInput.h"
#include "Game/Gamepad/Gamepad.h"

Title::Title(Camera* camera) : Object(camera) {
	pos.Set({640.0f,360.0f}, {1280.0f,720.0f});
	sceneFlag = false;
	BG.Set("./Resources/Title/background.png", 1280, 1280, 720);
	color = 0x00000000;

	testPos.Set({ 640.0f,360.0f }, { 1280.0f,720.0f });
}

Title::~Title() {

}

void Title::SceneChange() {
	scene = Situation::STAGE;
}

void Title::Update() {
	camera->scale = 1.0f;
	camera->shakeFlg = false;

	//	シーン切り替え
	if (KeyInput::Pushed(DIK_SPACE) || Gamepad::Pushed(Gamepad::Button::A))
	{
		sceneFlag = true;
	}
	else if (MyMath::GetAlpha(color) >= 255U)
	{
		SceneChange();
	}

	if (sceneFlag)
	{
		color = Fade::FadeInOut(color, 5.0f, true);
	}
	
	//	座標変換
	pos.Translate();
	testPos.Translate();
}

void Title::Reset() {
	sceneFlag = false;
	color = 0x00000000;
}

void Title::Draw() {
//	camera->DrawQuad(drawPos, tex, 0, false);
	camera->DrawUI(pos, BG, 0.0f, 0xffffffff);
	camera->DrawUI(testPos, whiteBox, 0.0f, color);
}




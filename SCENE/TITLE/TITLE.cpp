#include "SCENE/TITLE/TITLE.h"
#include "Game/Fade/Fade.h"
#include "Game/MyMath/MyMath.h"
#include "Game/KeyInput/KeyInput.h"

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


void Title::BeginProcess() {
	drawPos = pos;
	drawTestPos = testPos;
}

void Title::Update() {
	camera->shakeFlg = false;

	//	�V�[���؂�ւ�
	if (KeyInput::Pushed(DIK_SPACE))
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
	
	//	���W�ϊ�
	pos.Translate();
	testPos.Translate();
}

void Title::Reset() {
	sceneFlag = false;
	color = 0x00000000;
}

void Title::Draw() {
//	camera->DrawQuad(drawPos, tex, 0, false);
	camera->DrawUI(drawPos, BG, 0, false, 0xffffffff);
	camera->DrawUI(drawTestPos, whiteBox, 0, false, color);
}




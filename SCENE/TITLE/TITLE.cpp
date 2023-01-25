#include "SCENE/TITLE/TITLE.h"
#include "Game/Fade/Fade.h"
#include "Game/MyMath/MyMath.h"

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
	//	ƒV[ƒ“Ø‚è‘Ö‚¦
	if (sceneFlag)
	{
		SceneChange();
	}

	color = Fade::FadeInOut(color, 5.0f, true);
//	color = Fade::Flash(color, 5.0f);
	if (MyMath::GetAlpha(color) >= 255U)
	{
		sceneFlag = true;
	}

	//	À•W•ÏŠ·
	pos.Translate();
	testPos.Translate();
}

void Title::Reset() {
	sceneFlag = false;
}

void Title::Draw() {
//	camera->DrawQuad(drawPos, tex, 0, false);
	camera->DrawUI(drawPos, BG, 0, false, 0xffffffff);
	camera->DrawUI(drawTestPos, whiteBox, 0, false, color);
}




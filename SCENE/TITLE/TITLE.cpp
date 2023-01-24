#include "SCENE/TITLE/TITLE.h"
#include "Game/Fade/Fade.h"

Title::Title(Camera* camera) : Object(camera) {
	pos.Set({ 640.0f,360.0f }, { 1280.0f,720.0f });
	sceneFlag = false;
	BG.Set("./Resources/Title/background.png", 1280, 1280, 720);
	color = 0x00000000;
}

Title::~Title() {

}

void Title::SceneChange() {
	scene = Situation::STAGE;
}


void Title::Update() {
	//	ƒV[ƒ“Ø‚è‘Ö‚¦
	if (sceneFlag)
	{
		SceneChange();
	}

	color = Fade::FadeInOut(color, 5.0f, true);

	//	À•W•ÏŠ·
	pos.worldMatrix.Translate(pos.worldPos);
}

void Title::Reset() {
	sceneFlag = false;
}

void Title::Draw() {
//	camera->DrawQuad(drawPos, tex, 0, false);
	camera->DrawUI(drawPos, BG, 0, false, color);
}


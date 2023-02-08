#include "SCENE/GAME_CLEAR/GAME_CLEAR.h"
#include "Game/KeyInput/KeyInput.h"
#include "Game/Gamepad/Gamepad.h"

Game_Clear::Game_Clear(Camera* camera) :Object(camera) {
	sceneFlag = false;
#pragma region number
	number[0].Set("./Resources/number/0.png", 32, 32, 32);
	number[1].Set("./Resources/number/1.png", 32, 32, 32);
	number[2].Set("./Resources/number/2.png", 32, 32, 32);
	number[3].Set("./Resources/number/3.png", 32, 32, 32);
	number[4].Set("./Resources/number/4.png", 32, 32, 32);
	number[5].Set("./Resources/number/5.png", 32, 32, 32);
	number[6].Set("./Resources/number/6.png", 32, 32, 32);
	number[7].Set("./Resources/number/7.png", 32, 32, 32);
	number[8].Set("./Resources/number/8.png", 32, 32, 32);
	number[9].Set("./Resources/number/9.png", 32, 32, 32);
#pragma endregion number
	score = 0;

	pos.Set({ 640.0f,360.0f }, { 1280.0f,720.0f });
	BG.Set("./Resources/Title/gameclear.png", 1280, 1280, 720);

	linePos[0].Set({ pos.worldPos.x + 1280.0f,90.0f }, { 1280.0f,180.0f });
	linePos[1].Set({ pos.worldPos.x - 1280.0f,630.0f }, { 1280.0f,180.0f });
	
	charaPos.Set({ pos.worldPos.x + 1280.0f,360.0f }, { 384.0f,256.0f });
	gagePos.Set({ pos.worldPos.x + 1280.0f,360.0f }, { 512.0f,360.0f });
	for (int i = 0; i < 2; i++)
	{
		easeLine[i].Set(linePos[i].worldPos, { pos.worldPos.x,linePos[i].worldPos.y}, 0.02f, Easing::EaseOutElastic);
	}
	easeNum.Set(charaPos.worldPos, { 320.0f,charaPos.worldPos.y }, 0.01f, Easing::EaseOutExpo);
	gageEase.Set(gagePos.worldPos, { 880.0f,gagePos.worldPos.y }, 0.01f, Easing::EaseOutBounce);

	this->camera->worldPos = { 1280.0f / 2.0f, 720.0f / 2.0f };
}

Game_Clear::~Game_Clear() {

}

void Game_Clear::SceneChange() {
	situation = Situation::TITLE;
}

void Game_Clear::Update() {
	camera->scale = 1.0f;

	camera->shakeFlg = false;

	//	ÉVÅ[ÉìêÿÇËë÷Ç¶
	if (KeyInput::Pushed(DIK_SPACE) || Gamepad::Pushed(Gamepad::Button::A))
	{
		sceneFlag = true;
	}
	else if(sceneFlag)
	{
		SceneChange();
	}
	else if (KeyInput::Pushed(DIK_R))
	{
		Reset();
	}

	//	ê¸ÇÃà⁄ìÆ

	if (easeLine[0])
	{
		for (int i = 0; i < 2; i++)
		{
			linePos[i].worldPos = easeLine[i].Update();
		}
	}
	else
	{
		if (easeNum)
		{
			charaPos.worldPos = easeNum.Update();
			gagePos.worldPos = gageEase.Update();
		}
	}


}

void Game_Clear::Reset() {
	sceneFlag = false;

	linePos[0].Set({ pos.worldPos.x + 1280.0f,90.0f }, { 1280.0f,180.0f });
	linePos[1].Set({ pos.worldPos.x - 1280.0f,630.0f }, { 1280.0f,180.0f });

	charaPos.Set({ pos.worldPos.x + 1280.0f,360.0f }, { 384.0f,256.0f });
	gagePos.Set({ pos.worldPos.x + 1280.0f,360.0f }, { 512.0f,360.0f });
	for (int i = 0; i < 2; i++)
	{
		easeLine[i].Set(linePos[i].worldPos, { pos.worldPos.x,linePos[i].worldPos.y }, 0.02f, Easing::EaseOutElastic);
	}
	easeNum.Set(charaPos.worldPos, { 320.0f,charaPos.worldPos.y }, 0.01f, Easing::EaseOutExpo);
	gageEase.Set(gagePos.worldPos, { 880.0f,gagePos.worldPos.y }, 0.01f, Easing::EaseOutBounce);

	this->camera->worldPos = { 1280.0f / 2.0f, 720.0f / 2.0f };
}

void Game_Clear::Draw() {
	camera->DrawUI(pos, BG, 0.0f, 0xbbbbbbff);
	for (int i = 0; i < 2; i++)
	{
		camera->DrawUI(linePos[i], whiteBox, 0.0f, 0xbbbb00ff);
	}

	camera->DrawUI(charaPos, whiteBox, 0.0f, 0xff0000ff);
	camera->DrawUI(gagePos, whiteBox, 0.0f, 0xff0000ff);

}
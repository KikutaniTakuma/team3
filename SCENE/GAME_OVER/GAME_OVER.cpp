#include "SCENE/GAME_OVER/GAME_OVER.h"
#include "Game/KeyInput/KeyInput.h"
#include "Game/Gamepad/Gamepad.h"

Game_Over::Game_Over(Camera* camera) :Object(camera), kMaxText(8) {
	sceneFlag = false;
	pos.Set({ 640.0f,360.0f }, { 1280.0f,720.0f });
	BG.Set("./Resources/Title/gameover.png", 1280, 1280, 720);

	size = { 128.0f,128.0f };

	easeFrame.Restart();
	easeFrame.startFlag = true;
	index = 0;

#pragma region gameoverText

	gameoverText[0].Set("./Resources/Result/G.png", 32, 32, 32);
	gameoverText[1].Set("./Resources/Result/A.png", 32, 32, 32);
	gameoverText[2].Set("./Resources/Result/M.png", 32, 32, 32);
	gameoverText[3].Set("./Resources/Result/E.png", 32, 32, 32);
	gameoverText[4].Set("./Resources/Result/O.png", 32, 32, 32);
	gameoverText[5].Set("./Resources/Result/V.png", 32, 32, 32);
	gameoverText[6] = gameoverText[3];
	gameoverText[7].Set("./Resources/Result/R.png", 32, 32, 32);

	for (int i = 0; i < kMaxText; i++)
	{
		gameoverPos[i].Set({ 197.0f + (i * size.x),1000.0f }, size);
		endPos[i] = { gameoverPos[i].worldPos.x,500.0f };
	}

#pragma endregion gameoverText

	select = true;
	title.Set("./Resources/Title/title.png", 180, 180, 50);
	titlePos.Set({ gameoverPos[6].worldPos.x - (size.x / 2.0f),128.0f }, { 450.0f,128.0f });
	restart.Set("./Resources/Title/retry.png", 180, 180, 50);
	restartPos.Set({ gameoverPos[2].worldPos.x - (size.x / 2.0f),128.0f }, { 450.0f,128.0f });

}

Game_Over::~Game_Over() {

}

void Game_Over::SceneChange() {
	if (select)
	{
		scene = Situation::STAGE;
	}
	else
	{
		scene = Situation::TITLE;
	}
	
}

void Game_Over::EaseSet() {
	
	if (easeFrame() % 10 == 0 && index < kMaxText)
	{
		text[index].Set(gameoverPos[index].worldPos, endPos[index], 0.03f, Easing::EaseOutBounce);
		index++;
	}

}

void Game_Over::Update() {
	camera->scale = 1.0f;
	camera->shakeFlg = false;
	EaseSet();
	easeFrame.Start();
	for (int i = 0; i < index; i++)
	{
		gameoverPos[i].worldPos = text[i].Update();
	}
	
	//	�V�[���؂�ւ�
	if (KeyInput::Pushed(DIK_SPACE) || Gamepad::Pushed(Gamepad::Button::A))
	{
		sceneFlag = true;
	}
	else if (sceneFlag)
	{
		SceneChange();
	}

	if (KeyInput::Pushed(DIK_A)||KeyInput::Pushed(DIK_LEFT))
	{
		select = true;
	}
	else if (KeyInput::Pushed(DIK_D)||KeyInput::Pushed(DIK_RIGHT))
	{
		select = false;
	}
	else if (KeyInput::Pushed(DIK_R))
	{
		Reset();
	}


	//	���W�ϊ�
	pos.Translate();
}

void Game_Over::Reset() {
	sceneFlag = false;

	for (int i = 0; i < kMaxText; i++)
	{
		gameoverPos[i].Set({ 197.0f + (i * size.x),1000.0f }, size);
		endPos[i] = { gameoverPos[i].worldPos.x,500.0f };
	}
	select = true;

	easeFrame.Restart();
	easeFrame.startFlag = true;
	index = 0;

}

void Game_Over::Draw() {
	camera->DrawUI(pos, BG, 0.0f, 0x000000ff);

	for (int i = 0; i < kMaxText; i++)
	{
		camera->DrawQuad(gameoverPos[i], gameoverText[i], 0.0f, 0x0000ffff);
	}

	if (select)
	{
		camera->DrawQuad(titlePos, title, 0.0f, 0xffffffff);
		camera->DrawQuad(restartPos, restart, 0.0f, 0xff0000ff);
	}
	else
	{
		camera->DrawQuad(titlePos, title, 0.0f, 0xff0000ff);
		camera->DrawQuad(restartPos, restart, 0.0f, 0xffffffff);
	}
	
}
#include "SCENE/GAME_CLEAR/GAME_CLEAR.h"
#include "Game/KeyInput/KeyInput.h"
#include "Game/Gamepad/Gamepad.h"
#include "BrokenHud/BrokenHud.hpp"

Game_Clear::Game_Clear(Camera* camera) :Object(camera) {
	sceneFlag = false;
	select = false;
#pragma region TextureSet
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
	text.Set("./Resources/DamageRate.png", 112, 112, 48);
	percent.Set("./Resources/number/Percent.png", 32, 32, 32);

	title.Set("./Resources/Title/title.png", 180, 180, 50);
	retry.Set("./Resources/Title/retry.png", 180, 180, 50);

	comment[0].Set("./Resources/Result/comme1.png", 1000, 1000, 128);
	comment[1].Set("./Resources/Result/comme2.png", 1000, 1000, 128);
	comment[2].Set("./Resources/Result/comme3.png", 1000, 1000, 128);

#pragma endregion TextureSet
	score = static_cast<int>(BrokenHud::broknePer);
	oneNum = 0;
	twoNum = 0;
	perColor = 0xffffffff;
	commentNum = 0;

	pos.Set({ 640.0f,360.0f }, { 1280.0f,720.0f });
	
	linePos[0].Set({ pos.worldPos.x + 1280.0f,90.0f }, { 1280.0f,180.0f });
	linePos[1].Set({ pos.worldPos.x - 1280.0f,630.0f }, { 1280.0f,180.0f });
	
	percentPos.Set({ pos.worldPos.x + 540.0f,280.0f }, { 128.0f,128.0f });
	charaPos.Set({ pos.worldPos.x + 1280.0f,360.0f }, { 384.0f,256.0f });
	gagePos[0].Set({pos.worldPos.x + 1280.0f,360.0f}, {256.0f,360.0f});
	gagePos[1].Set({ pos.worldPos.x + 1280.0f + 256.0f,360.0f }, { 256.0f,360.0f });

	for (int i = 0; i < 2; i++)
	{
		easeLine[i].Set(linePos[i].worldPos, { pos.worldPos.x,linePos[i].worldPos.y}, 0.02f, Easing::EaseOutElastic);
	}
	easeNum.Set(charaPos.worldPos, { 320.0f,charaPos.worldPos.y }, 0.01f, Easing::EaseOutExpo);
	gageEase[0].Set(gagePos[0].worldPos, {980.0f,gagePos[0].worldPos.y}, 0.01f, Easing::EaseOutBounce);
	gageEase[1].Set(gagePos[1].worldPos, {724.0f,gagePos[1].worldPos.y}, 0.01f, Easing::EaseOutBounce);

	titlePos.Set({ 901.0f,100.0f }, { 450.0f,128.0f });
	retryPos.Set({ 389.0f,100.0f }, { 450.0f,128.0f });

	commentPos.Set({ 640.0f - 1280.0f,620.0f }, { 1000.0f,128.0f });
	comEase.Set(commentPos.worldPos, { 640.0f,commentPos.worldPos.y }, 0.01f, Easing::EaseOutCirc);

	this->camera->worldPos = { 1280.0f / 2.0f, 720.0f / 2.0f };

	sceneSe.Set("./Resources/Sound/PushSpaceSE.wav", false);
	selection.Set("./Resources/Sound/selection.wav", false);
	se.Set("./Resources/Sound/gameClearSE.wav", false);
	bgm.Set("./Resources/Sound/", true);
}

Game_Clear::~Game_Clear() {

}

void Game_Clear::SceneChange() {
	if (select)
	{
		situation = Situation::STAGE;
	}
	else
	{
		situation = Situation::TITLE;
	}
}


int Game_Clear::getDigits(int value, int num) {
	
	int mod_value = value % static_cast<int>(pow(10.0f, num + 1));
	int result = static_cast<int>(mod_value / pow(10.0f, num));

	return result;
}

void Game_Clear::SetScore() {
	oneNum = getDigits(score, 0);
	twoNum = getDigits(score, 1);
	
	if (score >= 40)
	{
		commentNum = 0;
		perColor = 0x90ee90ff;
	}
	else if (score >= 10)
	{
		commentNum = 1;
		perColor = 0xffa500ff;
	}
	else
	{
		commentNum = 2;
		perColor = 0xff0000ff;
	}

}

void Game_Clear::Update() {
	camera->scale = 1.0f;

	camera->shakeFlg = false;

	//	スコアの更新
	score = static_cast<int>(BrokenHud::broknePer);
	SetScore();
	
	//	シーン切り替え
	if (KeyInput::Pushed(DIK_SPACE) || Gamepad::Pushed(Gamepad::Button::A))
	{
		sceneFlag = true;
		sceneSe.StartMusic(0.5f);
	}
	else if(sceneFlag)
	{
		SceneChange();
	}
	else if (KeyInput::Pushed(DIK_A) || KeyInput::Pushed(DIK_LEFT)
		|| Gamepad::Pushed(Gamepad::Button::LEFT) || Gamepad::getStick(Gamepad::Stick::LEFT_X) < -5000)
	{
		select = true;
		selection.SoundEffect(0.5f);
	}
	else if (KeyInput::Pushed(DIK_D) || KeyInput::Pushed(DIK_RIGHT)
		|| Gamepad::Pushed(Gamepad::Button::RIGHT) || Gamepad::getStick(Gamepad::Stick::LEFT_X) > 5000)
	{
		select = false;
		selection.SoundEffect(0.5f);
	}
	else if (KeyInput::Pushed(DIK_R))
	{
		Reset();
	}


	//	線の移動

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
			for (int i = 0; i < 2; i++)
			{
				gagePos[i].worldPos = gageEase[i].Update();
			}
		}
		else
		{
			commentPos.worldPos = comEase.Update();
		}
	}

}

void Game_Clear::Reset() {
	sceneFlag = false;
	select = false;
	score = static_cast<int>(BrokenHud::broknePer);

	linePos[0].Set({ pos.worldPos.x + 1280.0f,90.0f }, { 1280.0f,180.0f });
	linePos[1].Set({ pos.worldPos.x - 1280.0f,630.0f }, { 1280.0f,180.0f });

	percentPos.Set({ pos.worldPos.x + 540.0f,280.0f }, { 128.0f,128.0f });
	charaPos.Set({ pos.worldPos.x + 1280.0f,360.0f }, { 384.0f,256.0f });
	gagePos[0].Set({ pos.worldPos.x + 1280.0f,360.0f }, { 256.0f,360.0f });
	gagePos[1].Set({ pos.worldPos.x + 1280.0f + 256.0f,360.0f }, { 256.0f,360.0f });

	for (int i = 0; i < 2; i++)
	{
		easeLine[i].Set(linePos[i].worldPos, { pos.worldPos.x,linePos[i].worldPos.y }, 0.02f, Easing::EaseOutElastic);
	}
	easeNum.Set(charaPos.worldPos, { 320.0f,charaPos.worldPos.y }, 0.01f, Easing::EaseOutExpo);
	gageEase[0].Set(gagePos[0].worldPos, { 980.0f,gagePos[0].worldPos.y }, 0.01f, Easing::EaseOutBounce);
	gageEase[1].Set(gagePos[1].worldPos, { 724.0f,gagePos[1].worldPos.y }, 0.01f, Easing::EaseOutBounce);

	titlePos.Set({ 901.0f,100.0f }, { 450.0f,128.0f });
	retryPos.Set({ 389.0f,100.0f }, { 450.0f,128.0f });

	commentPos.Set({ 640.0f - 1280.0f,620.0f }, { 1000.0f,128.0f });
	comEase.Set(commentPos.worldPos, { 640.0f,commentPos.worldPos.y }, 0.01f, Easing::EaseOutCirc);

	this->camera->worldPos = { 1280.0f / 2.0f, 720.0f / 2.0f };
}

void Game_Clear::Draw() {
	camera->DrawUI(pos, whiteBox, 0.0f, 0x000000ff);
	for (int i = 0; i < 2; i++)
	{
		camera->DrawUI(linePos[i], whiteBox, 0.0f, 0x555555ff);
	}

	camera->DrawUI(charaPos, text, 0.0f, 0xffffffff);
	camera->DrawUI(gagePos[0], number[oneNum], 0.0f, perColor);
	camera->DrawUI(gagePos[1], number[twoNum], 0.0f, perColor);
	camera->DrawUI(percentPos, percent, 0.0f, perColor);

	if (select)
	{
		camera->DrawUI(titlePos, title, 0.0f, 0xffffffff);
		camera->DrawUI(retryPos, whiteBox, 0.0f, 0xECD06Abb);
		camera->DrawUI(retryPos, retry, 0.0f, 0xff0000ff);
	}
	else
	{
		camera->DrawUI(titlePos, whiteBox, 0.0f, 0xECD06Abb);
		camera->DrawUI(titlePos, title, 0.0f, 0xff0000ff);
		camera->DrawUI(retryPos, retry, 0.0f, 0xffffffff);
	}

	camera->DrawUI(commentPos, comment[commentNum], 0.0f, perColor);

	if (!easeNum) {
		se.StartMusic(0.5f);
	}

	bgm.StartMusic(0.5f);
}
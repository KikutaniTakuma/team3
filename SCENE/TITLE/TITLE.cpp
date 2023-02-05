#include "SCENE/TITLE/TITLE.h"
#include "Game/Fade/Fade.h"
#include "Game/MyMath/MyMath.h"
#include "Game/KeyInput/KeyInput.h"
#include "Game/Gamepad/Gamepad.h"
#include "Game/Easing/Easing.h"
#include "Game/MapChip/MapChip.h"
#include <Novice.h>

Title::Title(Camera* camera) : Object(camera) , kMaxChara(5) {
	pos.Set({640.0f,360.0f}, {1280.0f,720.0f});
	sceneFlag = false;
	BG.Set("./Resources/Title/background.png", 1280, 1280, 720);
	color = 0x00000000;

	testPos.Set({ 640.0f,360.0f }, { 1280.0f,720.0f });

	for (int i = 0; i < kMaxChara; i++)
	{
		dir[i] = LEFT;
	}
	size = { 64.0f,64.0f };

#pragma region charaTextSet
	charaText[0].insert(std::make_pair(Direction::FRONT, Texture("./Resources/Player/SlimeFront.png", 256, 32, 32)));
	charaText[0].insert(std::make_pair(Direction::BACK, Texture("./Resources/Player/SlimeBack.png", 256, 32, 32)));
	charaText[0].insert(std::make_pair(Direction::RIGHT, Texture("./Resources/Player/SlimeRight.png", 256, 32, 32)));
	charaText[0].insert(std::make_pair(Direction::LEFT, Texture("./Resources/Player/SlimeLeft.png", 256, 32, 32)));
	charaTextPos[0].Set({ 500.0f,size.y }, size);

	charaText[1].insert(std::make_pair(Direction::FRONT, Texture("./Resources/Enemy/BraveFront.png", 128, 32, 32)));
	charaText[1].insert(std::make_pair(Direction::BACK, Texture("./Resources/Enemy/BraveBack.png", 128, 32, 32)));
	charaText[1].insert(std::make_pair(Direction::RIGHT, Texture("./Resources/Enemy/BraveRight.png", 128, 32, 32)));
	charaText[1].insert(std::make_pair(Direction::LEFT, Texture("./Resources/Enemy/BraveLeft.png", 128, 32, 32)));
	charaTextPos[1].Set({ 640.0f,size.y }, size);

	charaText[2].insert(std::make_pair(Direction::FRONT, Texture("./Resources/Enemy/FighterFront.png", 128, 32, 32)));
	charaText[2].insert(std::make_pair(Direction::BACK, Texture("./Resources/Enemy/FighterBack.png", 128, 32, 32)));
	charaText[2].insert(std::make_pair(Direction::RIGHT, Texture("./Resources/Enemy/FighterRight.png", 128, 32, 32)));
	charaText[2].insert(std::make_pair(Direction::LEFT, Texture("./Resources/Enemy/FighterLeft.png", 128, 32, 32)));
	charaTextPos[2].Set({ 700.0f,size.y }, size);

	charaText[3].insert(std::make_pair(Direction::FRONT, Texture("./Resources/Enemy/BraveFront.png", 128, 32, 32)));
	charaText[3].insert(std::make_pair(Direction::BACK, Texture("./Resources/Enemy/BraveBack.png", 128, 32, 32)));
	charaText[3].insert(std::make_pair(Direction::RIGHT, Texture("./Resources/Enemy/BraveRight.png", 128, 32, 32)));
	charaText[3].insert(std::make_pair(Direction::LEFT, Texture("./Resources/Enemy/BraveLeft.png", 128, 32, 32)));
	charaTextPos[3].Set({ 760.0f,size.y }, size);

	charaText[4].insert(std::make_pair(Direction::FRONT, Texture("./Resources/Enemy/BraveFront.png", 128, 32, 32)));
	charaText[4].insert(std::make_pair(Direction::BACK, Texture("./Resources/Enemy/BraveBack.png", 128, 32, 32)));
	charaText[4].insert(std::make_pair(Direction::RIGHT, Texture("./Resources/Enemy/BraveRight.png", 128, 32, 32)));
	charaText[4].insert(std::make_pair(Direction::LEFT, Texture("./Resources/Enemy/BraveLeft.png", 128, 32, 32)));
	charaTextPos[4].Set({ 820.0f,size.y }, size);
#pragma endregion charaTextSet

	speed = { 5.0f,5.0f };
	vel = { 0.0f,0.0f };
}

Title::~Title() {

}

void Title::SceneChange() {
	scene = Situation::STAGE;
}

void Title::Move() {
	for (int i = 0; i < kMaxChara; i++)
	{
		//	向きでの速度処理
		switch (dir[i])
		{
		case Direction::FRONT:
			vel.x = 0.0f;
			vel.y = -speed.y;
			break;
		case Direction::BACK:
			vel.x = 0.0f;
			vel.y = speed.y;
			break;
		case Direction::RIGHT:
			vel.x = speed.x;
			vel.y = 0.0f;
			break;
		case Direction::LEFT:
			vel.x = -speed.x;
			vel.y = 0.0f;
			break;
		default:
			break;
		}

		//	加算処理
		charaTextPos[i].worldPos += vel;

		//	制限
		if (charaTextPos[i].worldPos.x <= size.x && charaTextPos[i].worldPos.y <= size.y)
		{
			charaTextPos[i].worldPos.x = 0.0f + size.x;
			dir[i] = Direction::BACK;
		}
		else if (charaTextPos[i].worldPos.x <= size.x && charaTextPos[i].worldPos.y >= MapChip::kWindowHeight - size.y)
		{
			charaTextPos[i].worldPos.y = MapChip::kWindowHeight - size.y;
			dir[i] = Direction::RIGHT;
		}
		else if (charaTextPos[i].worldPos.x >= MapChip::kWindowWidth - size.x && charaTextPos[i].worldPos.y >= MapChip::kWindowHeight - size.y)
		{
			charaTextPos[i].worldPos.x = MapChip::kWindowWidth - size.x;
			dir[i] = Direction::FRONT;
		}
		else if (charaTextPos[i].worldPos.x >= MapChip::kWindowWidth - size.x && charaTextPos[i].worldPos.y <= size.y)
		{
			charaTextPos[i].worldPos.y = size.x;
			dir[i] = Direction::LEFT;
		}
	}	
}

void Title::Update() {
	

	Move();

	//	シーン切り替え
	if (KeyInput::Pushed(DIK_SPACE) || Gamepad::Pushed(Gamepad::Button::A))
	{
		sceneFlag = true;
	}
	else if (MyMath::GetAlpha(color) >= 255U)
	{
		SceneChange();
	}
	//	フェードアウト
	if (sceneFlag)
	{
		color = Fade::FadeInOut(color, 5.0f, true);
	}
	

}

void Title::Reset() {
	sceneFlag = false;
	color = 0x00000000;

	for (int i = 0; i < kMaxChara; i++)
	{
		if (i == 0)
		{
			charaTextPos[i].Set({ 500.0f,size.y }, size);
		}
		else
		{
			charaTextPos[i].Set({ 640.0f + ((i - 1) * 60.0f),size.y }, size);
		}
		dir[i] = LEFT;
	}

	//	カメラのリセット
	camera->scale = 1.0f;
	camera->shakeFlg = false;
	camera->worldPos = { static_cast<float>(MapChip::kWindowWidth / 2),static_cast<float>(MapChip::kWindowHeight / 2) };
}

void Title::Draw() {
//	camera->DrawQuad(drawPos, tex, 0, false);
	camera->DrawUI(pos, BG, 0.0f, 0xffffffff);

	for (int i = 0; i < kMaxChara; i++)
	{
		camera->DrawQuad(charaTextPos[i], charaText[i][dir[i]], 6.0f, MyMath::GetRGB(255, 255, 255, 255));
	}

	camera->DrawUI(testPos, whiteBox, 0.0f, color);
	
	Novice::ScreenPrintf(0, 30, "%0.1f : %0.1f", charaTextPos[0].worldPos.x, charaTextPos[0].worldPos.y);
}




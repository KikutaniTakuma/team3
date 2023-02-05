#include "SCENE/TITLE/TITLE.h"
#include "Game/Fade/Fade.h"
#include "Game/MyMath/MyMath.h"
#include "Game/KeyInput/KeyInput.h"
#include "Game/Gamepad/Gamepad.h"

#include "Game/MapChip/MapChip.h"
#include <Novice.h>

Title::Title(Camera* camera) : Object(camera) , kMaxChara(5) {
	pos.Set({640.0f,360.0f}, {1280.0f,720.0f});
	sceneFlag = false;
	BG.Set("./Resources/Title/background.png", 1280, 1280, 720);
	color = 0x00000000;

	testPos.Set({ 640.0f,360.0f }, { 1280.0f,720.0f });

	titleText.Set("./Resources/Title/titleText.png", 710, 710, 160);
	titleTextPos.Set({ 640.0f,440.0f }, { 950.0f,230.0f });

	pushSpace.Set("./Resources/Title/titlePushSpace.png", 390, 390, 60);
	pushSpacePos.Set({ 640.0f,220.0f }, { 600.0f,100.0f });
	pushSpaceColor = 0xffffffff;

	size = { 96.0f,96.0f };

#pragma region charaTextSet

	for (int i = 0; i < kMaxChara; i++)
	{
		if (i == 0)
		{
			charaTextPos[i].Set({ 500.0f,size.y }, size);
		}
		else
		{
			charaTextPos[i].Set({ (500.0f + (size.x * 2.0f)) + ((i - 1) * size.x),size.y }, size);
		}
		dir[i] = LEFT;
	}

	charaText[0].insert(std::make_pair(Direction::FRONT, Texture("./Resources/Player/SlimeFront.png", 256, 32, 32)));
	charaText[0].insert(std::make_pair(Direction::BACK, Texture("./Resources/Player/SlimeBack.png", 256, 32, 32)));
	charaText[0].insert(std::make_pair(Direction::RIGHT, Texture("./Resources/Player/SlimeRight.png", 256, 32, 32)));
	charaText[0].insert(std::make_pair(Direction::LEFT, Texture("./Resources/Player/SlimeLeft.png", 256, 32, 32)));
	charaColor[0] = MyMath::GetRGB(255, 255, 255, 255);

	charaText[1].insert(std::make_pair(Direction::FRONT, Texture("./Resources/Enemy/BraveFront.png", 128, 32, 32)));
	charaText[1].insert(std::make_pair(Direction::BACK, Texture("./Resources/Enemy/BraveBack.png", 128, 32, 32)));
	charaText[1].insert(std::make_pair(Direction::RIGHT, Texture("./Resources/Enemy/BraveRight.png", 128, 32, 32)));
	charaText[1].insert(std::make_pair(Direction::LEFT, Texture("./Resources/Enemy/BraveLeft.png", 128, 32, 32)));
	charaColor[1] = MyMath::GetRGB(255, 255, 255, 255);

	charaText[2].insert(std::make_pair(Direction::FRONT, Texture("./Resources/Enemy/FighterFront.png", 128, 32, 32)));
	charaText[2].insert(std::make_pair(Direction::BACK, Texture("./Resources/Enemy/FighterBack.png", 128, 32, 32)));
	charaText[2].insert(std::make_pair(Direction::RIGHT, Texture("./Resources/Enemy/FighterRight.png", 128, 32, 32)));
	charaText[2].insert(std::make_pair(Direction::LEFT, Texture("./Resources/Enemy/FighterLeft.png", 128, 32, 32)));
	charaColor[2] = MyMath::GetRGB(255, 255, 255, 255);

	charaText[3].insert(std::make_pair(Direction::FRONT, Texture("./Resources/Enemy/BraveFront.png", 128, 32, 32)));
	charaText[3].insert(std::make_pair(Direction::BACK, Texture("./Resources/Enemy/BraveBack.png", 128, 32, 32)));
	charaText[3].insert(std::make_pair(Direction::RIGHT, Texture("./Resources/Enemy/BraveRight.png", 128, 32, 32)));
	charaText[3].insert(std::make_pair(Direction::LEFT, Texture("./Resources/Enemy/BraveLeft.png", 128, 32, 32)));
	charaColor[3] = MyMath::GetRGB(0, 0, 255, 255);

	charaText[4].insert(std::make_pair(Direction::FRONT, Texture("./Resources/Enemy/BraveFront.png", 128, 32, 32)));
	charaText[4].insert(std::make_pair(Direction::BACK, Texture("./Resources/Enemy/BraveBack.png", 128, 32, 32)));
	charaText[4].insert(std::make_pair(Direction::RIGHT, Texture("./Resources/Enemy/BraveRight.png", 128, 32, 32)));
	charaText[4].insert(std::make_pair(Direction::LEFT, Texture("./Resources/Enemy/BraveLeft.png", 128, 32, 32)));
	charaColor[4] = MyMath::GetRGB(255, 0, 0, 255);
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
		//	�����ł̑��x����
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

		//	���Z����
		charaTextPos[i].worldPos += vel;

		//	����
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

	//	�V�[���؂�ւ�
	if (KeyInput::Pushed(DIK_SPACE) || Gamepad::Pushed(Gamepad::Button::A))
	{
		sceneFlag = true;
	}
	else if (MyMath::GetAlpha(color) >= 255U)
	{
		SceneChange();
	}
	//	�t�F�[�h�A�E�g
	if (sceneFlag)
	{
		color = Fade::FadeInOut(color, 5.0f, true);
	}
	//	�_��
	pushSpaceColor = Fade::Flash(pushSpaceColor, 5.0f);

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
			charaTextPos[i].Set({ (500.0f + (size.x * 2.0f)) + ((i - 1) * size.x),size.y }, size);
		}
		dir[i] = LEFT;
	}

	//	�J�����̃��Z�b�g
	camera->scale = 1.0f;
	camera->shakeFlg = false;
	camera->worldPos = { static_cast<float>(MapChip::kWindowWidth / 2),static_cast<float>(MapChip::kWindowHeight / 2) };
}

void Title::Draw() {
//	camera->DrawQuad(drawPos, tex, 0, false);
	camera->DrawUI(pos, BG, 0.0f, 0x000000ff);
	camera->DrawUI(titleTextPos, titleText, 0.0f, 0xffffffff);
	camera->DrawUI(pushSpacePos, pushSpace, 0.0f, pushSpaceColor);

	Novice::DrawBox(48, 70, 96, 612, 0.0f, 0x504c4cff, kFillModeSolid);
	Novice::DrawBox(1136, 70, 96, 612, 0.0f, 0x504c4cff, kFillModeSolid);
	Novice::DrawBox(48, 70, 1184, 84, 0.0f, 0x504c4cff, kFillModeSolid);
	Novice::DrawBox(48, 598, 1184, 84, 0.0f, 0x504c4cff, kFillModeSolid);

	for (int i = 0; i < kMaxChara; i++)
	{
		camera->DrawQuad(charaTextPos[i], charaText[i][dir[i]], 6.0f, charaColor[i]);
	}

	//	�t�F�[�h�A�E�g�p
	camera->DrawUI(testPos, whiteBox, 0.0f, color);

}




#include "BrokenHud.hpp"
#include "Game/MapChip/MapChip.h"
#include "Game/MyMath/MyMath.h"

float BrokenHud::broknePer = 100.0f;

BrokenHud::BrokenHud(Camera* camera):
	Object(camera),
	deadline(60.0f),
	color(MyMath::GetRGB(255,255,255,255)),
	lowColor(MyMath::GetRGB(255,0,0,255))
{
	tex.insert(std::make_pair(0, std::move(Texture("./Resources/number/0.png", 32, 32, 32))));
	tex.insert(std::make_pair(1, std::move(Texture("./Resources/number/1.png", 32, 32, 32))));
	tex.insert(std::make_pair(2, std::move(Texture("./Resources/number/2.png", 32, 32, 32))));
	tex.insert(std::make_pair(3, std::move(Texture("./Resources/number/3.png", 32, 32, 32))));
	tex.insert(std::make_pair(4, std::move(Texture("./Resources/number/4.png", 32, 32, 32))));
	tex.insert(std::make_pair(5, std::move(Texture("./Resources/number/5.png", 32, 32, 32))));
	tex.insert(std::make_pair(6, std::move(Texture("./Resources/number/6.png", 32, 32, 32))));
	tex.insert(std::make_pair(7, std::move(Texture("./Resources/number/7.png", 32, 32, 32))));
	tex.insert(std::make_pair(8, std::move(Texture("./Resources/number/8.png", 32, 32, 32))));
	tex.insert(std::make_pair(9, std::move(Texture("./Resources/number/9.png", 32, 32, 32))));

	pos.Set(Vector2D(50.0f, 620.0f), Vector2D(64.0f,64.0f));

	perTex = std::move(Texture("./Resources/number/Percent.png", 32, 32, 32));
	message = std::move(Texture("./Resources/DamageRate.png", 112, 112, 48));
	messagePos.Set({ pos.worldPos.x + 56.0f, pos.worldPos.y + 60.0f }, Vector2D(140.0f, 64.0f));
}

void BrokenHud::Update() {
	broknePer = (MapChip::GetBlockBreakPer() - deadline) / (100.0f - deadline) * 100.0f;
}


void BrokenHud::Draw() {
	int one = static_cast<int>(broknePer) - (static_cast<int>(broknePer) / 10) * 10;
	int ten = (static_cast<int>(broknePer) / 10);
	int hundread = (static_cast<int>(broknePer) / 100);

	if (one < 0 || one > 9) {
		one = 0;
	}
	if (ten < 0 || ten > 9) {
		ten = 0;
	}
	if (hundread < 0 || hundread > 9) {
		hundread = 0;
	}

	Vector2D  hundreadPos = pos.worldPos;
	Vector2D tenPos = { pos.worldPos.x + pos.getSize().x + 5.0f, pos.worldPos.y};
	Vector2D onePos = { tenPos.x + pos.getSize().x + 5.0f, pos.worldPos.y };
	Vector2D perPos = { onePos.x + pos.getSize().x + 5.0f, pos.worldPos.y };

	if (broknePer > 20.0f) {
		pos.worldPos = hundreadPos;

		camera->DrawUI(pos, tex[hundread], 0, color);

		pos.worldPos = tenPos;

		camera->DrawUI(pos, tex[ten], 0, color);

		pos.worldPos = onePos;

		camera->DrawUI(pos, tex[one], 0, color);
	}
	else {
		pos.worldPos = hundreadPos;

		camera->DrawUI(pos, tex[hundread], 0, lowColor);

		pos.worldPos = tenPos;

		camera->DrawUI(pos, tex[ten], 0, lowColor);

		pos.worldPos = onePos;

		camera->DrawUI(pos, tex[one], 0, lowColor);
	}


	pos.worldPos = perPos;

	camera->DrawUI(pos, perTex, 0, color);

	pos.worldPos = hundreadPos;

	camera->DrawUI(messagePos, message, 0, color);
}
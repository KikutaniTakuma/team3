#include "BrokenHud.hpp"
#include "Game/MapChip/MapChip.h"
#include "Game/MyMath/MyMath.h"

float BrokenHud::broknePer = 100.0f;

BrokenHud::BrokenHud(Camera* camera):
	Object(camera),
	deadline(70.0f),
	color(MyMath::GetRGB(255,255,255,255)),
	lowColor(MyMath::GetRGB(255,0,0,255))
{
	tex.insert(std::make_pair(0, Texture("./Resources/number/0.png", 32, 32, 32)));
	tex.insert(std::make_pair(1, Texture("./Resources/number/1.png", 32, 32, 32)));
	tex.insert(std::make_pair(2, Texture("./Resources/number/2.png", 32, 32, 32)));
	tex.insert(std::make_pair(3, Texture("./Resources/number/3.png", 32, 32, 32)));
	tex.insert(std::make_pair(4, Texture("./Resources/number/4.png", 32, 32, 32)));
	tex.insert(std::make_pair(5, Texture("./Resources/number/5.png", 32, 32, 32)));
	tex.insert(std::make_pair(6, Texture("./Resources/number/6.png", 32, 32, 32)));
	tex.insert(std::make_pair(7, Texture("./Resources/number/7.png", 32, 32, 32)));
	tex.insert(std::make_pair(8, Texture("./Resources/number/8.png", 32, 32, 32)));
	tex.insert(std::make_pair(9, Texture("./Resources/number/9.png", 32, 32, 32)));

	pos.Set(Vector2D(50.0f, 670.0f), Vector2D(64.0f,64.0f));
}

void BrokenHud::Update() {
	broknePer = (MapChip::GetBlockBreakPer() - deadline) / (100.0f - deadline) * 100.0f;
}


void BrokenHud::Draw() {
	int one = static_cast<int>(broknePer) - (static_cast<int>(broknePer) / 10) * 10;
	int ten = (static_cast<int>(broknePer) / 10);
	int hundread = (static_cast<int>(broknePer) / 100);

	if (one < 0) {
		one = 0;
	}
	if (ten < 0) {
		ten = 0;
	}
	if (hundread < 0) {
		hundread = 0;
	}

	Vector2D  hundreadPos = pos.worldPos;
	Vector2D tenPos = { pos.worldPos.x + pos.getSize().x + 5.0f, pos.worldPos.y};
	Vector2D onePos = { tenPos.x + pos.getSize().x + 5.0f, pos.worldPos.y };

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

	pos.worldPos = hundreadPos;
}
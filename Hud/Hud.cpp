#include "Hud.hpp"
#include "Game/MyMath/MyMath.h"
#include "Game/KeyInput/KeyInput.h"

Hud::Hud(Camera* camera):
	Object(camera),
	nmlColor(MyMath::GetRGB(200,200,200,0xff)),
	pushColor(MyMath::GetRGB(0xff, 0xa5, 0x00, 0xff))
{
	tex.insert(std::make_pair(0, Texture("./Resources/WASD/W.png", 64, 64, 64)));
	tex.insert(std::make_pair(1, Texture("./Resources/WASD/A.png", 64, 64, 64)));
	tex.insert(std::make_pair(2, Texture("./Resources/WASD/S.png", 64, 64, 64)));
	tex.insert(std::make_pair(3, Texture("./Resources/WASD/D.png", 64, 64, 64)));

	pos.Set(Vector2D(130.0f, 50.0f), Vector2D());

	wasdPos.insert(std::make_pair(0, Quad(Vector2D(pos.worldPos.x, pos.worldPos.y + 74.0f), Vector2D(64.0f,64.0f))));
	wasdPos.insert(std::make_pair(1, Quad(Vector2D(pos.worldPos.x - 74.0f, pos.worldPos.y), Vector2D(64.0f, 64.0f))));
	wasdPos.insert(std::make_pair(2, Quad(Vector2D(pos.worldPos), Vector2D(64.0f, 64.0f))));
	wasdPos.insert(std::make_pair(3, Quad(Vector2D(pos.worldPos.x + 74.0f, pos.worldPos.y), Vector2D(64.0f, 64.0f))));

}

void Hud::Update() {
}

void Hud::Draw() {
	if (KeyInput::getKeys(DIK_W)) {
		camera->DrawUI(wasdPos[0], tex[0], 0, pushColor);
	}
	else {
		camera->DrawUI(wasdPos[0], tex[0], 0,nmlColor);
	}
	if (KeyInput::getKeys(DIK_A)) {
		camera->DrawUI(wasdPos[1], tex[1], 0, pushColor);
	}
	else {
		camera->DrawUI(wasdPos[1], tex[1], 0, nmlColor);
	}
	if (KeyInput::getKeys(DIK_S)) {
		camera->DrawUI(wasdPos[2], tex[2], 0, pushColor);
	}
	else {
		camera->DrawUI(wasdPos[2], tex[2], 0, nmlColor);
	}
	if (KeyInput::getKeys(DIK_D)) {
		camera->DrawUI(wasdPos[3], tex[3], 0, pushColor);
	}
	else {
		camera->DrawUI(wasdPos[3], tex[3], 0, nmlColor);
	}

}
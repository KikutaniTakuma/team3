#include "Button/Button.h"
#include "Game/MyMath/MyMath.h"
#include <Novice.h>

#include "Game/MapChip/MapChip.h"
#include "Game/Texture/Texture.h"

Button::Button(Camera* camera) : Object(camera) {
	isPushButton = false;
//	buttonTexture = whiteBox;
	buttonTexture.Set("./Resources/white1x1.png", 1, 1, 1);
	pos.Set({ 0.0f,0.0f }, /*{ (float)MapChip::kMapSize,(float)MapChip::kMapSize }*/{ 32.0f,32.0f });
}

void Button::Collision(Quad playerPos) {
	//	Õ“Ë”»’è
	if (pos.Collision(playerPos))
	{
		isPushButton = true;
	}
}

bool Button::getPushButton() {
	return this->isPushButton;
}

void Button::setPos(Vector2D pos) {
	this->pos.worldPos = pos;
}

Vector2D Button::getPos() {
	return this->pos.worldPos;
}

void Button::Update() {

}

void Button::Reset() {
	isPushButton = false;
}

void Button::Draw() {
	if (isPushButton)
	{
		camera->DrawQuad(pos, buttonTexture, 0, true, 0xff0000ff);
	}
	else
	{
		camera->DrawUI(pos, buttonTexture, 0, true, 0xff0000ff);
		camera->DrawQuad(pos, buttonTexture, 0, true, 0x0000ffff);
	}
}
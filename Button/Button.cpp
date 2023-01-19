#include "Button/Button.h"
#include "Game/MyMath/MyMath.h"
#include <Novice.h>

#include "Game/MapChip/MapChip.h"
#include "Game/Texture/Texture.h"

Button::Button(Camera* camera) : Object(camera) {
	isPushButton = false;

	pos.Set({ 0.0f,0.0f }, { (float)MapChip::kMapSize,(float)MapChip::kMapSize });
}

void Button::Collision(Vector2D playerPos,Vector2D playerSize) {
	//	Õ“Ë”»’è
	if (MyMath::CollisionRectangle(this->pos.worldPos, this->pos.getSize(), playerPos, playerSize))
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

}

void Button::Draw(class Texture& tex) {

}
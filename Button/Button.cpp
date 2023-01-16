#include "Button/Button.h"
#include "Game/MyMath/MyMath.h"

Button::Button() {
	isPushButton = false;
	pos = { 0.0f,0.0f };
	size = { 32.0f,32.0f };
}

void Button::Collision(Vector2D playerPos,Vector2D playerSize) {
	//	Õ“Ë”»’è
	if (MyMath::CollisionRectangle(this->pos, this->size, playerPos, playerSize))
	{
		isPushButton = true;
	}
}

bool Button::getPushButton() {
	return this->isPushButton;
}

void Button::setPos(Vector2D pos) {
	this->pos = pos;
}

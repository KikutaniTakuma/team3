#include "Game/Object/Object.h"

Texture Object::whiteBox = Texture();

Object::Object(Camera* camera)
	:camera(camera),
	pos(Quad())
{
	if (!whiteBox) {
		whiteBox.Set("./Resources/white1x1.png", 1, 1, 1);
	}
}

void Object::BeginProcess() {
	drawPos = pos;
}

Quad Object::getPos() const {
	return pos;
}
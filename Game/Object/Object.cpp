#include "Game/Object/Object.h"

Object::Object(Camera* camera)
	:camera(camera)
{}

void Object::BeginProcess() {
	drawPos = pos;
}
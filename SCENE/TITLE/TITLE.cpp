#include "SCENE/TITLE/TITLE.h"

Title::Title(Camera* camera) : Object(camera) {
	pos.Set({ 640.0f,360.0f }, { 1280.0f,720.0f });
}

Title::~Title() {

}

void Title::Update() {
	pos.worldMatrix.Translate(pos.worldPos);
}

void Title::Reset() {

}

void Title::Draw(Texture& tex) {
//	camera->DrawQuad(drawPos, tex, 0, false);
	camera->DrawUI(drawPos, tex, 0, false, 0x991111ff);
}
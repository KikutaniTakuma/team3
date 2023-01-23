#include "SCENE/TITLE/TITLE.h"

Title::Title(Camera* camera) : Object(camera) {
	pos.Set({ 0.0f,0.0f }, { 1200.0f,700.0f });
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
	camera->DrawUI(drawPos, tex, 0, false, 0xff0000ff);
}
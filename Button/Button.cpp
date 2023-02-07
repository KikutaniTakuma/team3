#include "Button/Button.h"
#include "Game/MyMath/MyMath.h"
#include <Novice.h>

#include "Game/MapChip/MapChip.h"
#include "Game/Texture/Texture.h"

Button::Button(Camera* camera) : 
	Object(camera),
	buttonSE(Sound("./Resources/PushButtonSE.wav", false)),
	seVolum(0.5f),
	seFlg(false)
{
	isPushButton = false;
//	buttonTexture = whiteBox;
	onButtonTexture.Set("./Resources/ButtonOn.png", 192, 32, 38);
	offButtonTexture.Set("./Resources/ButtonOff.png", 32, 32, 32);
	pos.Set({ 0.0f,0.0f }, { (float)MapChip::kMapSize,(float)MapChip::kMapSize });
}

void Button::Collision(Quad playerPos) {
	//	Õ“Ë”»’è
	if (pos.Collision(playerPos) && !isPushButton)
	{
		isPushButton = true;
		seFlg = true;
		MapChip::LocalReload(pos.worldPos);
	}
	else {
		seFlg = false;
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
	pos.Translate();
}

void Button::Reset() {
	isPushButton = false;
}

void Button::Draw() {
	if (isPushButton)
	{
		camera->DrawQuad(pos, onButtonTexture, 4.0f, 0xffffffff);
	}
	else
	{
		camera->DrawQuad(pos, offButtonTexture, 0.0f, 0xffffffff);
	}
	if (seFlg) {
		buttonSE.SoundEffect(seVolum);
	}
}
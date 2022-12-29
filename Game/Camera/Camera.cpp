#include "Game/Camera/Camera.h"
#include "Game/Frame/Frame.h"
#include "Game/Texture/Texture.h"
#include "Game/Quad/Quad.h"
#include "Game/MapChip/MapChip.h"
#include "Game/MyMath/MyMath.h"
#include "Game/KeyInput/KeyInput.h"

#include <Novice.h>

#include <time.h>
#include <stdlib.h>
#include <limits.h>

Camera::Camera() {
	worldPos = { static_cast<float>(MapChip::kWindowWidth) / 2.0f, static_cast<float>(MapChip::kWindowHeight) / 2.0f };
	screenPos = { 0.0f,0.0f };

	drawLeftTop = { static_cast<float>(MapChip::kWindowWidth) / -2.0f, static_cast<float>(MapChip::kWindowHeight) / 2.0f };
	drawRightBottom = { static_cast<float>(MapChip::kWindowWidth) / 2.0f, static_cast<float>(MapChip::kWindowHeight) / -2.0f };

	size = { static_cast<float>(MapChip::kWindowWidth), static_cast<float>(MapChip::kWindowHeight) };
	scale = 1.0f;

	viewMatrix.Translate(worldPos);
	viewMatrix.Inverse();

	NorDevMatrix.Orthographic(drawLeftTop, drawRightBottom);

	viewPortMatrix.Viewport(screenPos, size);

	frame = new Frame;
	frame->Restart();

	shakeScale = { 10.0f, 10.0f };
}

Camera::~Camera(){
	delete frame;
}

void Camera::Update() {
	/// 操作説明
	/// ↑→↓←でカメラを移動
	/// Lshift + ↑→↓←でカメラ内のワールド座標を移動
	/// Lctrl + ↑→↓←でカメラの移す範囲の左上座標を移動
	/// Lalt + ↑→↓←でカメラの移す範囲の右下座標を移動
	/// PGUP でアップ
	/// PGDN で引き
	/// Lshift + PGUP でカメラ内のアップ
	/// Lshift + PGDN でカメラ内の引き
	/// Lshift + Rshift でシェイク
	
	if (KeyInput::getKeys(DIK_LCONTROL)) {
		if (KeyInput::getKeys(DIK_UP)) {
			drawLeftTop.y += 5.0f;
		}
		if (KeyInput::getKeys(DIK_DOWN)) {
			drawLeftTop.y -= 5.0f;
		}
		if (KeyInput::getKeys(DIK_RIGHT)) {
			drawLeftTop.x += 5.0f;
		}
		if (KeyInput::getKeys(DIK_LEFT)) {
			drawLeftTop.x -= 5.0f;
		}
	}
	else if (KeyInput::getKeys(DIK_LALT)) {
		if (KeyInput::getKeys(DIK_UP)) {
			drawRightBottom.y += 5.0f;
		}
		if (KeyInput::getKeys(DIK_DOWN)) {
			drawRightBottom.y -= 5.0f;
		}
		if (KeyInput::getKeys(DIK_RIGHT)) {
			drawRightBottom.x += 5.0f;
		}
		if (KeyInput::getKeys(DIK_LEFT)) {
			drawRightBottom.x -= 5.0f;
		}
	}
	else if (KeyInput::getKeys(DIK_LSHIFT)) {
		if (KeyInput::getKeys(DIK_UP)) {
			worldPos.y += 5.0f;
		}
		if (KeyInput::getKeys(DIK_DOWN)) {
			worldPos.y -= 5.0f;
		}
		if (KeyInput::getKeys(DIK_RIGHT)) {
			worldPos.x += 5.0f;
		}
		if (KeyInput::getKeys(DIK_LEFT)) {
			worldPos.x -= 5.0f;
		}
	}
	else {
		if (KeyInput::getKeys(DIK_UP)) {
			screenPos.y += 5.0f;
		}
		if (KeyInput::getKeys(DIK_DOWN)) {
			screenPos.y -= 5.0f;
		}
		if (KeyInput::getKeys(DIK_RIGHT)) {
			screenPos.x += 5.0f;
		}
		if (KeyInput::getKeys(DIK_LEFT)) {
			screenPos.x -= 5.0f;
		}
	}

	if (KeyInput::getKeys(DIK_LSHIFT)) {
		if (KeyInput::getKeys(DIK_PGUP)) {
			drawLeftTop.x += 5.0f;
			drawLeftTop.y -= 2.8125f;
			drawRightBottom.x -= 5.0f;
			drawRightBottom.y += 2.8125f;
		}
		else if (KeyInput::getKeys(DIK_PGDN)) {
			drawLeftTop.x -= 5.0f;
			drawLeftTop.y += 2.8125f;
			drawRightBottom.x += 5.0f;
			drawRightBottom.y -= 2.8125f;
		}
	}
	else {
		if (KeyInput::Pushed(DIK_PGUP)) {
			scale += 0.1f;
		}
		else if (KeyInput::Pushed(DIK_PGDN)) {
			scale -= 0.1f;
		}
	}

	if (KeyInput::getKeys(DIK_LSHIFT) && KeyInput::getKeys(DIK_RSHIFT)) {
		Vector2D tmp = this->worldPos;

		Shake();
		viewMatrix.Translate(this->worldPos);
		viewMatrix.Inverse();

		worldPos = tmp;
	}
	else {
		viewMatrix.Translate(this->worldPos);
		viewMatrix.Inverse();
	}

	
	NorDevMatrix.Orthographic(drawLeftTop / scale, drawRightBottom / scale);
	viewPortMatrix.Viewport(screenPos, size);

	vpvpMatrix = viewMatrix * NorDevMatrix * viewPortMatrix;

	frame->Start();
	if (frame->frame > ULLONG_MAX) {
		frame->Stop();
		frame->Restart();
	}
}

void Camera::Update(const Vector2D& worldPos, const Vector2D& cameraPos, const float& scale, const bool& shake) {
	frame->Start();
	if (frame->frame > ULLONG_MAX) {
		frame->Stop();
		frame->Restart();
	}

	this->scale = scale;

	this->worldPos = worldPos;

	// もしシェイクフラグがオンなら
	if (shake) {
		Shake();
	}

	viewMatrix.Translate(this->worldPos);
	viewMatrix.Inverse();
	NorDevMatrix.Orthographic(size / this->scale);
	viewPortMatrix.Viewport(cameraPos, size);

	vpvpMatrix = viewMatrix * NorDevMatrix * viewPortMatrix;
}

void Camera::Update(const Vector2D& worldPos, const Vector2D& cameraPos, const Vector2D& drawLeftTop, const Vector2D& drawRightBottom, const bool& shake) {
	frame->Start();
	if (frame->frame > ULLONG_MAX) {
		frame->Stop();
		frame->Restart();
	}

	this->worldPos = worldPos;

	// もしシェイクフラグがオンなら
	if (shake) {
		Shake();
	}
	this->drawLeftTop = drawLeftTop;
	this->drawRightBottom = drawRightBottom;

	viewMatrix.Translate(this->worldPos);
	viewMatrix.Inverse();
	NorDevMatrix.Orthographic(this->drawLeftTop, this->drawRightBottom);
	viewPortMatrix.Viewport(cameraPos, size);

	vpvpMatrix = viewMatrix * NorDevMatrix * viewPortMatrix;
}


void Camera::Shake() {
	worldPos.x += static_cast<float>((rand() % static_cast<int>(shakeScale.x))) - shakeScale.x / 2.0f;
	worldPos.y += static_cast<float>((rand() % static_cast<int>(shakeScale.y))) - shakeScale.y / 2.0f;
}

void Camera::DrawQuad(Quad quad, Texture& texture, const int& animationSpd, const bool& animationStop, const unsigned int& color) const {
	if (isDraw(quad.worldPos)) {
		quad.worldMatrix *= vpvpMatrix;

		if (!animationStop && animationSpd != 0) {
			if (frame->frame % animationSpd == 0) {
				texture.drawPos += texture.width;
				if (texture.drawPos > texture.spriteSize - texture.width) {
					texture.drawPos = 0;
				}
			}
		}

		Novice::DrawQuad(
			static_cast<int>(quad.getMatrixLeftTop().x), static_cast<int>(quad.getMatrixLeftTop().y),
			static_cast<int>(quad.getMatrixRightTop().x), static_cast<int>(quad.getMatrixRightTop().y),
			static_cast<int>(quad.getMatrixLeftUnder().x), static_cast<int>(quad.getMatrixLeftUnder().y),
			static_cast<int>(quad.getMatrixRightUnder().x), static_cast<int>(quad.getMatrixRightUnder().y),
			texture.drawPos, 0, texture.width, texture.height, texture.textureHandle, color
		);
	}
}

void Camera::DrawQuad(Quad quad, Texture& texture, float deg, const int& animationSpd, const bool& animationStop, const unsigned int& color) const {
	if (isDraw(quad.worldPos)) {
		quad.worldMatrix *= vpvpMatrix;

		if (!animationStop && animationSpd != 0) {
			if (frame->frame % animationSpd == 0) {
				texture.drawPos += texture.width;
				if (texture.drawPos > texture.spriteSize - texture.width) {
					texture.drawPos = 0;
				}
			}
		}

		Novice::DrawQuad(
			static_cast<int>(quad.getMatrixLeftTop().x), static_cast<int>(quad.getMatrixLeftTop().y),
			static_cast<int>(quad.getMatrixRightTop().x), static_cast<int>(quad.getMatrixRightTop().y),
			static_cast<int>(quad.getMatrixLeftUnder().x), static_cast<int>(quad.getMatrixLeftUnder().y),
			static_cast<int>(quad.getMatrixRightUnder().x), static_cast<int>(quad.getMatrixRightUnder().y),
			texture.drawPos, 0, texture.width, texture.height, texture.textureHandle, color
		);
	}
}


void Camera::DrawUI(Quad quad, Texture& texture, const int& animationSpd, const bool& animationStop, const unsigned int& color) const {
	Matrix3x3 mat;
	mat.Translate(worldPos);
	quad.worldMatrix *= mat * vpvpMatrix;

	if (!animationStop && animationSpd != 0) {
		if (frame->frame % animationSpd == 0) {
			texture.drawPos += texture.width;
			if (texture.drawPos > texture.spriteSize - texture.width) {
				texture.drawPos = 0;
			}
		}
	}

	Novice::DrawQuad(
		static_cast<int>(quad.getMatrixLeftTop().x), static_cast<int>(quad.getMatrixLeftTop().y),
		static_cast<int>(quad.getMatrixRightTop().x), static_cast<int>(quad.getMatrixRightTop().y),
		static_cast<int>(quad.getMatrixLeftUnder().x), static_cast<int>(quad.getMatrixLeftUnder().y),
		static_cast<int>(quad.getMatrixRightUnder().x), static_cast<int>(quad.getMatrixRightUnder().y),
		texture.drawPos, 0, texture.width, texture.height, texture.textureHandle, color
	);
}


bool Camera::isDraw(Vector2D pos, const float& drawLength) const {
	pos -= worldPos;
	if (pos.x < drawLeftTop.x - drawLength || pos.x > drawRightBottom.x + drawLength ||
		pos.y > drawLeftTop.y + drawLength || pos.y < drawRightBottom.y - drawLength) {
		return false;
	}
	else {
		return true;
	}
}

Vector2D Camera::getPos() const {
	return worldPos;
}

Vector2D Camera::getDrawLeftTop() const {
	return drawLeftTop;
}
Vector2D Camera::getDrawRightBottom() const {
	return drawRightBottom;
}
Vector2D Camera::getDrawSize() const {
	return size;
}
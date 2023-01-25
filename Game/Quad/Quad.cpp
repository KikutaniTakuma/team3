#include "Quad.h"
#include "Game/Matrix3x3/Matrix3x3.h"
#include "Game/MapChip/MapChip.h"
#include "Game/MyMath/MyMath.h"

Quad::Quad() {}

Quad::Quad(const Vector2D& worldPos, const Vector2D& size) {
	this->size = size;

	this->leftTop = { -1.0f * size.x / 2.0f, size.y / 2.0f };
	this->leftUnder = { -1.0f * size.x / 2.0f,  -1.0f * size.y / 2.0f };
	this->rightTop = size / 2.0f;
	this->rightUnder = { size.x / 2.0f, -1.0f * size.y / 2.0f };

	this->worldPos = worldPos;

	this->worldMatrix.Affin({1.0f,1.0f},0.0f, worldPos);
}

Quad::Quad(const Quad& quad) {
	*this = quad;
}

Quad::Quad(Vector2D&& worldPos, Vector2D&& size) {
	this->size = size;

	this->leftTop = { -1.0f * size.x / 2.0f, size.y / 2.0f };
	this->leftUnder = { -1.0f * size.x / 2.0f,  -1.0f * size.y / 2.0f };
	this->rightTop = size / 2.0f;
	this->rightUnder = { size.x / 2.0f, -1.0f * size.y / 2.0f };

	this->worldPos = worldPos;

	this->worldMatrix.Affin({ 1.0f,1.0f }, 0.0f, worldPos);
}

void Quad::Set(const Vector2D& worldPos, const Vector2D& size) {
	this->size = size;

	this->leftTop = { -1.0f * size.x / 2.0f, size.y / 2.0f };
	this->leftUnder = { -1.0f * size.x / 2.0f,  -1.0f * size.y / 2.0f };
	this->rightTop = size / 2.0f;
	this->rightUnder = { size.x / 2.0f, -1.0f * size.y / 2.0f };

	this->worldPos = worldPos;

	this->worldMatrix.Affin({ 1.0f,1.0f }, 0.0f, worldPos);
}

void Quad::Scale(const float& scale) {
	if (scale >= 0.0f) {
		leftTop *= scale;
		leftUnder *= scale;
		rightTop *= scale;
		rightUnder *= scale;
	}
}

void Quad::Rotate(float deg) {
	Matrix3x3 rotate;
	rotate.Rotate(deg);

	this->leftTop *= rotate;
	this->leftUnder *= rotate;
	this->rightTop *= rotate;
	this->rightUnder *= rotate;
}

const Quad& Quad::operator=(const Quad& tmp) {
	this->size = tmp.size;

	this->leftTop = tmp.getSizeLeftTop();
	this->leftUnder = tmp.getSizeLeftUnder();
	this->rightTop = tmp.getSizeRightTop();
	this->rightUnder = tmp.getSizeRightUnder();

	this->worldPos = tmp.worldPos;

	this->worldMatrix = tmp.worldMatrix;

	return *this;
}

Quad Quad::operator*(const  Matrix3x3& matrix) {
	Quad quad;

	quad.leftTop *= matrix;
	quad.leftUnder *= matrix;
	quad.rightTop *= matrix;
	quad.rightUnder *= matrix;
	
	return quad;
}

const Quad& Quad::operator*=(const  Matrix3x3& matrix) {
	this->leftTop *= matrix;
	this->leftUnder *= matrix;
	this->rightTop *= matrix;
	this->rightUnder *= matrix;

	return *this;
}

Quad Quad::operator+(const Vector2D& vec){
	Quad quad;

	quad.leftTop = leftTop + vec;

	quad.leftUnder = leftUnder + vec;

	quad.rightTop = rightTop + vec;

	quad.rightUnder = rightUnder + vec;


	quad.worldPos = worldPos+vec;

	return quad;
}

bool Quad::Collision(const Quad& tmp) {
	/*if (leftTop.x < tmp.rightTop.x && tmp.leftTop.x < rightTop.x) {
		if (leftTop.y < tmp.leftUnder.y && tmp.leftTop.y < leftUnder.y) {
			return true;
		}
	}
	return false;*/

	return MyMath::PythagoreanTheorem(abs(worldPos.x - tmp.worldPos.x), abs(worldPos.y - tmp.worldPos.y)) < MyMath::PythagoreanTheorem(size.x, size.y));
}

void Quad::Translate() {
	this->worldMatrix.Translate(worldPos);
}

void Quad::setVpvpMatrix(const Matrix3x3& tmp) {
	vpvpMatrix = tmp;
}

Vector2D Quad::getSize() const {
	return this->size;
}

Vector2D Quad::getPosLeftTop() const {
	return leftTop + worldPos;
}
Vector2D Quad::getPosLeftUnder() const {
	return leftUnder + worldPos;
}
Vector2D Quad::getPosRightTop() const {
	return rightTop + worldPos;
}
Vector2D Quad::getPosRightUnder() const {
	return rightUnder +worldPos;
}

Vector2D Quad::getMatrixLeftTop() const {
	return leftTop * worldMatrix * vpvpMatrix;
}
Vector2D Quad::getMatrixLeftUnder() const {
	return leftUnder * worldMatrix * vpvpMatrix;
}
Vector2D Quad::getMatrixRightTop() const {
	return rightTop * worldMatrix * vpvpMatrix;
}
Vector2D Quad::getMatrixRightUnder() const {
	return rightUnder * worldMatrix * vpvpMatrix;
}

const Vector2D& Quad::getSizeLeftTop() const {
	return leftTop;
}
const Vector2D& Quad::getSizeLeftUnder() const {
	return leftUnder;
}
const Vector2D& Quad::getSizeRightTop() const {
	return rightTop;
}
const Vector2D& Quad::getSizeRightUnder() const {
	return rightUnder;
}
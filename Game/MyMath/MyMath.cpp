#include "Game/MyMath/MyMath.h"
#define _USE_MATH_DEFINES
#include <cmath>
#include <random>
#include "Game/Vector2D/Vector2D.h"
#include "Game/MapChip/MapChip.h"

const int MyMath::kCoodinateChangeConstant = (MapChip::kMapHeight * MapChip::kMapSize);

void MyMath::CoordinateChange(const Vector2D& worldPos, Vector2D& screenPos) {
	screenPos.x = worldPos.x;
	screenPos.y = (worldPos.y * -1) + kCoodinateChangeConstant;
}

void MyMath::CoordinateChange(Vector2D& worldPos) {
	worldPos.y = (worldPos.y * -1) + kCoodinateChangeConstant;
}

void MyMath::CoordinateChange(Vector2D& worldPos, const int coordinateChangeConstant) {
	worldPos.y = (worldPos.y * -1) + coordinateChangeConstant;
}

void MyMath::CoordinateChange(int& worldPos) {
	worldPos = (worldPos * -1) + kCoodinateChangeConstant;
}

bool MyMath::CollisionRectangle(Vector2D LeftTop1, Vector2D size1, Vector2D LeftTop2, Vector2D size2) {
	if (LeftTop1.x < LeftTop2.x + size2.x && LeftTop2.x < LeftTop1.x + size1.x) {
		if (LeftTop1.y < LeftTop2.y - size2.y && LeftTop2.y < LeftTop1.y - size1.y) {
			return true;
		}
	}
	return false;
}

bool MyMath::CollisionRectangle(int LeftTopX1, int LeftTopY1, int sizeX1, int sizeY1, int LeftTopX2, int LeftTopY2, int sizeX2, int sizeY2) {
	if (LeftTopX1 < LeftTopX2 + sizeX2 && LeftTopX2 < LeftTopX1 + sizeX1) {
		if (LeftTopY1 < LeftTopY2 + sizeY2 && LeftTopY2 < LeftTopY1 + sizeY1) {
			return true;
		}
	}
	return false;
}

float MyMath::PythagoreanTheorem(const float& x, const float& y) {
	return sqrtf(powf(x, 2.0f) + powf(y, 2.0f));
}

float MyMath::Normalize(const float& x, const float& y) {
	return x / MyMath::PythagoreanTheorem(x, y);
}

Vector2D MyMath::Normalize(Vector2D vec) {
	vec.x /= MyMath::PythagoreanTheorem(vec.x, vec.y);
	vec.y /= MyMath::PythagoreanTheorem(vec.y, vec.x);

	return vec;
}

void MyMath::BubbleSort(int* data, int arr, bool order) {
	for (int i = 0; i < arr - 1; i++) {
		for (int j = arr - 1; j > i; j--) {
			if (order == true) {
				if (data[j - 1] > data[j]) {
					MyMath::Tmp(data[j], data[j - 1]);
				}
			}
			else if (order == false) {
				if (data[j - 1] < data[j]) {
					MyMath::Tmp(data[j], data[j - 1]);
				}
			}
		}
	}
}

float MyMath::Dot(const Vector2D& vec1, const Vector2D& vec2) {
	return (vec1.x * vec2.x) + (vec1.y * vec2.y);
}

bool MyMath::Cross(const Vector2D& vec1, const Vector2D& vec2) {
	return (vec1.x * vec2.y) - (vec1.y * vec2.x) >= 0 ? true : false;
}

float MyMath::ToRad(const float& deg) {
	return deg * static_cast<float>(M_PI) / 180.0f;
}

float MyMath::ToDeg(const float& rad) {
	return rad * 180.0f / static_cast<float>(M_PI);
}

bool MyMath::isAngle(float deg, float maxDeg, float minDeg) {
	return deg < maxDeg && deg > minDeg;
}

float MyMath::GetAngle(Vector2D pos, Vector2D origin) {
	return MyMath::ToDeg(atan2f(pos.y - origin.y, pos.x - origin.x));
}

float MyMath::Clamp(float num,float max,float min)
{
	if (num < min) {
		return num = min;
	}
	else if(num>max){
		return num = max;
	}
	return num;
}

unsigned int MyMath::GetRGB(unsigned int red, unsigned int green, unsigned int blue, unsigned int alpha) {
	return (red << 24) + (green << 16) + (blue << 8) + alpha;
}

int MyMath::Random(int min, int max) {
	std::random_device rnd;

	if (min > max) {
		Swap(min, max);
	}

	const int&& num = abs(max + 1) + abs(min);

	return (rnd() % num) + min;
}

bool MyMath::Capsule(Vector2D pos, Vector2D start, Vector2D end, float size) {

}
#include "MapChip.h"
#include <Novice.h>
#include "Game/Texture/Texture.h"
#include "Game/Vector2D/Vector2D.h"
#include "Game/MyMath/MyMath.h"
#include "Game/Quad/Quad.h"
#include "Game/Camera/Camera.h"

#include "Game/IOcsv/IOcsv.h"

std::vector<int> MapChip::data;
const int MapChip::kMapSize = 32;
const int MapChip::kWindowWidth = 1280;
const int MapChip::kWindowHeight = 720;
const int MapChip::kStageNumberWidth = 6;
const int MapChip::kStageNumberHeight = 11;
const int MapChip::kMapWidth = 199;
const int MapChip::kMapHeight = 200;
const Camera* MapChip::camera = nullptr;

void MapChip::Initilize() {
	MapChip::data.resize(MapChip::kMapHeight * MapChip::kMapWidth);

	IOcsv::Input("./Data/mappu2_-_1.csv", MapChip::data);
}
void MapChip::SetCamera(Camera* cameraPointa) {
	camera = cameraPointa;
}

void MapChip::Finalize() {
}

void MapChip::Reset() {
	IOcsv::Input("./Data/mappu2_-_1.csv", MapChip::data);
}


bool  MapChip::Collision(const Vector2D& pos) {
	if (GetType(pos) == (int)MapChip::Type::BLOCK) {
		return true;
	}
	else if(GetType(pos) == (int)MapChip::Type::NONE) {
		return false;
	}
	else {
		return false;
	}
}

int MapChip::GetType(Vector2D worldPos) {
	MyMath::CoordinateChange(worldPos);

	int y = (int)worldPos.y / MapChip::kMapSize;
	int x = (int)worldPos.x / MapChip::kMapSize;

	MyMath::CoordinateChange(worldPos);

	if (x >= MapChip::kMapWidth || y >= MapChip::kMapHeight || x < 0 || y < 0) {
		return (int)MapChip::Type::NONE;
	}
	else {
		return data[y * MapChip::kMapWidth + x];
	}
}

Vector2D MapChip::GetPos(Vector2D worldPos) {
	Vector2D mapChipPos;
	mapChipPos.x = (float)(static_cast<int>(worldPos.x) / kMapSize) * kMapSize;
	mapChipPos.y = (float)(static_cast<int>(worldPos.y - 1.0f) / kMapSize) * kMapSize;
	return mapChipPos;
}

Vector2D MapChip::GetNum(Vector2D worldPos) {
	MyMath::CoordinateChange(worldPos);
	Vector2D mapChipPos;
	mapChipPos.x = static_cast<float>((static_cast<int>(worldPos.x) / kMapSize));
	mapChipPos.y = static_cast<float>((static_cast<int>(worldPos.y - 1.0f) / kMapSize));
	return mapChipPos;
}


void MapChip::Draw(Texture& texture) {
	int x = 0;
	int y = 0;
	Quad quad({ 0.0f,0.0f }, { kMapSize, kMapSize });

	for (y = MapChip::kMapHeight - 1; y >= 0; y--) {
		for (x = 0; x < MapChip::kMapWidth; x++) {
			quad.worldPos = { static_cast<float>((x * kMapSize) + kMapSize / 2), static_cast<float>((y * kMapSize) + kMapSize / 2) };
			MyMath::CoordinateChange(quad.worldPos);
			quad.worldMatrix.Translate(quad.worldPos);

			if (!camera->isDraw(quad.worldPos))
			{
				continue;
			}

			switch (data[y * MapChip::kMapWidth + x]) {
			case (int)MapChip::Type::NONE:
				camera->DrawQuad(quad, texture, 0, false, BLACK);

				break;
			case (int)MapChip::Type::BLOCK:
				camera->DrawQuad(quad, texture, 0, false, WHITE);

				break;

			case (int)MapChip::Type::Closed:
				camera->DrawQuad(quad, texture, 0, false, MyMath::GetRGB(122,122,122,0xff));

				break;

			case (int)MapChip::Type::Open:
				camera->DrawQuad(quad, texture, 0, false, MyMath::GetRGB(255, 255, 0, 0xff));

				break;

			case (int)MapChip::Type::Short:
				camera->DrawQuad(quad, texture, 0, false, MyMath::GetRGB(255, 0, 0, 0xff));

				break;

			default:
				camera->DrawQuad(quad, texture, 0, false, BLACK);

				break;
			}
		}
	}
}

void MapChip::Collision(Quad& pos, Vector2D& moveVec) {
	// 1, 進んでいる方向に当たり判定のオブジェクトがあるかどうか
	// カプセル処理(だるい上に計算量多い)
	// 移動前の移動方向に一番近いオブジェクトがあたっているかどうか



	// 2, あったら移動上にある一番近いオブジェクトの位置に移動
	// オブジェクトの位置に移動

	// 3, 移動ベクトルを正規化して反対ベクトルをとる

	// 4, Quadの大きさベクトルとマップチップの大きさベクトルと反対ベクトルを掛ける

	// 5, 掛けたそれぞれのベクトルを足したものを移動ベクトルを掛ける
}

void MapChip::LoadMap(std::string fileName) {
	IOcsv::Input(fileName.c_str(), MapChip::data);
}


int MapChip::getData(const int& x, const int& y) {
	return data[y * MapChip::kMapWidth + x];
}

void MapChip::setData(int num, const int& x, const int& y) {
	if (num >= (int)Type::kMaxNum) { num = 0; }

	data[y * MapChip::kMapWidth + x] = num;
}
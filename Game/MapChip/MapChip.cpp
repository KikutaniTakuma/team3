#include "MapChip.h"
#include <Novice.h>
#include "Game/Texture/Texture.h"
#include "Game/Vector2D/Vector2D.h"
#include "Game/MyMath/MyMath.h"
#include "Game/Quad/Quad.h"
#include "Game/Camera/Camera.h"

#include "Game/IOcsv/IOcsv.h"
#include "Enemy/Enemy.h"

#include <fstream>
#include <sstream>
#include <algorithm>

std::vector<int> MapChip::data = std::vector<int>(0);
const int MapChip::kMapSize = 32;
const int MapChip::kWindowWidth = 1280;
const int MapChip::kWindowHeight = 720;
int MapChip::coodinateChangeConstant = 0;

int MapChip::mapWidth = 0; //199
int MapChip::mapHeight = 0;//200
float MapChip::mapMaxPosX = static_cast<float>((MapChip::mapWidth - 1) * MapChip::kMapSize);
float MapChip::mapMaxPosY = static_cast<float>((MapChip::mapHeight - 1) * MapChip::kMapSize);
float MapChip::mapMinPosX = static_cast<float>(MapChip::kMapSize);
float MapChip::mapMinPosY = static_cast<float>(MapChip::kMapSize);

const Camera* MapChip::camera = nullptr;
Quad MapChip::pos;
Vector2D MapChip::plyPos = Vector2D();
std::vector<Vector2D> MapChip::emyPos = std::vector<Vector2D>(0);
Vector2D MapChip::goalPos = Vector2D();
std::vector<Vector2D> MapChip::buttonPos = std::vector<Vector2D>(0);

Texture MapChip::block = Texture();
Texture MapChip::tile = Texture();


void MapChip::Initilize() {
	MapChip::LoadMap("./Data/mappu2_-_1.csv");//./Data/MapChipData.csv

	mapMaxPosX = static_cast<float>((MapChip::mapWidth - 1) * MapChip::kMapSize);
	mapMaxPosY = static_cast<float>((MapChip::mapHeight - 1) * MapChip::kMapSize);
	mapMinPosX = static_cast<float>(MapChip::kMapSize);
	mapMinPosY = static_cast<float>(MapChip::kMapSize);

	for (int y = 0; y < mapHeight; y++) {
		for (int x = 0; x < mapWidth; x++) {
			if (data[y * MapChip::mapWidth + x] == 55) {
				data[y * MapChip::mapWidth + x] = 0;
				plyPos = Vector2D(static_cast<float>(x * MapChip::kMapSize + (MapChip::kMapSize / 2)), CoordinateChange(static_cast<float>(y * MapChip::kMapSize) + static_cast<float>(MapChip::kMapSize / 2)));
			}
			if (data[y * MapChip::mapWidth + x] == 56) {
				data[y * MapChip::mapWidth + x] = 0;
				emyPos.push_back(Vector2D(static_cast<float>(x * MapChip::kMapSize) + (MapChip::kMapSize / 2), CoordinateChange(static_cast<float>(y * MapChip::kMapSize) + static_cast<float>(MapChip::kMapSize / 2))));
			}
			if (data[y * MapChip::mapWidth + x] == 50) {
				data[y * MapChip::mapWidth + x] = 1;
				goalPos = Vector2D(static_cast<float>(x * MapChip::kMapSize) + (MapChip::kMapSize / 2), CoordinateChange(static_cast<float>(y * MapChip::kMapSize) + static_cast<float>(MapChip::kMapSize / 2)));
			}
			if (data[y * MapChip::mapWidth + x] == 51) {
				data[y * MapChip::mapWidth + x] = 0;
				buttonPos.push_back(Vector2D(static_cast<float>(x * MapChip::kMapSize) + (MapChip::kMapSize / 2), CoordinateChange(static_cast<float>(y * MapChip::kMapSize) + static_cast<float>(MapChip::kMapSize / 2))));
			}
		}
	}

	block.Set("./Resources/Block.png", 64, 64, 64);
	tile.Set("./Resources/Tile.png", 32, 32, 32);
}
void MapChip::SetCamera(Camera* cameraPointa) {
	camera = cameraPointa;
}

void MapChip::Finalize() {
}

void MapChip::Reset() {
	MapChip::LoadMap("./Data/mappu2_-_1.csv");

	mapMaxPosX = static_cast<float>((MapChip::mapWidth - 1) * MapChip::kMapSize);
	mapMaxPosY = static_cast<float>((MapChip::mapHeight - 1) * MapChip::kMapSize);
	mapMinPosX = static_cast<float>(MapChip::kMapSize);
	mapMinPosY = static_cast<float>(MapChip::kMapSize);

	for (int y = 0; y < mapHeight; y++) {
		for (int x = 0; x < mapWidth; x++) {
			if (data[y * MapChip::mapWidth + x] == 55) {
				data[y * MapChip::mapWidth + x] = 0;
				plyPos = Vector2D(static_cast<float>(x * MapChip::kMapSize + (MapChip::kMapSize / 2)), CoordinateChange(static_cast<float>(y * MapChip::kMapSize) + static_cast<float>(MapChip::kMapSize / 2)));
			}
			if (data[y * MapChip::mapWidth + x] == 56) {
				data[y * MapChip::mapWidth + x] = 0;
				emyPos.push_back(Vector2D(static_cast<float>(x * MapChip::kMapSize) + (MapChip::kMapSize / 2), CoordinateChange(static_cast<float>(y * MapChip::kMapSize) + static_cast<float>(MapChip::kMapSize / 2))));
			}
			if (data[y * MapChip::mapWidth + x] == 50) {
				data[y * MapChip::mapWidth + x] = 1;
				goalPos = Vector2D(static_cast<float>(x * MapChip::kMapSize) + (MapChip::kMapSize / 2), CoordinateChange(static_cast<float>(y * MapChip::kMapSize) + static_cast<float>(MapChip::kMapSize / 2)));
			}
			if (data[y * MapChip::mapWidth + x] == 51) {
				data[y * MapChip::mapWidth + x] = 0;
				buttonPos.push_back(Vector2D(static_cast<float>(x * MapChip::kMapSize) + (MapChip::kMapSize / 2), CoordinateChange(static_cast<float>(y * MapChip::kMapSize) + static_cast<float>(MapChip::kMapSize / 2))));
			}
		}
	}
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
	CoordinateChange(worldPos);

	int y = (int)worldPos.y / MapChip::kMapSize;
	int x = (int)worldPos.x / MapChip::kMapSize;

	if (x >= MapChip::mapWidth || y >= MapChip::mapHeight || x < 0 || y < 0) {
		return (int)MapChip::Type::NONE;
	}
	else {
		return data[y * MapChip::mapWidth + x];
	}
}

Vector2D MapChip::GetPos(Vector2D worldPos) {
	Vector2D mapChipPos;
	mapChipPos.x = (float)(static_cast<int>(worldPos.x) / kMapSize) * kMapSize;
	mapChipPos.y = (float)(static_cast<int>(worldPos.y - 1.0f) / kMapSize) * kMapSize;
	return mapChipPos;
}

Vector2D MapChip::GetNum(Vector2D worldPos) {
	CoordinateChange(worldPos);
	Vector2D mapChipPos;
	mapChipPos.x = static_cast<float>((static_cast<int>(worldPos.x) / kMapSize));
	mapChipPos.y = static_cast<float>((static_cast<int>(worldPos.y - 1.0f) / kMapSize));
	return mapChipPos;
}

void MapChip::CoordinateChange(Vector2D& worldPos) {
	worldPos.y = (worldPos.y * -1) + coodinateChangeConstant;
}

float MapChip::CoordinateChange(float worldPosY) {
	worldPosY = (worldPosY * -1) + coodinateChangeConstant;

	return worldPosY;
}


void MapChip::Draw(Texture& texture) {
	int x = 0;
	int y = 0;
	pos.Set({ 0.0f,0.0f }, { kMapSize, kMapSize });

	// カメラの映る範囲のマップチップの番号を取得
	int firstY = (static_cast<int>(camera->getPos().y) / kMapSize) + (static_cast<int>((camera->getDrawSize().y) / 2.0f) / kMapSize) + 1;
	int lastY = (static_cast<int>(camera->getDrawSize().y / 2.0f) / kMapSize) - (static_cast<int>(camera->getPos().y) / kMapSize) - 1;
	firstY += lastY + static_cast<int>(MapChip::GetNum(camera->worldPos).y);
	/*int hoge = static_cast<int>(MapChip::GetNum(camera->worldPos).y);*/
	

	if (firstY > mapHeight - 1) {
		firstY = mapHeight - 1;
	}
	if (lastY < 0) {
		lastY = 0;
	}

	int firstX = (static_cast<int>(camera->getPos().x) / kMapSize) - (static_cast<int>(camera->getDrawSize().x / 2.0f) / kMapSize) - 1;
	int lastX = (static_cast<int>(camera->getPos().x) / kMapSize) + (static_cast<int>(camera->getDrawSize().x / 2.0f) / kMapSize) + 1;

	if (firstX < 0) {
		firstX = 0;
	}
	if (lastX > mapWidth) {
		lastX = mapWidth;
	}

	for (y = firstY; y >= lastY; y--) {
		for (x = firstX; x < lastX; x++) {
	
			pos.worldPos = { static_cast<float>((x * kMapSize) + kMapSize / 2), static_cast<float>((y * kMapSize) + kMapSize / 2) };
			CoordinateChange(pos.worldPos);

			switch (data[y * MapChip::mapWidth + x]) {
			case (int)MapChip::Type::NONE:
				camera->DrawQuad(pos, tile, 0, MyMath::GetRGB(100, 100, 100, 0xff));

				break;
			case (int)MapChip::Type::BLOCK:
				camera->DrawQuad(pos, block, 0, 0x555555ff);

				break;
			case (int)MapChip::Type::BREAK:
				camera->DrawQuad(pos, texture, 0, MyMath::GetRGB(200, 200, 0, 0xff));

				break;

			case (int)MapChip::Type::SACRED:
				camera->DrawQuad(pos, texture, 0, MyMath::GetRGB(200, 200, 200, 0xff));

				break;

			/*case 4:
				camera->DrawQuad(pos, texture, 0, false, MyMath::GetRGB(200, 200, 200, 0xff));
				break;
				*/


			default:
				camera->DrawQuad(pos, tile, 0, MyMath::GetRGB(100, 100, 100, 0xff));

				break;
			}
		}
	}
}

void MapChip::CollisionBlock(Quad& pos, Vector2D& moveVec) {
	// 1, 進んでいる方向に当たり判定のオブジェクトがあるかどうか
	// 当たる可能性があるオブジェクトを選び取る関数
	/*Vector2D start = MapChip::GetNum(pos.worldPos);
	Vector2D end = MapChip::GetNum(pos.worldPos + moveVec);

	if (start.x > end.x) { MyMath::Swap(start.x, end.x); }
	if (start.y < end.y) { MyMath::Swap(start.y, end.y); }

	for (int y = start.y; y <= end.y; y++) {
		for (int x = start.x; x <= end.x; x++) {
			if (MyMath::Capsule) {
				break;
			}
		}
	}*/
	// 
	// 
	// 
	// 移動前の移動方向に一番近いオブジェクトがあたっているかどうか


	// 2, あったら移動上にある一番近いオブジェクトの位置に移動
	// オブジェクトの位置に移動


	// 3, 移動ベクトルを正規化して反対ベクトルをとる

	// 4, Quadの大きさベクトルとマップチップの大きさベクトルと反対ベクトルを掛ける

	// 5, 掛けたそれぞれのベクトルを足したものを移動ベクトルを掛ける
}

int MapChip::LoadMap(std::string fileName) {
	// ファイルバッファー(コンストラクタで開く)
	std::ifstream fileBuff(fileName);

	// もしファイルが開かなかったり、なかったら1を返す
	if (!fileBuff) { return 1; }

	else
	{
		// バッファ
		std::string lineBuff;
		std::string buff;

		// イテレータ
		auto id = data.begin();

		// 引数の要素数バッファー
		auto size = data.size();
		auto num = 0;

		bool widthFlg = true;
		mapWidth = 0;
		mapHeight = 0;

		// 一行取得
		while (getline(fileBuff, lineBuff))
		{
			// 変換
			std::istringstream line(lineBuff);

			// 区切り文字以前のstringを取得
			while (getline(line, buff, ','))
			{
				// buffに格納されている文字がすべて数字なら数値(int型)に変えて代入
				if (std::all_of(buff.cbegin(), buff.cend(), isdigit))
				{
					if (num >= size) {
						data.push_back(stoi(buff));
						if (widthFlg) {
							mapWidth++;
						}
					}
					else {
						*id = stoi(buff);// stringをintへ変換し保存
						id++;
						num++;
						if (widthFlg) {
							mapWidth++;
						}
					}
				}
			}

			if (widthFlg) {
				widthFlg = false;
			}
			mapHeight++;
		}

		coodinateChangeConstant = mapHeight * kMapSize;

		return 0;
	}
}


int MapChip::getData(const int& x, const int& y) {
	return data[y * MapChip::mapWidth + x];
}

void MapChip::setData(int num, const int& x, const int& y) {
	if (num >= (int)Type::kMaxNum) { num = 0; }

	data[y * MapChip::mapWidth + x] = num;
}

Vector2D MapChip::getPlyPos() {
	return plyPos;
}

Vector2D MapChip::getEmyPos(size_t index) {
	return emyPos[index];
}

Vector2D MapChip::getGoalPos() {
	return goalPos;
}

Vector2D MapChip::getButtonPos(size_t index) {
	return buttonPos[index];
}

void MapChip::LocalReload(Vector2D pos) {
	std::vector<int> tmp(0);

	IOcsv::Input("./Data/mappu2_-_1.csv", tmp);
	
	// 場所によってwidthとheightをきめる
	int startX;
	int endX;

	if (MapChip::GetNum(pos).x < static_cast<float>(mapWidth / 2)) {
		startX = 0;
		endX = mapWidth / 2;
	}
	else {
		startX = mapWidth / 2;
		endX = mapWidth;
	}

	int startY;
	int endY;

	if (MapChip::GetNum(pos).y < static_cast<float>(mapHeight / 2)) {
		startY = 0;
		endY = mapHeight / 2;
	}
	else {
		startY = mapHeight / 2;
		endY = mapHeight;
	}

	for (int y = startY; y < endY; y++) {
		for (int x = startX; x < endX; x++) {
			data[y * MapChip::mapWidth + x] = tmp[y * MapChip::mapWidth + x];
		}
	}
}
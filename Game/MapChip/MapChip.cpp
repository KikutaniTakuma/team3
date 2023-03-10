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
int  MapChip::blockCount = 0;
int MapChip::brkCount = 0;
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
std::vector<Vector2D> MapChip::goalPos = std::vector<Vector2D>(0);
std::vector<Vector2D> MapChip::buttonPos = std::vector<Vector2D>(0);

Texture MapChip::block = Texture();
Texture MapChip::tile = Texture();
Texture MapChip::breakTile = Texture();


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
				goalPos.push_back(Vector2D(static_cast<float>(x * MapChip::kMapSize) + (MapChip::kMapSize / 2), CoordinateChange(static_cast<float>(y * MapChip::kMapSize) + static_cast<float>(MapChip::kMapSize / 2))));
			}
			if (data[y * MapChip::mapWidth + x] == 51) {
				data[y * MapChip::mapWidth + x] = 0;
				buttonPos.push_back(Vector2D(static_cast<float>(x * MapChip::kMapSize) + (MapChip::kMapSize / 2), CoordinateChange(static_cast<float>(y * MapChip::kMapSize) + static_cast<float>(MapChip::kMapSize / 2))));
			}
		}
	}

	block.Set("./Resources/Block.png", 64, 64, 64);
	tile.Set("./Resources/Tile.png", 32, 32, 32);
	breakTile.Set("./Resources/BreakTile.png", 32, 32, 32);
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
				goalPos.push_back(Vector2D(static_cast<float>(x * MapChip::kMapSize) + (MapChip::kMapSize / 2), CoordinateChange(static_cast<float>(y * MapChip::kMapSize) + static_cast<float>(MapChip::kMapSize / 2))));
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

	// ?J???????f?????????}?b?v?`?b?v????????????
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
				camera->DrawQuad(pos, breakTile, 0, MyMath::GetRGB(255, 255, 255, 0xff));

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
	// 1, ?i???????????????????????????I?u?W?F?N?g??????????????
	// ?????????\?????????I?u?W?F?N?g???I??????????
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
	// ?????O?????????????????????I?u?W?F?N?g??????????????????????


	// 2, ?????????????????????????????I?u?W?F?N?g?????u??????
	// ?I?u?W?F?N?g?????u??????


	// 3, ?????x?N?g???????K???????????x?N?g????????

	// 4, Quad?????????x?N?g?????}?b?v?`?b?v?????????x?N?g?????????x?N?g?????|????

	// 5, ?|???????????????x?N?g?????????????????????x?N?g?????|????
}

int MapChip::LoadMap(std::string fileName) {
	// ?t?@?C???o?b?t?@?[(?R???X?g???N?^???J??)
	std::ifstream fileBuff(fileName);

	// ?????t?@?C?????J?????????????A??????????1??????
	if (!fileBuff) { return 1; }

	else
	{
		// ?o?b?t?@
		std::string lineBuff;
		std::string buff;

		// ?C?e???[?^
		auto id = data.begin();

		// ???????v?f???o?b?t?@?[
		auto size = data.size();
		auto num = 0;

		bool widthFlg = true;
		mapWidth = 0;
		mapHeight = 0;
		blockCount = 0;
		brkCount = 0;

		// ???s????
		while (getline(fileBuff, lineBuff))
		{
			// ????
			std::istringstream line(lineBuff);

			// ?????????????O??string??????
			while (getline(line, buff, ','))
			{
				// buff???i?[?????????????????????????????????l(int?^)????????????
				if (std::all_of(buff.cbegin(), buff.cend(), isdigit))
				{
					if (stoi(buff) == static_cast<int>(Type::BLOCK)) {
						blockCount++;
					}

					if (num >= size) {
						data.push_back(stoi(buff));
						if (widthFlg) {
							mapWidth++;
						}
					}
					else {
						*id = stoi(buff);// string??int????????????
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

		blockCount -= ((mapHeight + mapWidth) * 2 - 4);

		coodinateChangeConstant = mapHeight * kMapSize;

		return 0;
	}
}


int MapChip::getData(const int& x, const int& y) {
	return data[y * MapChip::mapWidth + x];
}

void MapChip::setData(int num, const int& x, const int& y) {
	if (num >= (int)Type::kMaxNum) { num = 0; }

	else if (data[y * MapChip::mapWidth + x] == static_cast<int>(Type::BLOCK)) {
		brkCount++;
		data[y * MapChip::mapWidth + x] = num;
	}

	else {
		data[y * MapChip::mapWidth + x] = num;
	}
}

Vector2D MapChip::getPlyPos() {
	return plyPos;
}

Vector2D MapChip::getEmyPos(size_t index) {
	return emyPos[index];
}

Vector2D MapChip::getGoalPos(size_t index) {
	return goalPos[index];
}

Vector2D MapChip::getButtonPos(size_t index) {
	return buttonPos[index];
}

void MapChip::LocalReload(Vector2D pos) {
	std::vector<int> tmp(0);

	IOcsv::Input("./Data/mappu2_-_1.csv", tmp);
	
	// ????????????width??height????????
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
			if (tmp[y * MapChip::mapWidth + x] == static_cast<int>(Type::BLOCK) && data[y * MapChip::mapWidth + x] == static_cast<int>(Type::BREAK)) {
				brkCount--;
			}

			if (tmp[y * MapChip::mapWidth + x] == 55) {
				tmp[y * MapChip::mapWidth + x] = 0;
			}
			if (tmp[y * MapChip::mapWidth + x] == 56) {
				tmp[y * MapChip::mapWidth + x] = 0;
			}
			if (tmp[y * MapChip::mapWidth + x] == 50) {
				tmp[y * MapChip::mapWidth + x] = 1;
			}
			if (tmp[y * MapChip::mapWidth + x] == 51) {
				tmp[y * MapChip::mapWidth + x] = 0;
			}

			data[y * MapChip::mapWidth + x] = tmp[y * MapChip::mapWidth + x];
		}
	}
}

int MapChip::GetArea(Vector2D pos) {
	if (MapChip::GetNum(pos).x < static_cast<float>(mapHeight / 2)) {
		if (MapChip::GetNum(pos).y < static_cast<float>(mapHeight / 2)) {
			return 3;
		}
		else {
			return 1;
		}
	}
	else {
		if (MapChip::GetNum(pos).y < static_cast<float>(mapHeight / 2)) {
			return 2;
		}
		else {
			return 0;
		}
	}

}

float MapChip::GetBlockBreakPer() {
	return 100.0f - ((static_cast<float>(brkCount) / static_cast<float>(blockCount)) * 100.0f);
}
#include "MapChip.h"
#include <Novice.h>
#include "Game/Texture/Texture.h"
#include "Game/Vector2D/Vector2D.h"
#include "Game/MyMath/MyMath.h"
#include "Game/Quad/Quad.h"
#include "Game/Camera/Camera.h"

#include "Game/IOcsv/IOcsv.h"
#include "Game/Enemy/Enemy.h"

std::vector<int> MapChip::data;
const int MapChip::kMapSize = 32;
const int MapChip::kWindowWidth = 1280;
const int MapChip::kWindowHeight = 720;
const int MapChip::kStageNumberWidth = 6;//6
const int MapChip::kStageNumberHeight = 11;//11
const int MapChip::kMapWidth = 199; //199
const int MapChip::kMapHeight = 200;//200
const Camera* MapChip::camera = nullptr;
Quad MapChip::pos;
Vector2D MapChip::plyPos = Vector2D();
std::vector<Vector2D> MapChip::emyPos = std::vector<Vector2D>(Enemy::kMaxEmyNum);


void MapChip::Initilize() {
	MapChip::data.resize(MapChip::kMapHeight * MapChip::kMapWidth);

	IOcsv::Input("./Data/mappu2_-_1.csv", MapChip::data);//./Data/MapChipData.csv

	int count = 0;
	for (int y = 0; y < kMapHeight; y++) {
		for (int x = 0; x < kMapWidth; x++) {
			if (data[y * MapChip::kMapWidth + x] == 55) {
				data[y * MapChip::kMapWidth + x] = 0;
				plyPos = Vector2D(static_cast<float>(x * MapChip::kMapSize), MyMath::CoordinateChange(static_cast<float>(y * MapChip::kMapSize)));
			}
			if (data[y * MapChip::kMapWidth + x] == 56 && count < Enemy::kMaxEmyNum) {
				data[y * MapChip::kMapWidth + x] = 0;
				emyPos[count] = Vector2D(static_cast<float>(x * MapChip::kMapSize), MyMath::CoordinateChange(static_cast<float>(y * MapChip::kMapSize)));
				count++;
			}
		}
	}
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
	pos.Set({ 0.0f,0.0f }, { kMapSize, kMapSize });

	// �J�����̉f��͈͂̃}�b�v�`�b�v�̔ԍ����擾
	int firstY = (static_cast<int>(camera->getPos().y) / kMapSize) + (static_cast<int>((camera->getDrawSize().y) / 2.0f) / kMapSize) + 1;
	int lastY = (static_cast<int>(camera->getDrawSize().y / 2.0f) / kMapSize) - (static_cast<int>(camera->getPos().y) / kMapSize) - 1;
	firstY += lastY + static_cast<int>(MapChip::GetNum(camera->worldPos).y);
	/*int hoge = static_cast<int>(MapChip::GetNum(camera->worldPos).y);*/
	

	if (firstY > kMapHeight - 1) {
		firstY = kMapHeight - 1;
	}
	if (lastY < 0) {
		lastY = 0;
	}

	int firstX = (static_cast<int>(camera->getPos().x) / kMapSize) - (static_cast<int>(camera->getDrawSize().x / 2.0f) / kMapSize) - 1;
	int lastX = (static_cast<int>(camera->getPos().x) / kMapSize) + (static_cast<int>(camera->getDrawSize().x / 2.0f) / kMapSize) + 1;

	if (firstX < 0) {
		firstX = 0;
	}
	if (lastX > kMapWidth) {
		lastX = kMapWidth;
	}

	for (y = firstY; y >= lastY; y--) {
		for (x = firstX; x < lastX; x++) {
	
			pos.worldPos = { static_cast<float>((x * kMapSize) + kMapSize / 2), static_cast<float>((y * kMapSize) + kMapSize / 2) };
			MyMath::CoordinateChange(pos.worldPos);
			pos.worldMatrix.Translate(pos.worldPos);

			switch (data[y * MapChip::kMapWidth + x]) {
			case (int)MapChip::Type::NONE:
				camera->DrawQuad(pos, texture, 0, false, BLACK);

				break;
			case (int)MapChip::Type::BLOCK:
				camera->DrawQuad(pos, texture, 0, false, MyMath::GetRGB(200,200,200,0xff));

				break;

			default:
				camera->DrawQuad(pos, texture, 0, false, BLACK);

				break;
			}
		}
	}
}

void MapChip::CollisionBlock(Quad& pos, Vector2D& moveVec) {
	// 1, �i��ł�������ɓ����蔻��̃I�u�W�F�N�g�����邩�ǂ���
	// ������\��������I�u�W�F�N�g��I�ю��֐�
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
	// �ړ��O�̈ړ������Ɉ�ԋ߂��I�u�W�F�N�g���������Ă��邩�ǂ���


	// 2, ��������ړ���ɂ����ԋ߂��I�u�W�F�N�g�̈ʒu�Ɉړ�
	// �I�u�W�F�N�g�̈ʒu�Ɉړ�


	// 3, �ړ��x�N�g���𐳋K�����Ĕ��΃x�N�g�����Ƃ�

	// 4, Quad�̑傫���x�N�g���ƃ}�b�v�`�b�v�̑傫���x�N�g���Ɣ��΃x�N�g�����|����

	// 5, �|�������ꂼ��̃x�N�g���𑫂������̂��ړ��x�N�g�����|����
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

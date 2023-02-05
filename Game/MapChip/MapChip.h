#pragma once

#include "Game/Vector2D/Vector2D.h"
#include "Game/Texture/Texture.h"

class Texture;
class Quad;

#include <vector>
#include <string>

class MapChip {
public:
	enum class Type {
		NONE, // 0
		BLOCK, // 1

		kMaxNum
	};

private:
	inline MapChip() {}
	inline ~MapChip() {}

public:
	static const int kMapSize;
	static const int kWindowWidth;
	static const int kWindowHeight;
	static int coodinateChangeConstant;

private:
	static int mapWidth;
	static int mapHeight;
	static float mapMaxPosX;
	static float mapMaxPosY;
	static float mapMinPosX;
	static float mapMinPosY;

public:
	static void CoordinateChange(Vector2D& worldPos);

	static float CoordinateChange(float worldPosY);

	static inline int getMapWidth() {
		return mapWidth;
	}
	static inline int getMapHeight() {
		return mapHeight;
	}
	static inline float getMapMaxPosX() {
		return mapMaxPosX;
	}
	static inline float getMapMaxPosY() {
		return mapMaxPosY;
	}
	static inline float getMapMinPosX() {
		return mapMinPosX;
	}
	static inline float getMapMinPosY() {
		return mapMinPosY;
	}


	static std::vector<int> data;

private:
	static const class Camera* camera;

	static Quad pos;

	static Vector2D plyPos;
	static std::vector<Vector2D> emyPos;
	static Vector2D goalPos;
	static std::vector<Vector2D> buttonPos;

	static Texture block;
	static Texture tile;

public:
	static void Initilize();

	static void SetCamera(class Camera* cameraPointa);

	static void Finalize();

	static bool Collision(const Vector2D& pos);

	// マップチップの踏んでいる場所
	static int GetType(Vector2D worldPos);

	// マップチップの座標
	static Vector2D GetPos(Vector2D worldPos);

	//　マップチップの番号取得
	static Vector2D GetNum(Vector2D worldPos);

	// MapChipの表示処理
	static void Draw(Texture& texture);

	// ホットリロード
	static void Reset();

	/// <summary>
	/// マップチップの当たり判定
	/// </summary>
	static void CollisionBlock(Quad& pos, Vector2D& moveVec);

	/// <summary>
	/// 特定のマップチップ読み込み
	/// </summary>
	/// <param name="fileName">読み込みたいファイルパス</param>
	static int LoadMap(std::string fileName);

	// getter
	static int getData(const int& x, const int& y);

	// setter
	static void setData(int num, const int& x, const int& y);

	static Vector2D getPlyPos();
	static Vector2D getEmyPos(size_t index);

	static Vector2D getGoalPos();
	static Vector2D getButtonPos(size_t index);
};
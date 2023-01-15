#pragma once

class Texture;
class Vector2D;
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
	static const int kStageNumberWidth;
	static const int kStageNumberHeight;
	static const int kMapWidth;
	static const int kMapHeight;
	static std::vector<int> data;

private:
	static const class Camera* camera;

public:
	static void Initilize();

	static void SetCamera(class Camera* cameraPointa);

	static void Finalize();

	static bool Collision(const Vector2D& pos);

	// �}�b�v�`�b�v�̓���ł���ꏊ
	static int GetType(Vector2D worldPos);

	// �}�b�v�`�b�v�̍��W
	static Vector2D GetPos(Vector2D worldPos);

	//�@�}�b�v�`�b�v�̔ԍ��擾
	static Vector2D GetNum(Vector2D worldPos);

	// MapChip�̕\������
	static void Draw(Texture& texture);

	// �z�b�g�����[�h
	static void Reset();

	/// <summary>
	/// �}�b�v�`�b�v�̓����蔻��
	/// </summary>
	static void Collision(Quad& pos, Vector2D& moveVec);

	/// <summary>
	/// ����̃}�b�v�`�b�v�ǂݍ���
	/// </summary>
	/// <param name="fileName">�ǂݍ��݂����t�@�C���p�X</param>
	static void LoadMap(std::string fileName);

	// getter
	static int getData(const int& x, const int& y);

	// setter
	static void setData(int num, const int& x, const int& y);
};
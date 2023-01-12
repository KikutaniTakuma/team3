#pragma once

class Vector2D;

class MyMath {
private:
	inline MyMath(){}
	inline ~MyMath(){}

public:
	// ���[���h���W��ϊ����̒萔
	static const int kCoodinateChangeConstant;

	static void CoordinateChange(Vector2D& worldPos);

	// �O�����̒藝
	static float PythagoreanTheorem(const float& x, const float& y);

	// ���K��
	// �����������K�������
	static float Normalize(const float& x, const float& y);

	static Vector2D Normalize(Vector2D vec);

	/*
	��`�̓����蔻��
	
	�������F��`�̍�����W
	�������F��`�̃T�C�Y
	��O�����F��`�̍�����W2
	��l�����F��`�̃T�C�Y2

	�߂�l�F�������Ă�F�P
	�@�@�@  �������ĂȂ��F�O
	*/
	static bool CollisionRectangle(Vector2D LeftTop1, Vector2D size1, Vector2D LeftTop2, Vector2D size2);

	/*
	��`�̓����蔻��

	�������F��`�̍�����W
	�������F��`�̃T�C�Y
	��O�����F��`�̍�����W2
	��l�����F��`�̃T�C�Y2

	�߂�l�F�������Ă�F�P
	�@�@�@  �������ĂȂ��F�O
	*/
	static bool CollisionRectangle(int LeftTopX1, int LeftTopY1, int sizeX1, int sizeY1, int LeftTopX2, int LeftTopY2, int sizeX2, int sizeY2);

	/*
	����ւ�

	�������Ƒ����������ւ���
	*/
	template <class T>
	static inline void Tmp(T& x, T& y) {
		T tmp;
		tmp = x;
		x = y;
		y = tmp;
	}


	/*
	�o�u���\�[�g

	�������F�f�[�^
	�������F�f�[�^�̗v�f��
	��O�����Ftrue���������Afalse�傫����
	*/
	static void BubbleSort(int* data, int arr, bool order);

	/// <summary>
	/// ����
	/// </summary>
	/// <param name="vec1"></param>
	/// <param name="vec2"></param>
	/// <returns></returns>
	static bool Dot(const Vector2D& vec1, const Vector2D& vec2);

	/// <summary>
	/// �O��
	/// </summary>
	/// <param name="vec1">�|�W�V����1</param>
	/// <param name="vec2">�|�W�V����2</param>
	/// <returns>�|�W�V����1���|�W�V����2���������ɂ������Ƃ���true���E����false��Ԃ�</returns>
	static bool Cross(const Vector2D& vec1, const Vector2D& vec2);

	/// <summary>
	/// �x���@����ʓx�@�ɕϊ�
	/// </summary>
	/// <param name="deg">�ϊ�������deg</param>
	/// <returns>�ϊ���̊p�x</returns>
	static float ToRad(const float& deg);

	/// <summary>
	/// �ʓx�@����x���@�ɕϊ�
	/// </summary>
	/// <param name="rad">�ϊ�������rad</param>
	/// <returns>�ϊ���̊p�x</returns>
	static float ToDeg(const float& rad);

	/// <summary>
	/// ����̊p�x�͈̔͂��ǂ���
	/// </summary>
	/// <param name="deg">�͈͂ɓ����Ă邩�ǂ����̊p�x</param>
	/// <param name="maxDeg">����̊p�x�̍ő�l</param>
	/// <param name="minDeg">����̊p�x�̍ŏ��l</param>
	/// <returns>����̊p�x�͈̔͂Ȃ�ture</returns>
	static bool isAngle(float deg, float maxDeg, float minDeg);

	/// <summary>
	/// ����̏ꏊ����̊p�x�����߂�
	/// </summary>
	/// <param name="pos">���߂����|�W�V����</param>
	/// <param name="origin">�ǂ�����̊p�x���̃|�W�V����</param>
	/// <returns>�p�x(deg)</returns>
	static float GetAngle(Vector2D pos, Vector2D origin);

	/// <summary>
	/// �����ɓ��ꂽ���̂���������
	/// </summary>
	/// <param name="num">��������������1</param>
	/// <param name="num2">��������������2</param>
	template<typename T>
	static inline void Swap(T& num, T& num2) {
		T tmp = num;
		num = num2;
		num2 = tmp;
	}

	static float Clamp(float num, float max, float min);

	static unsigned int GetRGB(unsigned int red, unsigned int green, unsigned int blue, unsigned int alpha);

	/// <summary>
	/// min�ȏ�max�ȉ��܂ł̃����_���Ȓl��Ԃ�
	/// </summary>
	/// <param name="min">�ŏ��l</param>
	/// <param name="max">�ő�l</param>
	/// <returns>min�ȏ�max�ȉ��܂ł̃����_���Ȓl</returns>
	static int Random(int min, int max);

	/// <summary>
	/// �J�v�Z������
	/// </summary>
	/// <param name="pos">�I�u�W�F�N�g�̈ʒu</param>
	/// <param name="start">�ړ����Ă��镨�̂̃X�^�[�g�ʒu</param>
	/// <param name="end">�ړ����Ă��镨�̂̈ړ���̈ʒu</param>
	/// <param name="size">�J�v�Z���̃T�C�Y</param>
	/// <returns>�������Ă���ture</returns>
	static bool Capsule(Vector2D pos, Vector2D start, Vector2D end, float size);

	template<class T>
	static inline void SafeDelete(T*& p) {
		delete p;
		p = nullptr;
	}
};
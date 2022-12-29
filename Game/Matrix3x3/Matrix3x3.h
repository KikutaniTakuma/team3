#pragma once

#include <array>

class Vector2D;

class Matrix3x3 {
public:
	using arr3x3 = std::array<std::array<float, 3>, 3>;

public:
	Matrix3x3();
	Matrix3x3(const Matrix3x3& matrix);

	inline ~Matrix3x3() {}

private:
	static const int HEIGHT = 3;
	static const int WIDTH = 3;

public:
	arr3x3 m;

public:
	Matrix3x3 operator*(const Matrix3x3& Matrix1) const;
	const Matrix3x3& operator=(const Matrix3x3& Matrix1);
	const Matrix3x3& operator*=(const Matrix3x3& Matrix1);

public:
	// ��]�s��
	void Rotate(float degree);
	friend Matrix3x3 MakeRotate(float degree);

	// ���s�ړ��s��
	void Translate(const Vector2D& vec);
	void Translate(const float& vecX, const float& vecY);
	friend Matrix3x3 MakeTranslate(const Vector2D& vec);

	// �X�J���[�{�s��
	void Scalar(const Vector2D& vec);
	void Scalar(const float& vecX, const float& vecY);
	friend Matrix3x3 MakeScalar(const Vector2D& vec);

	// �A�t�B���ϊ�
	void Affin(const Vector2D& size, float degree, const Vector2D& trancelate);
	friend Matrix3x3 MakeAffin(const Vector2D& size, float degree, const Vector2D& trancelate);

	// �t�s��
	void Inverse();

	// �]�u�s��
	void Transepose();

	// ���ˉe�s��
	void Orthographic(const Vector2D& leftTop, const Vector2D& rightUnder);
	void Orthographic(const Vector2D& size);
	friend Matrix3x3 MakeOrthographic(const Vector2D& leftTop, const Vector2D& rightUnder);
	friend Matrix3x3 MakeOrthographic(const Vector2D& size);

	/// <summary>
	/// �r���[�|�[�g�s��
	/// </summary>
	/// <param name="pos">�J�����̍���̍��W</param>
	/// <param name="size">�傫��</param>
	void Viewport(const Vector2D& pos, const Vector2D& size);

	friend Matrix3x3 MakeViewport(const Vector2D& pos, const Vector2D& size);
};
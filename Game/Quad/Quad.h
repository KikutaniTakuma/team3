#pragma once

#include "Game/Vector2D/Vector2D.h"
#include "Game/Matrix3x3/Matrix3x3.h"

class Quad {
public:
	/// <summary>
	/// �K��R���X�g���N�^
	/// </summary>
	Quad();

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="worldPos">�|�W�V����</param>
	/// <param name="size">�傫��</param>
	Quad(const Vector2D& worldPos, const Vector2D& size);

	/// <summary>
	/// �R�s�[�R���X�g���N�^
	/// </summary>
	/// <param name="quad">Quad</param>
	Quad(const Quad& quad);

	/// <summary>
	/// ���[�u�R���X�g���N�^
	/// </summary>
	/// <param name="worldPos">�|�W�V����</param>
	/// <param name="size">�傫��</param>
	Quad(Vector2D&& worldPos, Vector2D&& size);

	/// <summary>
	/// Set(�R���X�g���N�^�Ɠ���)
	/// </summary>
	/// <param name="worldPos">�|�W�V����</param>
	/// <param name="size">�傫��</param>
	void Set(const Vector2D& worldPos, const Vector2D& size);

	/// <summary>
	/// �X�P�[�����O
	/// </summary>
	/// <param name="scale">�傫��</param>
	void Scale(const float& scale);

	/// <summary>
	/// ��]
	/// </summary>
	/// <param name="deg">degree</param>
	void Rotate(float deg);

	/// <summary>
	/// ���
	/// </summary>
	/// <param name="quad">quad</param>
	/// <returns>const�Q��Quad</returns>
	const Quad& operator=(const Quad& quad);

	/// <summary>
	/// �|���Z
	/// 4�_���|����
	/// </summary>
	/// <param name="matrix">�s��</param>
	/// <returns>Quad</returns>
	Quad operator*(const Matrix3x3& matrix);

	/// <summary>
	/// ����|���Z
	/// </summary>
	/// <param name="matrix">�s��</param>
	/// <returns>const�Q��Quad</returns>
	const Quad& operator*=(const Matrix3x3& matrix);

	Quad operator+(const Vector2D& vec);

private:
	Vector2D leftTop;
	Vector2D leftUnder;
	Vector2D rightTop;
	Vector2D rightUnder;

	Vector2D size;

	Matrix3x3 vpvpMatrix;

public:
	Vector2D worldPos;

	Matrix3x3 worldMatrix;

public:
	void setVpvpMatrix(const Matrix3x3& tmp);

	void Translate();

	Vector2D getSize() const;

	// getter
	// worldPos�𑫂������̂��Ԃ��Ă���

	Vector2D getPosLeftTop() const;
	Vector2D getPosLeftUnder() const;
	Vector2D getPosRightTop() const;
	Vector2D getPosRightUnder() const;

	// worldPos�𑫂��ĂȂ����̂��Ԃ��Ă���
	const Vector2D& getSizeLeftTop() const;
	const Vector2D& getSizeLeftUnder() const;
	const Vector2D& getSizeRightTop() const;
	const Vector2D& getSizeRightUnder() const;

	// ���[���h�s����|�������̂�Ԃ�
	Vector2D getMatrixLeftTop() const;
	Vector2D getMatrixLeftUnder() const;
	Vector2D getMatrixRightTop() const;
	Vector2D getMatrixRightUnder() const;
};
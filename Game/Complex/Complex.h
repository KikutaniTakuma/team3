#pragma once

class Complex {
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Complex();

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="re">����</param>
	/// <param name="im">����</param>
	Complex(const float& re, const float& im);

	/// <summary>
	/// �R�s�[�R���X�g���N�^
	/// </summary>
	/// <param name="tmp">���f��</param>
	Complex(const Complex& tmp);

	/// <summary>
	/// Vector2D�ŏ�����
	/// </summary>
	/// <param name="tmp">Vec2</param>
	Complex(const class Vector2D& tmp);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	inline ~Complex(){}

public:
	/// <summary>
	/// ����
	/// </summary>
	float real;

	/// <summary>
	/// ����
	/// </summary>
	float imag;

public:
	/// <summary>
	/// ���Z�q�̃I�[�o�[���[�h
	/// </summary>
	/// <param name="num">�����������f��</param>
	/// <returns>����������</returns>
	Complex operator+(const Complex& num);

	/// <summary>
	/// ���Z�q�̃I�[�o�[���[�h
	/// </summary>
	/// <param name="num">�|���������f��</param>
	/// <returns>�|��������</returns>
	Complex operator*(const Complex& num);

	/// <summary>
	/// ���Z�q�̃I�[�o�[���[�h
	/// </summary>
	/// <param name="num">������������f��</param>
	/// <returns>*this</returns>
	const Complex& operator=(const Complex& num);

	/// <summary>
	/// ���Z�q�̃I�[�o�[���[�h
	/// </summary>
	/// <param name="num">���������vec2</param>
	/// <returns>*this</returns>
	const Complex& operator=(const class Vector2D& num);

	/// <summary>
	/// ���Z�q�̃I�[�o�[���[�h
	/// </summary>
	/// <param name="num">��������Z���������f��</param>
	/// <returns>�����đ����������</returns>
	const Complex& operator+=(const Complex& num);

	/// <summary>
	/// ���Z�q�̃I�[�o�[���[�h
	/// </summary>
	/// <param name="num">������Ċ|���Z���������f��</param>
	/// <returns>�|���đ����������</returns>
	const Complex& operator*=(const Complex& num);

public:
	const class Vector2D& GetVector2D() const;
};
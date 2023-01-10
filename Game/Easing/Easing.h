#pragma once

#include "Game/MyMath/MyMath.h"
#include "Game/Vector2D/Vector2D.h"
#include <functional>
#define _USE_MATH_DEFINES
#include <math.h>

		/*�@�C�[�W���O�`�[�g�V�[�g�Q�Ɓi����[1]����E��[30]�ɂ����āj�@*/

//		�g�����F�ᕶ
//		if(true){
//			T = Easing::EaseInSine(num);		Easing(�N���X��)	EaseInSine(�N���X���ϐ���)
//			num += spd;
//			pos_x = (1 - T) * �n�_ + T * �I�_;
//			pos_y = (1 - T) * �n�_ + T * �I�_;
//		}

class Easing {
public:
	Easing();

	Easing(Vector2D start, Vector2D end, float speed, std::function<float(float)> easeType);

	void Set(Vector2D start, Vector2D end, float speed, std::function<float(float)> easeType);

	Vector2D Update();

public:
	float spd;

private:
	float easeT;
	Vector2D startPos;
	Vector2D endPos;
	Vector2D currentPos;
	std::function<float(float)> easeFunc;

public:
	//	1��
	friend float EaseInSine(float x);
	//	2
	friend float EaseOutSine(float x);
	//	3
	friend float EaseInOutSine(float x);
	//	4
	friend float EaseInQuad(float x);
	//	5
	friend float EaseOutQuad(float x);
	//	6
	friend float EaseInOutQuad(float x);
	//	7
	friend float EaseInCubic(float x);
	//	8
	friend float EaseOutCubic(float x);
	//	9
	friend float EaseInOutCubic(float x);
	//	10
	friend float EaseInQuart(float x);
	//	11
	friend float EaseOutQuart(float x);
	//	12
	friend float EaseInOutQuart(float x);
	//	13
	friend float EaseInQuint(float x);
	//	14
	friend float EaseOutQuint(float x);
	//	15
	friend float EaseInOutQuint(float x);
	//	16
	friend float EaseInExpo(float x);
	//	17
	friend float EaseOutExpo(float x);
	//	18
	friend float EaseInOutExpo(float x);
	//	19
	friend float EaseInCirc(float x);
	//	20
	friend float EaseOutCirc(float x);
	//	21
	friend float EaseInOutCirc(float x);
	//	22
	friend float EaseInBack(float x);
	//	23
	friend float EaseOutBack(float x);
	//	24
	friend float EaseInOutBack(float x);
	//	25
	friend float EaseInElastic(float x);
	//	26
	friend float EaseOutElastic(float x);
	//	27
	friend float EaseInOutElastic(float x);
	//	28
	friend float EaseInBounce(float x);
	//	29
	friend float EaseOutBounce(float x);
	//	30
	friend float EaseInOutBounce(float x);
};
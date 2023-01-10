#include "Game/Easing/Easing.h"
#include "Game/Vector2D/Vector2D.h"
#include "Game/MyMath/MyMath.h"

Easing::Easing(std::function<float(float)> func, float spd) :
	function(func),
	t(0.0f),
	num(0.0f),
	spd(spd)
{}

Easing::Easing(const Easing& tmp) {
	*this = tmp;
}

Easing::Easing(Easing&& tmp) {
	*this = tmp;
}

void Easing::Use(Vector2D& pos, Vector2D start, Vector2D end) {
	t = function(spd);
	num += spd;
	num = MyMath::Clamp(num, 1.0f, 0.0f);
	pos.x = (1 - t) * start.x + t * end.x;
	pos.y = (1 - t) * start.y + t * end.y;
}

const Easing& Easing::operator=(const Easing& tmp) {
	function = tmp.function;
	t = tmp.t;
	num = tmp.spd;
	spd = tmp.spd;

	return *this;
}

//	1”Ô
float EaseInSine(float x) {
	return 1 - cosf((x * M_PI) / 2);
}
//	2
float EaseOutSine(float x) {
	return sinf((x * M_PI) / 2);
}
//	3
float EaseInOutSine(float x) {
	return -(cosf(M_PI * x) - 1) / 2;
}
//	4
float EaseInQuad(float x) {
	return powf(x, 2);
}
//	5
float EaseOutQuad(float x) {
	return 1 - (1 - x) * (1 - x);
}
//	6
float EaseInOutQuad(float x) {

	if (x < 0.5f)
	{
		return 2 * powf(x, 2);
	}
	else
	{
		return 1 - powf(-2 * x + 2, 2) / 2;
	}
}
//	7
float EaseInCubic(float x) {
	return pow(x, 3);
}
//	8
float EaseOutCubic(float x) {
	return 1 - powf(1 - x, 3);
}
//	9
float EaseInOutCubic(float x) {
	if (x < 0.5f)
	{
		return 4 * powf(x, 4);
	}
	else
	{
		return 1 - powf(-2 * x + 2, 3) / 2;
	}
}
//	10
float EaseInQuart(float x) {
	return powf(x, 4);
}
//	11
float EaseOutQuart(float x) {
	return 1 - powf(1 - x, 4);
}
//	12
float EaseInOutQuart(float x) {
	if (x < 0.5f)
	{
		return 8 * powf(x, 4);
	}
	else
	{
		return 1 - powf(-2 * x + 2, 4) / 2;
	}
}
//	13
float EaseInQuint(float x) {
	return powf(x, 5);
}
//	14
float EaseOutQuint(float x) {
	return 1 - powf(1 - x, 5);
}
//	15
float EaseInOutQuint(float x) {
	if (x < 0.5f)
	{
		return 16 * powf(x, 5);
	}
	else
	{
		return 1 - powf(-2 * x + 2, 5) / 2;
	}
}
//	16
float EaseInExpo(float x) {
	if (x == 0)
	{
		return 0;
	}
	else
	{
		return powf(2, 10 * x - 10);
	}
}
//	17
float EaseOutExpo(float x) {
	if (x == 1)
	{
		return 1;
	}
	else
	{
		return 1 - powf(2.0f, -10.0f * x);
	}
}
//	18
float EaseInOutExpo(float x) {
	if (x == 0)
	{
		return 0;
	}
	else if (x == 1)
	{
		return 1;
	}
	else if (x < 0.5f)
	{
		return powf(2, 20 * x - 10) / 2;
	}
	else
	{
		return (2 - powf(2, -20 * x + 10)) / 2;
	}
}
//	19
float EaseInCirc(float x) {
	return 1 - sqrtf(1 - powf(x, 2));
}
//	20
float EaseOutCirc(float x) {
	return sqrtf(1 - powf(x - 1, 2));
}
//	21
float EaseInOutCirc(float x) {
	if (x < 0.5f)
	{
		return (1 - sqrtf(1 - powf(2 * x, 2))) / 2;
	}
	else
	{
		return (sqrtf(1 - powf(-2 * x + 2, 2)) + 1) / 2;
	}
}
//	22
float EaseInBack(float x) {
	const float c1 = 1.70158;
	const float c3 = c1 + 1;

	return (c3 * powf(x, 3)) - (c1 * powf(x, 2));
}
//	23
float EaseOutBack(float x) {
	const float c1 = 1.70158;
	const float c3 = c1 + 1;

	return 1 + c3 * powf(x - 1, 3) + c1 * powf(x - 1, 2);
}
//	24
float EaseInOutBack(float x) {
	const float c1 = 1.70158;
	const float c2 = c1 * 1.525;

	if (x < 0.5f)
	{
		return (powf(2 * x, 2) * ((c2 + 1) * 2 * x - c2)) / 2;
	}
	else
	{
		return (powf(2 * x - 2, 2) * ((c2 + 1) * (x * 2 - 2) + c2) + 2) / 2;
	}
}
//	25
float EaseInElastic(float x) {
	const float c4 = (2 * M_PI) / 3;

	if (x == 0)
	{
		return 0;
	}
	else if (x == 1)
	{
		return 1;
	}
	else
	{
		return -powf(2, 10 * x - 10) * sinf((x * 10 - 10.75) * c4);
	}
}
//	26
float EaseOutElastic(float x) {
	const float c4 = (2 * M_PI) / 3;

	if (x == 0.0f) {
		return 0.0f;
	}
	else if (x >= 1.0f) {
		return 1.0f;
	}
	else {
		return powf(2, -10.0f * x) * sinf((x * 10.0f - 0.75f) * c4) + 1;
	}
}
//	27
float EaseInOutElastic(float x) {
	const float c5 = (2 * M_PI) / 4.5;

	if (x == 0)
	{
		return 0;
	}
	else if (x == 1)
	{
		return 1;
	}
	else if (x < 0.5f)
	{
		return -(powf(2, 20 * x - 10) * sinf((20 * x - 11.125) * c5)) / 2;
	}
	else
	{
		return (powf(2, -20 * x + 10) * sinf((20 * x - 11.125) * c5)) / 2 + 1;
	}
}
//	28
float EaseInBounce(float x) {
	return 1 - EaseOutBounce(1 - x);
}
//	29
float EaseOutBounce(float x) {
	const float n1 = 7.5625;
	const float d1 = 2.75;

	if (x < 1 / d1) {
		return n1 * powf(x, 2);
	}
	else if (x < 2 / d1) {
		return n1 * (x -= 1.5 / d1) * x + 0.75;
	}
	else if (x < 2.5 / d1) {
		return n1 * (x -= 2.25 / d1) * x + 0.9375;
	}
	else {
		return n1 * (x -= 2.625 / d1) * x + 0.984375;
	}
}
//	30
float EaseInOutBounce(float x) {
	if (x < 0.5f)
	{
		return (1 - EaseOutBounce(1 - 2 * x)) / 2;
	}
	else
	{
		return (1 + EaseOutBounce(2 * x - 1)) / 2;
	}
}
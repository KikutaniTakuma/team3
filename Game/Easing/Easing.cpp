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
	return 1 - cosf((x * static_cast<float>(static_cast<float>(M_PI))) / 2.0f);
}
//	2
float EaseOutSine(float x) {
	return sinf((x * static_cast<float>(M_PI)) / 2.0f);
}
//	3
float EaseInOutSine(float x) {
	return -(cosf(static_cast<float>(M_PI) * x) - 1.0f) / 2.0f;
}
//	4
float EaseInQuad(float x) {
	return powf(x, 2.0f);
}
//	5
float EaseOutQuad(float x) {
	return 1.0f - (1.0f - x) * (1.0f - x);
}
//	6
float EaseInOutQuad(float x) {

	if (x < 0.5f)
	{
		return 2.0f * powf(x, 2.0f);
	}
	else
	{
		return 1.0f - powf(-2.0f * x + 2.0f, 2.0f) / 2.0f;
	}
}
//	7
float EaseInCubic(float x) {
	return pow(x, 3.0f);
}
//	8
float EaseOutCubic(float x) {
	return 1 - powf(1.0f - x, 3.0f);
}
//	9
float EaseInOutCubic(float x) {
	if (x < 0.5f)
	{
		return 4.0f * powf(x, 4.0f);
	}
	else
	{
		return 1.0f - powf(-2.0f * x + 2.0f, 3.0f) / 2.0f;
	}
}
//	10
float EaseInQuart(float x) {
	return powf(x, 4.0f);
}
//	11
float EaseOutQuart(float x) {
	return 1.0f - powf(1 - x, 4.0f);
}
//	12
float EaseInOutQuart(float x) {
	if (x < 0.5f)
	{
		return 8.0f * powf(x, 4.0f);
	}
	else
	{
		return 1.0f - powf(-2.0f * x + 2.0f, 4.0f) / 2.0f;
	}
}
//	13
float EaseInQuint(float x) {
	return powf(x, 5.0f);
}
//	14
float EaseOutQuint(float x) {
	return 1.0f - powf(1.0f - x, 5.0f);
}
//	15
float EaseInOutQuint(float x) {
	if (x < 0.5f)
	{
		return 16.0f * powf(x, 5.0f);
	}
	else
	{
		return 1.0f - powf(-2.0f * x + 2.0f, 5.0f) / 2.0f;
	}
}
//	16
float EaseInExpo(float x) {
	if (x == 0.0f)
	{
		return 0.0f;
	}
	else
	{
		return powf(2.0f, 10.0f * x - 10.0f);
	}
}
//	17
float EaseOutExpo(float x) {
	if (x == 1.0f)
	{
		return 1.0f;
	}
	else
	{
		return 1.0f - powf(2.0f, -10.0f * x);
	}
}
//	18
float EaseInOutExpo(float x) {
	if (x == 0.0f)
	{
		return 0.0f;
	}
	else if (x == 1.0f)
	{
		return 1.0f;
	}
	else if (x < 0.5f)
	{
		return powf(2.0f, 20.0f * x - 10.0f) / 2.0f;
	}
	else
	{
		return (2.0f - powf(2.0f, -20.0f * x + 10.0f)) / 2.0f;
	}
}
//	19
float EaseInCirc(float x) {
	return 1.0f - sqrtf(1.0f - powf(x, 2.0f));
}
//	20
float EaseOutCirc(float x) {
	return sqrtf(1.0f - powf(x - 1.0f, 2.0f));
}
//	21
float EaseInOutCirc(float x) {
	if (x < 0.5f)
	{
		return (1.0f - sqrtf(1.0f - powf(2.0f * x, 2.0f))) / 2.0f;
	}
	else
	{
		return (sqrtf(1.0f - powf(-2.0f * x + 2.0f, 2.0f)) + 1.0f) / 2.0f;
	}
}
//	22
float EaseInBack(float x) {
	const float c1 = 1.70158f;
	const float c3 = c1 + 1.0f;

	return (c3 * powf(x, 3.0f)) - (c1 * powf(x, 2.0f));
}
//	23
float EaseOutBack(float x) {
	const float c1 = 1.70158f;
	const float c3 = c1 + 1.0f;

	return 1.0f + c3 * powf(x - 1.0f, 3.0f) + c1 * powf(x - 1.0f, 2.0f);
}
//	24
float EaseInOutBack(float x) {
	const float c1 = 1.70158f;
	const float c2 = c1 * 1.525f;

	if (x < 0.5f)
	{
		return (powf(2.0f * x, 2.0f) * ((c2 + 1.0f) * 2.0f * x - c2)) / 2.0f;
	}
	else
	{
		return (powf(2.0f * x - 2.0f, 2.0f) * ((c2 + 1.0f) * (x * 2.0f - 2.0f) + c2) + 2.0f) / 2.0f;
	}
}
//	25
float EaseInElastic(float x) {
	const float c4 = (2.0f * static_cast<float>(M_PI)) / 3.0f;

	if (x == 0.0f)
	{
		return 0.0f;
	}
	else if (x == 1.0f)
	{
		return 1.0f;
	}
	else
	{
		return -powf(2.0f, 10.0f * x - 10.0f) * sinf((x * 10.0f - 10.75f) * c4);
	}
}
//	26
float EaseOutElastic(float x) {
	const float c4 = (2 * static_cast<float>(M_PI)) / 3.0f;

	if (x == 0.0f) {
		return 0.0f;
	}
	else if (x >= 1.0f) {
		return 1.0f;
	}
	else {
		return powf(2.0f, -10.0f * x) * sinf((x * 10.0f - 0.75f) * c4) + 1.0f;
	}
}
//	27
float EaseInOutElastic(float x) {
	const float c5 = (2.0f * static_cast<float>(M_PI)) / 4.5f;

	if (x == 0.0f)
	{
		return 0.0f;
	}
	else if (x == 1.0f)
	{
		return 1.0f;
	}
	else if (x < 0.5f)
	{
		return -(powf(2.0f, 20.0f * x - 10.0f) * sinf((20.0f * x - 11.125f) * c5)) / 2.0f;
	}
	else
	{
		return (powf(2.0f, -20.0f * x + 10.0f) * sinf((20.0f * x - 11.125f) * c5)) / 2.0f + 1.0f;
	}
}

// 29
float EaseOutBounce(float x) {
	const float n1 = 7.5625f;
	const float d1 = 2.75f;

	if (x < 1.0f / d1) {
		return n1 * powf(x, 2.0f);
	}
	else if (x < 2.0f / d1) {
		return n1 * (x -= 1.5f / d1) * x + 0.75f;
	}
	else if (x < 2.5f / d1) {
		return n1 * (x -= 2.25f / d1) * x + 0.9375f;
	}
	else {
		return n1 * (x -= 2.625f / d1) * x + 0.984375f;
	}
}
//	28
float EaseInBounce(float x) {
	return 1.0f - EaseOutBounce(1.0f - x);
}

//	30
float EaseInOutBounce(float x) {
	if (x < 0.5f)
	{
		return (1.0f - EaseOutBounce(1.0f - 2.0f * x)) / 2.0f;
	}
	else
	{
		return (1.0f + EaseOutBounce(2.0f * x - 1.0f)) / 2.0f;
	}
}
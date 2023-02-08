#include "Game/Fade/Fade.h"
#include "Game/MyMath/MyMath.h"
#include "Game/Camera/Camera.h"

Fade::Fade() {
	
}

unsigned int Fade::FadeInOut(unsigned int color, float speed, bool InOut) {
	unsigned int red = color >> 24;
	unsigned int green = color >> 16 & 0xff;
	unsigned int blue = color >> 8 & 0xff;
	unsigned int alpha = color & 0xff;
	
	
	InOut ? alpha += static_cast<unsigned int>(speed) * static_cast<unsigned int>(Camera::getHitStop()) : alpha -= static_cast<unsigned int>(speed) * static_cast<unsigned int>(Camera::getHitStop());
	MyMath::Clamp(alpha, 255U, 0U);

	return MyMath::GetRGB(red, green, blue, alpha);
}


unsigned int Fade::Flash(unsigned int color, float speed) {
	unsigned int red = color >> 24;
	unsigned int green = color >> 16 & 0xff;
	unsigned int blue = color >> 8 & 0xff;
	unsigned int alpha = color & 0xff;
	static bool flag = false;

	if (alpha >= 255)
	{
		flag = true;
	}
	else if (alpha <= 0)
	{
		flag = false;
	}

	flag ? alpha -= static_cast<unsigned int>(speed) : alpha += static_cast<unsigned int>(speed);
	MyMath::Clamp(alpha, 255U, 0U);

	return MyMath::GetRGB(red, green, blue, alpha);
}
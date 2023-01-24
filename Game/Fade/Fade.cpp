#include "Game/Fade/Fade.h"
#include "Game/MyMath/MyMath.h"

Fade::Fade() {
	red = 0;
	green = 0;
	blue = 0;
	alpha = 0;
	flag = false;
}

unsigned int Fade::FadeIn(unsigned int color,float speed) {
	red = color >> 24;
	green = color >> 16 & 0xff;
	blue = color >> 8 & 0xff;
	alpha = color & 0xff;
	
	alpha += speed;
	MyMath::Clamp(alpha, 255u, 0u);

	return MyMath::GetRGB(red, green, blue, alpha);
}

unsigned int Fade::FadeOut(unsigned int color, float speed) {
	red = color >> 24;
	green = color >> 16 & 0xff;
	blue = color >> 8 & 0xff;
	alpha = color & 0xff;

	alpha -= speed;
	MyMath::Clamp(alpha, 255u, 0u);

	return MyMath::GetRGB(red, green, blue, alpha);
}

unsigned int Fade::Flash(unsigned int color, float speed) {
	red = color >> 24;
	green = color >> 16 & 0xff;
	blue = color >> 8 & 0xff;
	alpha = color & 0xff;

	if (alpha >= 255.0f)
	{
		flag = true;
	}
	else if (alpha <= 0.0f)
	{
		flag = false;
	}

	flag ? alpha -= speed : alpha += speed;

	return MyMath::GetRGB(red, green, blue, alpha);
}
#include "Game/Fade/Fade.h"
#include "Game/MyMath/MyMath.h"

Fade::Fade() {
	red = 0;
	green = 0;
	blue = 0;
	alpha = 0;
}

unsigned int Fade::FadeIn(unsigned int color,float speed) {
	red = color >> 24;
	green = color >> 16 & 0xff;
	blue = color >> 8 & 0xff;
	alpha = color & 0xff;
	
	alpha += speed;
	MyMath::Clamp((float)alpha, 255.0f, 0.0f);

	return MyMath::GetRGB(red, green, blue, alpha);
}
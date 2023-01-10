#pragma once


class Fade {
public:
	Fade();
private:
	unsigned int red;
	unsigned int green;
	unsigned int blue;
	unsigned int alpha;

public:
	unsigned int FadeIn(unsigned int color,float speed);

	unsigned int FadeOut(unsigned int color,float speed);
};
#pragma once


class Fade {
public:
	Fade();
private:

public:
	/// <summary>
	/// Fade関数
	/// </summary>
	/// <param name="color">色</param>
	/// <param name="speed">速度</param>
	/// <param name="InOut">true:In false:Out</param>
	/// <returns></returns>
	static unsigned int FadeInOut(unsigned int color, float speed, bool InOut);

	static unsigned int Flash(unsigned int color, float speed);
};
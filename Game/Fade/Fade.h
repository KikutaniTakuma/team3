#pragma once


class Fade {
public:
	Fade();
private:

public:
	/// <summary>
	/// FadeŠÖ”
	/// </summary>
	/// <param name="color">F</param>
	/// <param name="speed">‘¬“x</param>
	/// <param name="InOut">true:In false:Out</param>
	/// <returns></returns>
	static unsigned int FadeInOut(unsigned int color, float speed, bool InOut);

	static unsigned int Flash(unsigned int color, float speed);
};
#include "Game/Fullscreen/Fullscreen.h"
#include <Novice.h>
#include "Game/KeyInput/KeyInput.h"

bool Screen::screenmode;

Screen::Screen() {
	screenmode = false;
}

//フルスクリーン切り替え-----------------------------------------------------------------------------
void Screen::Chang(int Key) {
	
	if (KeyInput::Pushed(Key))
	{
		if (screenmode == false)
		{
			screenmode = true;
		}
		else
		{
			screenmode = false;
		}
	}

	if (screenmode == false)
	{
		Novice::SetWindowMode(kWindowed);
	}
	else if (screenmode == true)
	{
		Novice::SetWindowMode(kFullscreen);
	}
}
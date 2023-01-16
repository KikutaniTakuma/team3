#include "Game/Fullscreen/Fullscreen.h"
#include <Novice.h>
#include "Game/KeyInput/KeyInput.h"

Screen::Screen() {

}

bool Screen::screenmode = false;

//�t���X�N���[���؂�ւ�-----------------------------------------------------------------------------
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
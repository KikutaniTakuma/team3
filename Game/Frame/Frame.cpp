#include "Frame.h"
#include "Game/Camera/Camera.h"
#include <cmath>

Frame::Frame(void):
	frame(0),
	startFlag(false),
	add(1.0f)
{}

void Frame::Start(float delta) {
	if (startFlag == true) {
		if (delta > 1.0f) {
			add *= delta;
		}
		frame += static_cast<unsigned long long>(floor(add));
		add = 1.0f;
	}
}

void Frame::Pause(void) {
	startFlag = false;
}

void Frame::Stop(void){
	startFlag = false;
	frame = 0;
}

void Frame::Restart(void) {
	startFlag = true;
}
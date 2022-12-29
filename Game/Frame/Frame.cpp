#include "Frame.h"

Frame::Frame(void) {
	frame = 0;
	startFlag = false;
}

void Frame::Start(void) {
	if (startFlag == true) {
		frame++;
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
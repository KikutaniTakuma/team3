#pragma once

//	スクリーン切り替え
class Screen {
public:
	Screen();
private:
	static bool screenmode;
public:
	static void Chang(int Key);
};


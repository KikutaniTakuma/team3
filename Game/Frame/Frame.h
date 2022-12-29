#pragma once

class Frame {
public:
	Frame(void);

	// フレーム
	unsigned long long frame;

	// スタートフラグ
	bool startFlag;

	// スタート関数
	void Start(void);

	// 停止
	void Pause(void);

	// ストップ
	void Stop(void);

	// リスタート
	void Restart(void);
};
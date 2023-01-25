#pragma once

class Frame {
public:
	Frame(void);

private:
	float add;

public:
	// フレーム
	unsigned long long frame;

	// スタートフラグ
	bool startFlag;

	// スタート関数
	void Start(float delta = 1.0f);

	// 停止
	void Pause(void);

	// ストップ
	void Stop(void);

	// リスタート
	void Restart(void);
};
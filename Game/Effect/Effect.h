#pragma once

#include "Game/Object/Object.h"
#include "Game/Frame/Frame.h"
#include "Game/Easing/Easing.h"
#include <vector>
#include <Novice.h>

class Effect : public Object {
protected:
	struct Emitter {
		Vector2D max; // 最大
		Vector2D min; // 最小
	};

	struct Particle {
		Vector2D pos; // pos
		Vector2D moveVec; // 移動ベクトル
		float spd; // 動くスピード
		float size; // 大きさ
		bool flg; // 今動いているかのフラグ
		int alpha; // アルファ値
		Easing ease; // イージング用
	};

public:
	Effect(Camera* camera);

public:
	// Effetを動かすフラグ(これをfalseにすれば強制的に終わらせられる)
	bool flg;
	// エミッターのポジション
	Vector2D worldPos;

protected:
	// エミッター
	Emitter emitter;

	// パーティクル用Quad
	Quad particleBuf;
	// パーティクルの可変長配列
	std::vector<Particle> particle;
	// パーティクルの量
	size_t particleNum;

	// フレーム
	Frame frame;

	// パーティクルを出す頻度
	int freq;
	// 加速用
	float acceleration;

	// パーティクルを一定の頻度で出すための値
	int count;

	// ブレンドモード
	BlendMode blend;

public:
	virtual void Update() override;
	virtual void Draw() override;
	virtual void Reset() override;
};
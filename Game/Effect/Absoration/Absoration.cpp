#include "Absoration.hpp"
#include "Game/MyMath/MyMath.h"
#include "Game/Mouse/Mouse.h"
#include "Game/KeyInput/KeyInput.h"

/// こちらは例でございます

Absoration::Absoration(Camera* camera) :
	Effect(camera)
{
	// ブレンドモード
	blend = BlendMode::kBlendModeAdd;

	// パーティクルの数
	particleNum = 1000;

	particle.resize(particleNum);

	// エミッターの大きさ
	emitter = { {-100.0f, -100.0f}, { 100.0f, 100.0f} };

	// 加算する値
	acceleration = 10.0f;

	// パーティクルの初期化
	for (auto& i : particle) {
		i = { Vector2D(), Vector2D(), 2.0f,0.0f,false,0,Easing(Vector2D(), pos.worldPos, 0.01f, Easing::EaseOutCirc) };
	}
}

void Absoration::Update() {
	// 基本的にはここをパクって

	if (flg) {
		for (int i = count; i < count + freq && count < particle.size(); i++) {
			if (!particle[i].flg) {
				/// 
				/// こんなかの処理を変えることで動きとかが変わる
				/// 

				// パーティクルが出ているか
				particle[i].flg = true;

				// ここでパーティクルの初期設定
				particle[i].size = static_cast<float>(MyMath::Random(20, 100));
				particle[i].pos = pos.worldPos;
				float len = static_cast<float>((MyMath::Random(static_cast<int>(emitter.max.x), static_cast<int>(emitter.max.x) * 2)));
				Vector2D rotate = { len,len };
				rotate.Rotate(static_cast<float>(MyMath::Random(0, 359)));
				particle[i].pos += rotate;
				particle[i].moveVec = { -particle[i].spd, -particle[i].spd };
				particle[i].moveVec.Rotate(static_cast<float>(MyMath::Random(0, 359)));

				// イージングを初期化
				particle[i].ease.Set(particle[i].pos, pos.worldPos, 0.01f, Easing::EaseOutCirc);
			}
		}
		count += freq;

		MyMath::Clamp(count, 0, static_cast<int>(particle.size()));
		if (count == particle.size()) {
			count = 0;
			flg = false;
		}

	}

	// ここで動きを制御
	for (auto& i : particle) {
		if (i.flg) {
			i.alpha += static_cast<int>(acceleration);
			i.pos = i.ease.Update();
			if (i.alpha >= 255) {
				i.alpha = 255;
			}

			// 終了処理
			if (!i.ease) {
				i = { Vector2D(), Vector2D(), 2.0f,0.0f,false,0,Easing(Vector2D(), pos.worldPos, 0.01f, Easing::EaseOutCirc) };
			}
		}
	}
}

void Absoration::Reset() {
	count = 0;
	particleBuf = Quad();
	blend = BlendMode::kBlendModeAdd;
	flg = true;

	pos.Set({ 640.0f,360.0f }, { 0.0f,0.0f });
	frame.Restart();
	worldPos = pos.worldPos;

	emitter = { {-100.0f, -100.0f}, { 100.0f, 100.0f} };

	acceleration = 10.0f;

	for (auto& i : particle) {
		i = { Vector2D(), Vector2D(), 2.0f,0.0f,false,0,Easing(Vector2D(), pos.worldPos, 0.01f, Easing::EaseOutCirc) };
	}
}

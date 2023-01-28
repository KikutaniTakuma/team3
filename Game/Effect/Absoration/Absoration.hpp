#pragma once

#include "Game/Effect/Effect.h"

// エフェクトをインクルードして継承
// コンストラクタにはCameraポインタを

class Absoration : public Effect {
public:
	Absoration(Camera* camera);

	void Update() override;
	void Reset() override;
};
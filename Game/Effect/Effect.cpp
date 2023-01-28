#include "Game/Effect/Effect.h"
#include "Game/MyMath/MyMath.h"
#include "Game/Mouse/Mouse.h"
#include "Game/KeyInput/KeyInput.h"
#include "Game/Texture/Texture.h"

Effect::Effect(Camera* camera) :
	Object(camera),
	acceleration(2.0f),
	emitter({ {-3.0f, -3.0f}, { 3.0f, 3.0f} }),
	freq(5),
	count(0),
	particleBuf(Quad()),
	particleNum(1000),
	particle(particleNum),
	blend(BlendMode::kBlendModeAdd),
	flg(true)
{
	
}

void Effect::Update() {
}

void Effect::Draw() {
	Novice::SetBlendMode(blend);

	for (auto& i : particle) {
		if (i.flg) {
			particleBuf.Set(i.pos, { i.size,i.size });
			camera->DrawQuad(particleBuf, whiteBox, 0, false, 0xffff0000 + i.alpha);
		}
	}

	Novice::SetBlendMode(kBlendModeNormal);
}

void Effect::Reset() {

}
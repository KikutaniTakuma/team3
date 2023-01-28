#include "Absoration.hpp"
#include "Game/MyMath/MyMath.h"
#include "Game/Mouse/Mouse.h"
#include "Game/KeyInput/KeyInput.h"

/// ������͗�ł������܂�

Absoration::Absoration(Camera* camera) :
	Effect(camera)
{
	// �u�����h���[�h
	blend = BlendMode::kBlendModeAdd;

	// �p�[�e�B�N���̐�
	particleNum = 1000;

	particle.resize(particleNum);

	// �G�~�b�^�[�̑傫��
	emitter = { {-100.0f, -100.0f}, { 100.0f, 100.0f} };

	// ���Z����l
	acceleration = 10.0f;

	// �p�[�e�B�N���̏�����
	for (auto& i : particle) {
		i = { Vector2D(), Vector2D(), 2.0f,0.0f,false,0,Easing(Vector2D(), pos.worldPos, 0.01f, Easing::EaseOutCirc) };
	}
}

void Absoration::Update() {
	// ��{�I�ɂ͂������p�N����

	if (flg) {
		for (int i = count; i < count + freq && count < particle.size(); i++) {
			if (!particle[i].flg) {
				/// 
				/// ����Ȃ��̏�����ς��邱�Ƃœ����Ƃ����ς��
				/// 

				// �p�[�e�B�N�����o�Ă��邩
				particle[i].flg = true;

				// �����Ńp�[�e�B�N���̏����ݒ�
				particle[i].size = static_cast<float>(MyMath::Random(20, 100));
				particle[i].pos = pos.worldPos;
				float len = static_cast<float>((MyMath::Random(static_cast<int>(emitter.max.x), static_cast<int>(emitter.max.x) * 2)));
				Vector2D rotate = { len,len };
				rotate.Rotate(static_cast<float>(MyMath::Random(0, 359)));
				particle[i].pos += rotate;
				particle[i].moveVec = { -particle[i].spd, -particle[i].spd };
				particle[i].moveVec.Rotate(static_cast<float>(MyMath::Random(0, 359)));

				// �C�[�W���O��������
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

	// �����œ����𐧌�
	for (auto& i : particle) {
		if (i.flg) {
			i.alpha += static_cast<int>(acceleration);
			i.pos = i.ease.Update();
			if (i.alpha >= 255) {
				i.alpha = 255;
			}

			// �I������
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

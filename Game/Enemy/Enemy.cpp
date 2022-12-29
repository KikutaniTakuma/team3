#include "Game/Enemy/Enemy.h"
#include "Game/Camera/Camera.h"
#include "Game/IOcsv/IOcsv.h"
#include "Game/KeyInput/KeyInput.h"

Enemy::Enemy(Camera* cameraPointa)
	:Object(cameraPointa)
{
	std::vector<float> data;
	if(IOcsv::Input("./Data/EnemyData.csv", data))
	{
		pos.Set({ 640.0f, 360.0f }, { 32.0f, 32.0f });
	}
	else {
		pos.Set({ data[0], data[1] }, { data[2], data[3] });
	}
}

void Enemy::Update() {
	
}

void Enemy::Draw(Texture& tex) {
	camera->DrawQuad(drawPos, tex, 0, false);
}

void Enemy::Reset() {
	std::vector<float> data;
	if (IOcsv::Input("./Data/EnemyData.csv", data))
	{
		pos.Set({ 640.0f, 360.0f }, { 32.0f, 32.0f });
	}
	else {
		pos.Set({ data[0], data[1] }, { data[2], data[3] });
	}
}
#include "Player.h"
#include "Game/Vector2D/Vector2D.h"
#include "Game/Matrix3x3/Matrix3x3.h"
#include "Game/KeyInput/KeyInput.h"
#include "Game/Mouse/Mouse.h"
#include "Game/MyMath/MyMath.h"
#include "Game/IOcsv/IOcsv.h"
#include "Game/MapChip/MapChip.h"
#include "Game/GamePad/GamePad.h"
#include "Game/Camera/Camera.h"
#include "Game/Quad/Quad.h"
#include "Game/Texture/Texture.h"
#include "Game/Quad/Quad.h"
#include <Novice.h>

#define _USE_MATH_DEFINES
#include <math.h>

// 規定コンストラクタ
Player::Player(Camera* camera):
	Object(camera),
	highSpd(7.0f)
{
	size = new Vector2D;
	tentativPos = new Vector2D;
	moveVec = new Vector2D;
	
	std::vector<float> data;

	if (!IOcsv::Input("./Data/playerData.csv", data) && data.size() == 10) {
		*size = {
			data[3],
			data[4]
		};

		pos.Set(MapChip::getPlyPos(), *size);

		nmlSpd = data[2];

		jumpValue = data[5];
		jumpSeconsdValue = data[6];

		gravity = data[7];

		deadZone = static_cast<unsigned short>(data[8]);

		flgZeroGravity = static_cast<bool>(data[9]);
	}
	else {
		pos.worldPos = {
		640.0f,
		140.0f
		};

		nmlSpd = 10.0f;

		*size = {
		32.0f,
		32.0f
		};

		jumpValue = 20.0f;

		jumpSeconsdValue = 15.0f;

		gravity = 0.5f;

		deadZone = 5000;

		flgZeroGravity = false;

		// データバッファー
		data = {
			pos.worldPos.x, pos.worldPos.y,
			nmlSpd,
			size->x, size->y,
			jumpValue, jumpSeconsdValue, gravity,
			static_cast<float>(deadZone),
			static_cast<float>(flgZeroGravity)
		};
		std::vector<std::string> coment = {
			"PosX", "PosY",
			"Speed",
			"SizeX", "SizeY",
			"jumpValue", "jumpSecondValue", "GravityValue",
			"Gamepad Stick Deadzone",
			"Gravity On Off"
		};

		IOcsv::Output("./Data/playerData.csv", data, coment);
	}

	*tentativPos = pos.worldPos;

	flgJump = false;

	flgJumpSecond = false;

	flgGravity = true;

	tex.insert(std::make_pair(Direction::FRONT, Texture("./Resources/Player/SlimeFront.png",256,32,32)));
	tex.insert(std::make_pair(Direction::BACK, Texture("./Resources/Player/SlimeBack.png", 256, 32, 32)));
	tex.insert(std::make_pair(Direction::RIGHT, Texture("./Resources/Player/SlimeRight.png", 256, 32, 32)));
	tex.insert(std::make_pair(Direction::LEFT, Texture("./Resources/Player/SlimeLeft.png", 256, 32, 32)));
}

// デストラクタ
Player::~Player() {
	delete tentativPos;
	delete size;
	delete moveVec;
}

// 更新処理関数
void Player::Update() {
	this->Move();

	this->Collision();

	pos.worldMatrix.Translate(pos.worldPos);

	/*if (!(MapChip::GetNum(pos.worldPos).x < 20.0f) && !(MapChip::GetNum(pos.worldPos).x > 179.0f) &&
		!(MapChip::GetNum(pos.worldPos).y < 20.0f )&& !(MapChip::GetNum(pos.worldPos).y > 180.0f)) {
	}*/
	camera->worldPos = pos.worldPos;
}

// 描画処理関数
void Player::Draw() {
	camera->DrawQuad(pos, tex[dir], 6.0f, MyMath::GetRGB(255,255,255,255));

#ifdef _DEBUG
	/*Novice::ScreenPrintf(0, 20, "X = %f", pos.worldPos.x);
	Novice::ScreenPrintf(0, 40, "Y = %f", pos.worldPos.y);*/
#endif 
	/*Novice::ScreenPrintf(0, 20, "breakPer = %f", MapChip::GetBlockBreakPer());*/
}

// 移動関数
void Player::Move() {
	if (MapChip::GetType(pos.worldPos) == static_cast<int>(MapChip::Type::SACRED)) {
		spd = highSpd;
	}
	else {
		spd = nmlSpd;
	}

	moveVec->x = 0.0f;
	if (flgZeroGravity == true) {
		moveVec->y = 0.0f;

		if (KeyInput::LongPush(DIK_W)||KeyInput::LongPush(DIK_UP)) {
			moveVec->y += spd;
		}
		else if (Gamepad::getStick(Gamepad::Stick::LEFT_Y) > deadZone) {
			moveVec->y = Gamepad::getStick(Gamepad::Stick::LEFT_Y);
		}
		if (KeyInput::LongPush(DIK_S)|| KeyInput::LongPush(DIK_DOWN)) {
			moveVec->y -= spd;
		}
		else if (Gamepad::getStick(Gamepad::Stick::LEFT_Y) < -1 * deadZone) {
			moveVec->y = Gamepad::getStick(Gamepad::Stick::LEFT_Y);
		}
		if (KeyInput::LongPush(DIK_A)|| KeyInput::LongPush(DIK_LEFT)) {
			moveVec->x -= spd;
		}
		else if (Gamepad::getStick(Gamepad::Stick::LEFT_X) < -1 * deadZone) {
			moveVec->x = Gamepad::getStick(Gamepad::Stick::LEFT_X);
		}
		if (KeyInput::LongPush(DIK_D)|| KeyInput::LongPush(DIK_RIGHT)) {
			moveVec->x += spd;
		}
		else if (Gamepad::getStick(Gamepad::Stick::LEFT_X) > deadZone) {
			moveVec->x = Gamepad::getStick(Gamepad::Stick::LEFT_X);
		}

		Vector2D posBuff = *moveVec;

		if (MyMath::PythagoreanTheorem(posBuff.x, posBuff.y) != 0) {
			posBuff.x = MyMath::Normalize(posBuff.x, posBuff.y);
			posBuff.y = MyMath::Normalize(posBuff.y, posBuff.x);
		}

		*moveVec = posBuff * spd;
	}
	else {
		if (KeyInput::LongPush(DIK_A) ||
			Gamepad::getStick(Gamepad::Stick::LEFT_X) < -1 * deadZone) {
			moveVec->x -= spd;
		}
		if (KeyInput::LongPush(DIK_D) ||
			Gamepad::getStick(Gamepad::Stick::LEFT_X) > deadZone) {
			moveVec->x += spd;
		}
	}

	if (flgZeroGravity == false) {
		this->Jump();
	}

	if (flgGravity == true && flgZeroGravity == false) {
		moveVec->y -= gravity;
		if (moveVec->y <= static_cast<float>(-1 * MapChip::kMapSize)) {
			moveVec->y = static_cast<float>(-1 * MapChip::kMapSize);
		}
		if (moveVec->y > static_cast<float>(MapChip::kMapSize)) {
			moveVec->y = static_cast<float>(MapChip::kMapSize);
		}
	}

	*tentativPos += *moveVec * camera->getDelta() * static_cast<float>(Camera::getHitStop());

	if (tentativPos->x > MapChip::getMapMaxPosX() - pos.getSize().x / 2.0f) {
		tentativPos->x = MapChip::getMapMaxPosX() - pos.getSize().x / 2.0f;
	}
	if (tentativPos->x < MapChip::getMapMinPosX() + pos.getSize().x / 2.0f) {
		tentativPos->x = MapChip::getMapMinPosX() + pos.getSize().x / 2.0f;
	}
	if (tentativPos->y > MapChip::getMapMaxPosY() - pos.getSize().y / 2.0f) {
		tentativPos->y = MapChip::getMapMaxPosY() - pos.getSize().y / 2.0f;
	}
	if (tentativPos->y < MapChip::getMapMinPosY() + pos.getSize().y / 2.0f) {
		tentativPos->y = MapChip::getMapMinPosY() + pos.getSize().y / 2.0f;
	}

	if (moveVec->x > 0.0f) {
		dir = Direction::RIGHT;
		if (moveVec->y > 0.0f && moveVec->y > moveVec->x) {
			dir = Direction::BACK;
		}
		else if (moveVec->y < 0.0f && -moveVec->y > moveVec->x) {
			dir = Direction::FRONT;
		}
	}
	else if (moveVec->x < 0.0f) {
		dir = Direction::LEFT;
		if (moveVec->y > 0.0f && -moveVec->y < moveVec->x) {
			dir = Direction::BACK;
		}
		else if (moveVec->y < 0.0f && moveVec->y < moveVec->x) {
			dir = Direction::FRONT;
		}
	}
	else if (moveVec->y > 0.0f) {
		dir = Direction::BACK;
	}
	else if (moveVec->y < 0.0f) {
		dir = Direction::FRONT;
	}
}

// ジャンプ関数
void Player::Jump() {
	if (KeyInput::Pushed(DIK_SPACE) && flgJump == false ||
		Gamepad::Pushed(Gamepad::Button::A) && flgJump == false) {
		flgJump = true;
		moveVec->y = jumpValue;
		flgGravity = true;
	}
	else if (KeyInput::Pushed(DIK_SPACE) && flgJump == true && flgJumpSecond == false ||
		Gamepad::Pushed(Gamepad::Button::A) && flgJump == true && flgJumpSecond == false) {
		flgJumpSecond = true;
		moveVec->y = jumpSeconsdValue;
	}
}

// 当たり判定関数
void Player::Collision() {
	Vector2D LeftTop = { pos.getSizeLeftTop().x + tentativPos->x, pos.getSizeLeftTop().y + tentativPos->y };

	Vector2D RightTop = { pos.getSizeRightTop().x + tentativPos->x - 1.0f, pos.getSizeRightTop().y + tentativPos->y };

	Vector2D LeftUnder = { pos.getSizeLeftUnder().x + tentativPos->x, pos.getSizeLeftUnder().y + tentativPos->y + 1.0f };

	Vector2D RightUnder = { pos.getSizeRightUnder().x + tentativPos->x - 1.0f, pos.getSizeRightUnder().y + tentativPos->y + 1.0f };

	// もし上に向かっていたら
	if (moveVec->y > 0.0f) {
		// もし右移動していたら
		if (moveVec->x > 0.0f) {
			// 右上にのみブロックがある
			if (MapChip::Collision(RightTop) && !MapChip::Collision(LeftTop) && !MapChip::Collision(RightUnder)) {
				Vector2D mapPos = MapChip::GetPos(RightTop);

				if (RightTop.x - mapPos.x < RightTop.y - mapPos.y) {
					mapPos.x -= MapChip::kMapSize;

					tentativPos->x = mapPos.x + size->x / 2.0f;
				}
				else if (RightTop.x - mapPos.x > RightTop.y - mapPos.y) {
					mapPos.y -= MapChip::kMapSize;

					tentativPos->y = mapPos.y + size->y / 2.0f;
				}
				else if (RightTop.x - mapPos.x == RightTop.y - mapPos.y) {
					mapPos.y -= MapChip::kMapSize;
					tentativPos->y = mapPos.y + size->y / 2.0f;
				}
			}
			// 左上にのみブロックがある
			else if (!MapChip::Collision(RightTop) && MapChip::Collision(LeftTop) && !MapChip::Collision(RightUnder)) {
				Vector2D mapPos = MapChip::GetPos(LeftTop);

				if ((mapPos.x + MapChip::kMapSize) - LeftTop.x < LeftTop.y - mapPos.y) {
					mapPos.x += MapChip::kMapSize;

					tentativPos->x = mapPos.x + size->x / 2.0f;
				}
				else if ((mapPos.x + MapChip::kMapSize) - LeftTop.x > LeftTop.y - mapPos.y) {
					mapPos.y -= MapChip::kMapSize;
					tentativPos->y = mapPos.y + size->y / 2.0f;
				}
				else if ((mapPos.x + MapChip::kMapSize) - LeftTop.x == LeftTop.y - mapPos.y) {
					mapPos.y -= MapChip::kMapSize;
					tentativPos->y = mapPos.y + size->y / 2.0f;
				}
			}
			// 右下にのみブロックがある
			else if (!MapChip::Collision(RightTop) && !MapChip::Collision(LeftTop) && MapChip::Collision(RightUnder)) {
				Vector2D mapPos = MapChip::GetPos(RightUnder);

				if (static_cast<int>(mapPos.y) % MapChip::kMapSize == 0) {
					RightUnder.y -= 1.0f;
				}
				mapPos = MapChip::GetPos(RightUnder);

				if (RightUnder.x - mapPos.x < (mapPos.y + MapChip::kMapSize) - RightUnder.y) {
					mapPos.x -= MapChip::kMapSize;
					tentativPos->x = mapPos.x + size->x / 2.0f;
				}
				else if (RightUnder.x - mapPos.x > (mapPos.y + MapChip::kMapSize) - RightUnder.y) {
					mapPos.y += MapChip::kMapSize;

					tentativPos->y = mapPos.y + size->y / 2.0f;

					flgJump = false;
					flgJumpSecond = false;
					flgGravity = false;

					moveVec->y = 0.0f;
				}
				else if (RightUnder.x - mapPos.x == (mapPos.y + MapChip::kMapSize) - RightUnder.y) {
					mapPos.y += MapChip::kMapSize;

					tentativPos->y = mapPos.y + size->y / 2.0f;

					flgJump = false;
					flgJumpSecond = false;
					flgGravity = false;

					moveVec->y = 0.0f;
				}
			}

			// 上にブロックがある
			else if (MapChip::Collision(RightTop) && MapChip::Collision(LeftTop) && !MapChip::Collision(RightUnder)) {
				Vector2D mapPos = MapChip::GetPos(RightTop);
				mapPos.y -= MapChip::kMapSize;

				tentativPos->y = mapPos.y + size->y / 2.0f;
			}
			// 右側にブロックがある
			else if (MapChip::Collision(RightTop) && !MapChip::Collision(LeftTop) && MapChip::Collision(RightUnder)) {
				Vector2D mapPos = MapChip::GetPos(RightTop);
				mapPos.x -= MapChip::kMapSize;

				tentativPos->x = mapPos.x + size->x / 2.0f;
			}
			// 右上に進めない
			else if (MapChip::Collision(RightTop) && MapChip::Collision(LeftTop) && MapChip::Collision(RightUnder) || 
				     !MapChip::Collision(RightTop) && MapChip::Collision(LeftTop) && MapChip::Collision(RightUnder)) {
				Vector2D mapPos = MapChip::GetPos(RightTop);
				mapPos.y -= MapChip::kMapSize;

				tentativPos->y = mapPos.y + size->y / 2.0f;

				mapPos = MapChip::GetPos(RightTop);
				mapPos.x -= MapChip::kMapSize;

				tentativPos->x = mapPos.x + size->x / 2.0f;
			}
		}

		// もし左移動していたら
		else if ((moveVec->x < 0.0f)) {
			// 左上にのみブロックがある
			if (MapChip::Collision(LeftTop) && !MapChip::Collision(RightTop) && !MapChip::Collision(LeftUnder)) {
				Vector2D mapPos = MapChip::GetPos(LeftTop);

				if ((mapPos.x + MapChip::kMapSize) - LeftTop.x < LeftTop.y - mapPos.y) {
					mapPos.x += MapChip::kMapSize;

					tentativPos->x = mapPos.x + size->x / 2.0f;
				}
				else if ((mapPos.x + MapChip::kMapSize) - LeftTop.x > LeftTop.y - mapPos.y) {
					mapPos.y -= MapChip::kMapSize;
					tentativPos->y = mapPos.y + size->y / 2.0f;
				}
				else if ((mapPos.x + MapChip::kMapSize) - LeftTop.x == LeftTop.y - mapPos.y) {
					mapPos.y -= MapChip::kMapSize;
					tentativPos->y = mapPos.y + size->y / 2.0f;
				}
			}
			// 右上にのみブロックがある
			else if (!MapChip::Collision(LeftTop) && MapChip::Collision(RightTop) && !MapChip::Collision(LeftUnder)) {
				Vector2D mapPos = MapChip::GetPos(RightTop);

				if (RightTop.x - mapPos.x < RightTop.y - mapPos.y) {
					mapPos.x -= MapChip::kMapSize;

					tentativPos->x = mapPos.x + size->x / 2.0f;
				}
				else if (RightTop.x - mapPos.x > RightTop.y - mapPos.y) {
					mapPos.y -= MapChip::kMapSize;

					tentativPos->y = mapPos.y + size->y / 2.0f;
				}
				else if (RightTop.x - mapPos.x == RightTop.y - mapPos.y) {
					mapPos.y -= MapChip::kMapSize;
					tentativPos->y = mapPos.y + size->y / 2.0f;
				}
			}
			// 左下にのみブロックがある
			else if (!MapChip::Collision(LeftTop) && !MapChip::Collision(RightTop) && MapChip::Collision(LeftUnder)) {
				Vector2D mapPos = MapChip::GetPos(LeftUnder);

				if (static_cast<int>(mapPos.y) % MapChip::kMapSize == 0) {
					LeftUnder.y -= 1.0f;
				}
				mapPos = MapChip::GetPos(LeftUnder);

				if ((mapPos.x + MapChip::kMapSize) - LeftUnder.x < (mapPos.y + MapChip::kMapSize) - LeftUnder.y) {
					mapPos.x += MapChip::kMapSize;

					tentativPos->x = mapPos.x + size->x / 2.0f;
				}
				else if ((mapPos.x + MapChip::kMapSize) - LeftUnder.x > (mapPos.y + MapChip::kMapSize) - LeftUnder.y) {
					mapPos.y += MapChip::kMapSize;

					tentativPos->y = mapPos.y + size->y / 2.0f;

					flgJump = false;
					flgJumpSecond = false;
					flgGravity = false;

					moveVec->y = 0.0f;
				}
				else if ((mapPos.x + MapChip::kMapSize) - LeftUnder.x == (mapPos.y + MapChip::kMapSize) - LeftUnder.y) {
					mapPos.y += MapChip::kMapSize;

					tentativPos->y = mapPos.y + size->y / 2.0f;


					flgJump = false;
					flgJumpSecond = false;
					flgGravity = false;

					moveVec->y = 0.0f;
				}
			}

			// 上にブロックがある
			else if (MapChip::Collision(LeftTop) && MapChip::Collision(RightTop) && !MapChip::Collision(LeftUnder)) {
				Vector2D mapPos = MapChip::GetPos(LeftTop);
				mapPos.y -= MapChip::kMapSize;

				tentativPos->y = mapPos.y + size->y / 2.0f;
			}
			// 左側にブロックがある
			else if (MapChip::Collision(LeftTop) && !MapChip::Collision(RightTop) && MapChip::Collision(LeftUnder)) {
				Vector2D mapPos = MapChip::GetPos(LeftTop);
				mapPos.x += MapChip::kMapSize;

				tentativPos->x = mapPos.x + size->x / 2.0f;
			}
			// 左上に進めない
			else if (MapChip::Collision(LeftTop) && MapChip::Collision(RightTop) && MapChip::Collision(LeftUnder) || 
					 !MapChip::Collision(LeftTop) && MapChip::Collision(RightTop) && MapChip::Collision(LeftUnder)) {
				Vector2D mapPos = MapChip::GetPos(LeftTop);
				mapPos.y -= MapChip::kMapSize;

				tentativPos->y = mapPos.y + size->y / 2.0f;

				mapPos = MapChip::GetPos(LeftTop);
				mapPos.x += MapChip::kMapSize;

				tentativPos->x = mapPos.x + size->x / 2.0f;
			}
		}

		else if (MapChip::Collision(LeftTop)) {
			Vector2D mapPos = MapChip::GetPos(LeftTop);
			mapPos.y -= MapChip::kMapSize;

			tentativPos->y = mapPos.y + size->y / 2.0f;

		}
		else if (MapChip::Collision(RightTop)) {
			Vector2D mapPos = MapChip::GetPos(RightTop);
			mapPos.y -= MapChip::kMapSize;

			tentativPos->y = mapPos.y + size->y / 2.0f;
		}
	}

	// もし下移動していたら
	else if (moveVec->y < 0.0f) {
		// 右移動
		if (moveVec->x > 0.0f) {
			// 右下にのみブロックがある
			if (!MapChip::Collision(LeftUnder) && MapChip::Collision(RightUnder) && !MapChip::Collision(RightTop)) {
				Vector2D mapPos = MapChip::GetPos(RightUnder);

				if (static_cast<int>(mapPos.y) % MapChip::kMapSize == 0) {
					RightUnder.y -= 1.0f;
				}
				mapPos = MapChip::GetPos(RightUnder);

				if (RightUnder.x - mapPos.x < (mapPos.y + MapChip::kMapSize) - RightUnder.y) {
					mapPos.x -= MapChip::kMapSize;
					tentativPos->x = mapPos.x + size->x / 2.0f;
				}
				else if (RightUnder.x - mapPos.x > (mapPos.y + MapChip::kMapSize) - RightUnder.y) {
					mapPos.y += MapChip::kMapSize;

					tentativPos->y = mapPos.y + size->y / 2.0f;

					flgJump = false;
					flgJumpSecond = false;
					flgGravity = false;

					moveVec->y = 0.0f;
				}
				else if (RightUnder.x - mapPos.x == (mapPos.y + MapChip::kMapSize) - RightUnder.y) {
					mapPos.y += MapChip::kMapSize;

					tentativPos->y = mapPos.y + size->y / 2.0f;

					flgJump = false;
					flgJumpSecond = false;
					flgGravity = false;

					moveVec->y = 0.0f;
				}
			}
			// 左下にのみブロックがある
			else if (MapChip::Collision(LeftUnder) && !MapChip::Collision(RightUnder) && !MapChip::Collision(RightTop)) {
				Vector2D mapPos = MapChip::GetPos(LeftUnder);
				if (static_cast<int>(mapPos.y) % MapChip::kMapSize == 0) {
					LeftUnder.y -= 1.0f;
				}
				mapPos = MapChip::GetPos(LeftUnder);
				mapPos.y += MapChip::kMapSize;

				tentativPos->y = mapPos.y + size->y / 2.0f;

				flgJump = false;
				flgJumpSecond = false;
				flgGravity = false;

				moveVec->y = 0.0f;
			}
			// 右上のみにブロックがある
			else if (!MapChip::Collision(LeftUnder) && !MapChip::Collision(RightUnder) && MapChip::Collision(RightTop)) {
				Vector2D mapPos = MapChip::GetPos(RightTop);

				mapPos.x -= MapChip::kMapSize;
				tentativPos->x = mapPos.x + size->x / 2.0f;
			}

			// 下にブロックがある
			else if (MapChip::Collision(LeftUnder) && MapChip::Collision(RightUnder) && !MapChip::Collision(RightTop)) {
				Vector2D mapPos = MapChip::GetPos(RightUnder);
				if (static_cast<int>(mapPos.y) % MapChip::kMapSize == 0) {
					LeftUnder.y -= 1.0f;
				}
				mapPos = MapChip::GetPos(LeftUnder);
				mapPos.y += MapChip::kMapSize;

				tentativPos->y = mapPos.y + size->y / 2.0f;

				flgJump = false;
				flgJumpSecond = false;
				flgGravity = false;

				moveVec->y = 0.0f;
			}
			// 右にブロックがある
			else if (!MapChip::Collision(LeftUnder) && MapChip::Collision(RightUnder) && MapChip::Collision(RightTop)) {
				Vector2D mapPos = MapChip::GetPos(RightTop);

				mapPos.x -= MapChip::kMapSize;
				tentativPos->x = mapPos.x + size->x / 2.0f;
			}
			// 右下に進めない
			else if (MapChip::Collision(LeftUnder) && MapChip::Collision(RightUnder) && MapChip::Collision(RightTop) || 
					 MapChip::Collision(LeftUnder) && !MapChip::Collision(RightUnder) && MapChip::Collision(RightTop)) {
				Vector2D mapPos = MapChip::GetPos(RightUnder);
				if (static_cast<int>(mapPos.y) % MapChip::kMapSize == 0) {
					RightUnder.y -= 1.0f;
				}
				mapPos = MapChip::GetPos(RightUnder);

				mapPos.y += MapChip::kMapSize;

				tentativPos->y = mapPos.y + size->y / 2.0f;

				mapPos.x -= MapChip::kMapSize;
				tentativPos->x = mapPos.x + size->x / 2.0f;

				flgJump = false;
				flgJumpSecond = false;
				flgGravity = false;

				moveVec->y = 0.0f;
			}
		}
		// 左移動してたら
		else if (moveVec->x < 0.0f) {
			// 左下にしかブロックがない
			if (MapChip::Collision(LeftUnder) && !MapChip::Collision(RightUnder) && !MapChip::Collision(LeftTop)) {
				Vector2D mapPos = MapChip::GetPos(LeftUnder);

				if (static_cast<int>(mapPos.y) % MapChip::kMapSize == 0) {
					LeftUnder.y -= 1.0f;
				}
				mapPos = MapChip::GetPos(LeftUnder);

				if ((mapPos.x + MapChip::kMapSize) - LeftUnder.x < (mapPos.y + MapChip::kMapSize) - LeftUnder.y) {
					mapPos.x += MapChip::kMapSize;

					tentativPos->x = mapPos.x + size->x / 2.0f;
				}
				else if ((mapPos.x + MapChip::kMapSize) - LeftUnder.x > (mapPos.y + MapChip::kMapSize) - LeftUnder.y) {
					mapPos.y += MapChip::kMapSize;

					tentativPos->y = mapPos.y + size->y / 2.0f;

					flgJump = false;
					flgJumpSecond = false;
					flgGravity = false;

					moveVec->y = 0.0f;
				}
				else if ((mapPos.x + MapChip::kMapSize) - LeftUnder.x == (mapPos.y + MapChip::kMapSize) - LeftUnder.y) {
					mapPos.y += MapChip::kMapSize;

					tentativPos->y = mapPos.y + size->y / 2.0f;


					flgJump = false;
					flgJumpSecond = false;
					flgGravity = false;

					moveVec->y = 0.0f;
				}
			}
			// 右下にのみブロックがある
			else if (!MapChip::Collision(LeftUnder) && MapChip::Collision(RightUnder) && !MapChip::Collision(LeftTop)) {
				Vector2D mapPos = MapChip::GetPos(RightUnder);
				if (static_cast<int>(mapPos.y) % MapChip::kMapSize == 0) {
					RightUnder.y -= 1.0f;
				}
				mapPos = MapChip::GetPos(RightUnder);

				mapPos.y += MapChip::kMapSize;

				tentativPos->y = mapPos.y + size->y / 2.0f;

				flgJump = false;
				flgJumpSecond = false;
				flgGravity = false;

				moveVec->y = 0.0f;
			}
			// 左上にのみブロックがある
			else if (!MapChip::Collision(LeftUnder) && !MapChip::Collision(RightUnder) && MapChip::Collision(LeftTop)) {
				Vector2D mapPos = MapChip::GetPos(LeftTop);
				mapPos.x += MapChip::kMapSize;

				tentativPos->x = mapPos.x + size->x / 2.0f;
			}

			// 下にブロックがある
			else if (MapChip::Collision(LeftUnder) && MapChip::Collision(RightUnder) && !MapChip::Collision(LeftTop)) {
				Vector2D mapPos = MapChip::GetPos(LeftUnder);
				if (static_cast<int>(mapPos.y) % MapChip::kMapSize == 0) {
					LeftUnder.y -= 1.0f;
				}
				mapPos = MapChip::GetPos(LeftUnder);

				mapPos.y += MapChip::kMapSize;

				tentativPos->y = mapPos.y + size->y / 2.0f;

				flgJump = false;
				flgJumpSecond = false;
				flgGravity = false;

				moveVec->y = 0.0f;
			}
			// 左にブロックがある
			else if (MapChip::Collision(LeftUnder) && !MapChip::Collision(RightUnder) && MapChip::Collision(LeftTop)) {
				Vector2D mapPos = MapChip::GetPos(LeftTop);
				mapPos.x += MapChip::kMapSize;

				tentativPos->x = mapPos.x + size->x / 2.0f;
			}
			// 左下に進めない
			else if (MapChip::Collision(LeftUnder) && MapChip::Collision(RightUnder) && MapChip::Collision(LeftTop) || 
					 !MapChip::Collision(LeftUnder) && MapChip::Collision(RightUnder) && MapChip::Collision(LeftTop)) {
				Vector2D mapPos = MapChip::GetPos(LeftUnder);
				if (static_cast<int>(mapPos.y) % MapChip::kMapSize == 0) {
					LeftUnder.y -= 1.0f;
				}
				mapPos = MapChip::GetPos(LeftUnder);

				mapPos.y += MapChip::kMapSize;

				tentativPos->y = mapPos.y + size->y / 2.0f;

				mapPos = MapChip::GetPos(LeftTop);
				mapPos.x += MapChip::kMapSize;

				tentativPos->x = mapPos.x + size->x / 2.0f;

				flgJump = false;
				flgJumpSecond = false;
				flgGravity = false;

				moveVec->y = 0.0f;
			}
		}

		else if (MapChip::Collision(LeftUnder) || MapChip::Collision(RightUnder)) {
			Vector2D mapPos = MapChip::GetPos(LeftUnder);
			if (static_cast<int>(mapPos.y) % MapChip::kMapSize == 0) {
				LeftUnder.y -= 1.0f;
			}
			mapPos = MapChip::GetPos(LeftUnder);

			mapPos.y += MapChip::kMapSize;
			tentativPos->y = mapPos.y + size->y / 2.0f;
			flgJump = false;
			flgJumpSecond = false;
			flgGravity = false;

			moveVec->y = 0.0f;
		}
	}
	else if (moveVec->x > 0.0f) {
		if (MapChip::Collision(RightTop) || MapChip::Collision(RightUnder)) {
			Vector2D mapPos = MapChip::GetPos(RightTop);
			mapPos.x -= MapChip::kMapSize;

			tentativPos->x = mapPos.x + size->x / 2.0f;
		}
	}
	else if (moveVec->x < 0.0f) {
		if (MapChip::Collision(LeftTop) || MapChip::Collision(LeftUnder)) {
			Vector2D mapPos = MapChip::GetPos(LeftTop);
			mapPos.x += MapChip::kMapSize;

			tentativPos->x = mapPos.x + size->x / 2.0f;
		}
	}
	else {
		if (MapChip::Collision(LeftTop) || MapChip::Collision(RightTop)) {
			Vector2D mapPos = MapChip::GetPos(LeftTop);
			mapPos.y -= MapChip::kMapSize;

			tentativPos->y = mapPos.y + size->y / 2.0f;
		}
		if (MapChip::Collision(LeftUnder) || MapChip::Collision(RightUnder)) {
			Vector2D mapPos = MapChip::GetPos(LeftUnder);
			mapPos.y += MapChip::kMapSize;
			tentativPos->y = mapPos.y + size->y / 2.0f;
		}
		if (MapChip::Collision(RightTop) || MapChip::Collision(RightUnder)) {
			Vector2D mapPos = MapChip::GetPos(RightTop);
			mapPos.x -= MapChip::kMapSize;

			tentativPos->x = mapPos.x + size->x / 2.0f;
		}
		if (MapChip::Collision(LeftTop) || MapChip::Collision(LeftUnder)) {
			Vector2D mapPos = MapChip::GetPos(LeftTop);
			mapPos.x += MapChip::kMapSize;

			tentativPos->x = mapPos.x + size->x / 2.0f;
		}
	}

	LeftTop = { pos.getSizeLeftTop().x + tentativPos->x, pos.getSizeLeftTop().y + tentativPos->y };

	RightTop = { pos.getSizeRightTop().x + tentativPos->x - 1.0f, pos.getSizeRightTop().y + tentativPos->y };

	LeftUnder = { pos.getSizeLeftUnder().x + tentativPos->x , pos.getSizeLeftUnder().y + tentativPos->y + 1.0f };

	RightUnder = { pos.getSizeRightUnder().x + tentativPos->x - 1.0f, pos.getSizeRightUnder().y + tentativPos->y + 1.0f };

	if (!MapChip::Collision(LeftUnder) && !MapChip::Collision(RightUnder)) {
		flgGravity = true;
	}

	if (!MapChip::Collision(RightTop) && !MapChip::Collision(LeftTop) && !MapChip::Collision(RightUnder) && !MapChip::Collision(LeftUnder)) {
		pos.worldPos = *tentativPos;
	}
}

//ホットリロード関数
void Player::Reset() {
	// データバッファー
	std::vector<float> data;

	if (!IOcsv::Input("./Data/playerData.csv", data)) {
		*size = {
			data[3],
			data[4]
		};

		pos.Set({ data[0],data[1] }, *size);

		nmlSpd = data[2];

		jumpValue = data[5];
		jumpSeconsdValue = data[6];

		gravity = data[7];

		deadZone = static_cast<unsigned short>(data[8]);

		flgZeroGravity = static_cast<bool>(data[9]);
	}

	*tentativPos = pos.worldPos;
}

// getter
Vector2D Player::getWorldPos() const { return pos.worldPos; }
float Player::getWorldPosX() const { return pos.worldPos.x; }
float Player::getWorldPosY() const { return pos.worldPos.y; }

float Player::getSize() const
{
	return size->x;
}

Vector2D Player::getMoveVec() const {
	return *moveVec;
}


// setter
void Player::setWorldPos(Vector2D pos) {
	*tentativPos = pos;
	this->pos.worldPos = pos;
}
void Player::setWorldPosX(const float& num) { pos.worldPos.x = num; }
void Player::setWorldPosY(const float& num) { pos.worldPos.y = num; }
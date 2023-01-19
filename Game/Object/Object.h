#pragma once

#include "Game/Camera/Camera.h"
#include "Game/Quad/Quad.h"
#include "Game/Texture/Texture.h"

class Object {
public:
	Object() = delete;
	Object(Camera* camera);

protected:
	Camera* camera;

	Quad pos;
	Quad drawPos;

	static Texture whiteBox;

public:
	void BeginProcess();

	virtual void Update() = 0;

	virtual void Draw(class Texture& tex) = 0;

	virtual void Reset() = 0;
};
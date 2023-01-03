#pragma once
#include "Game/Camera/Camera.h"
#include "Game/Quad/Quad.h"

class Object {
public:
	Object() = delete;
	Object(Camera* camera);

protected:
	const Camera* camera;

	Quad pos;
	Quad drawPos;

public:
	void BeginProcess();

	virtual void Update() = 0;

	virtual void Draw(class Texture& tex) = 0;

	virtual void Reset() = 0;
};
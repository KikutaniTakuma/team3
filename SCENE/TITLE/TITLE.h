#pragma once
#include "Game/Object/Object.h"

class Title : public Object
{
public:
	Title(Camera *camera);
	~Title();

private:

public:
	//
	void Update() override;

	void Reset() override;

	void Draw(class Texture& tex) override;

};


#pragma once
#include "Game/Vector2D/Vector2D.h"

class Node
{
public:
	enum class State {
		None,
		Open,
		Closed
	};

public:
	Node();

public:
	int c;
	int h;
	int s;
	Vector2D pos;
	State state;
	Node* pre;
};
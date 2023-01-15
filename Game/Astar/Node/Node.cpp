#include "Game/Astar/Node/Node.h"

Node::Node() :
	c(0),
	h(0),
	s(0),
	pos(Vector2D()),
	state(State::None),
	pre(nullptr)
{}
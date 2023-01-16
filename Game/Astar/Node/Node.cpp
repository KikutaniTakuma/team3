#include "Game/Astar/Node/Node.h"
#include "Game/MapChip/MapChip.h"

Node::Node() :
	c(0),
	h(0),
	s(0),
	x(0),
	y(0),
	state(State::None),
	pre(nullptr),
	edges(0)
{}

Node::Node(Vector2D pos):
	c(0),
	h(0),
	s(0),
	x(static_cast<int>(MapChip::GetNum(pos).x)),
	y(static_cast<int>(MapChip::GetNum(pos).y)),
	state(State::None),
	pre(nullptr),
	edges(0)
{}

const Node& Node::operator=(const Node& tmp) {
	c = tmp.c;
	h = tmp.h;
	s = tmp.s;
	x = tmp.x;
	y = tmp.y;
	state = tmp.state;
	pre = tmp.pre;

	return *this;
}

void Node::Open() {
	state = Node::State::Closed;
	int tmp[4] = {
		y * MapChip::kMapWidth + x + 1,
		y * MapChip::kMapWidth + x - 1,
		(y + 1)* MapChip::kMapWidth + x,
		(y - 1)* MapChip::kMapWidth + x
	};

	if (tmp[0] < MapChip::data.size() && tmp[0] >= 0) {
		if (MapChip::data[tmp[0]] != 1) {
			edges.emplace_back(Node({ static_cast<float>(x + 1), static_cast<float>(y) }));
		}
	}
	if (tmp[1] < MapChip::data.size() && tmp[1] >= 0) {
		if (MapChip::data[tmp[1]] != 1) {
			edges.emplace_back(Node({ static_cast<float>(x) - 1, static_cast<float>(y) }));
		}
	}
	if (tmp[2] < MapChip::data.size() && tmp[2] >= 0) {
		if (MapChip::data[tmp[2]] != 1) {
			edges.emplace_back(Node({ static_cast<float>(x), static_cast<float>(y + 1) }));
		}
	}
	if (tmp[3] < MapChip::data.size() && tmp[3] >= 0) {
		if (MapChip::data[tmp[3]] != 1) {
			edges.emplace_back(Node({ static_cast<float>(x), static_cast<float>(y - 1) }));
		}
	}

	for (auto& i : edges) {
		i.state = Node::State::Open;
		i.c = c + 1;
		i.pre = this;
	}
}
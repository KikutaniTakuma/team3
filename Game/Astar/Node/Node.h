#pragma once
#include "Game/Vector2D/Vector2D.h"
#include <vector>

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
	Node(Vector2D pos);
	Node(int x, int y);

public:
	int c;
	int h;

	int x;
	int y;
	State state;
	Node* pre;

	std::vector<Node> edges;

public:
	const Node& operator=(const Node& tmp);

	bool operator==(const Node& tmp);

	void Open();

	inline int getS() {
		return h + c;
	}
};

inline bool Less(Node* a, Node* b)
{
	if (a->getS() < b->getS())
	{
		return true;
	}

	return false;
}
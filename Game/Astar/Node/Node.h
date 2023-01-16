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

public:
	int c;
	int h;
private:
	int s;
public:
	int x;
	int y;
	State state;
	Node* pre;

	std::vector<Node> edges;

public:
	const Node& operator=(const Node& tmp);

	void Open();

	inline int getS() {
		return h + c;
	}
};
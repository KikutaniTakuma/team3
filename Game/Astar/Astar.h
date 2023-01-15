#pragma once

#include <vector>
#include <stack>
#include "Game/Vector2D/Vector2D.h"
#include "Node/Node.h"

class Astar {
public:
	Astar();

private:
	int width;
	int height;

	int cost;

	Vector2D start;
	Vector2D goal;

	Node startNode;

	std::stack<Vector2D> shortData;

public:
	void Proc();

	void Move(Vector2D& pos);

private:
	int Heuristic();
};
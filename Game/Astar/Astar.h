#pragma once

#include <vector>
#include "Game/Vector2D/Vector2D.h"
#include "Node/Node.h"

class Astar {
public:
	Astar();

private:
	int width;
	int height;

	int score;

public:
	Vector2D start;
	Vector2D goal;

private:
	Node startNode;

	Node& currentNode;

	std::vector<Node> nodeData;

	std::vector<Node> openData;

public:
	void Proc();

	/*void Move(Vector2D& pos);*/

private:
	int Heuristic(Vector2D pos);

	int Heuristic(int x, int y);
};
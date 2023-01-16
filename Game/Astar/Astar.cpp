#include "Game/Astar/Astar.h"
#include "Game/MapChip/MapChip.h"

void Astar::Proc() {
	startNode.pos = start;

	startNode.state = Node::State::Open;
	startNode.c = cost;
	startNode.h = this->Heuristic();
	startNode.s = startNode.c + startNode.h;
	startNode.pre = nullptr;


}

int Astar::Heuristic() {
	width = abs(static_cast<int>(MapChip::GetNum(start).x - MapChip::GetNum(goal).x));
	height = abs(static_cast<int>(MapChip::GetNum(start).y - MapChip::GetNum(goal).y));
	return 0;
}
#include "Game/Astar/Astar.h"
#include "Game/MapChip/MapChip.h"

Astar::Astar() :
	nodeData(0),
	openData(0),
	currentNode(startNode),
	score(0),
	width(0),
	height(0)
{}

void Astar::Proc() {
	//最初のノードをオープン
	startNode = Node(start);
	startNode.state = Node::State::Open;
	startNode.c = 0;
	startNode.h = this->Heuristic(start);
	startNode.pre = nullptr;

	//ここからループ
	//ヒューリスティック関数がゼロになるまで
	while (this->Heuristic(currentNode.x, currentNode.y) != 0)
	{
		// 周りのノードをオープン
		currentNode.Open();
		for (auto& i : currentNode.edges) {
			i.h = this->Heuristic(i.x, i.y);
			openData.emplace_back(i);
			nodeData.emplace_back(i);
		}

		// 基準ノードをリセット
		score = openData[0].getS();
		for (auto i = openData.begin(); i != openData.end(); i++) {
			if (i->getS() < score) {
				score = i->getS();
			}
		}

		for (auto i = openData.begin(); i != openData.end(); i++) {
			if (i->getS() == score) {
				currentNode = *i;
				openData.erase(i);
				break;
			}
		}
	}

	Node* tmp = &currentNode;
	while (tmp != nullptr) {
		MapChip::data[tmp->y * MapChip::kMapWidth + tmp->x] = (int)MapChip::Type::Short;
		tmp = tmp->pre;
	}


}

int Astar::Heuristic(Vector2D pos) {
	width = abs(static_cast<int>(MapChip::GetNum(pos).x - MapChip::GetNum(goal).x));
	height = abs(static_cast<int>(MapChip::GetNum(pos).y - MapChip::GetNum(goal).y));

	return width + height;
}

int Astar::Heuristic(int x, int y) {
	width = abs(x - static_cast<int>(MapChip::GetNum(goal).x));
	height = abs(y - static_cast<int>(MapChip::GetNum(goal).y));

	return width + height;
}
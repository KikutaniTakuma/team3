#include "Game/Astar/Astar.h"
#include "Game/MapChip/MapChip.h"

Astar::Astar() :
	closeData(0),
	openData(0),
	currentNode(&startNode),
	score(0),
	width(0),
	height(0)
{}

void Astar::Proc() {
	//最初のノードをオープン
	startNode = Node(start);
	startNode.h = this->Heuristic(startNode.x, startNode.y);
	startNode.state = Node::State::Open;

	openData.push_back(&startNode);

	/*bool flg = true;*/

	//ここからループ
	//ヒューリスティック関数がゼロになるまで
	while (openData.empty() == false)
	{
		Node* searchNode = *(openData.begin());

		openData.erase(openData.begin());
		
		closeData.push_back(searchNode);

		if (*searchNode == Node(goal)) {
			break;
		}

		searchNode->Open();

		for (auto& j : searchNode->edges) {
			j.h = this->Heuristic(j.x, j.y);
			openData.push_back(&j);
			for (auto& i : openData) {
				if (!(*i == j)) {
					openData.pop_back();
					break;
				}
			}
		}

		openData.sort(Less);


		/*for (int i = 0; i < currentNode.edges.size(); i++) {
			currentNode.edges[i].h = this->Heuristic(currentNode.edges[i].x, currentNode.edges[i].y);
			openData.emplace_back(currentNode.edges[i]);
			for (auto& j : nodeData) {
				if (j == currentNode.edges[i]) {
					openData.pop_back();
					flg = false;
					break;
				}
				else {
					flg = true;
				}
			}
			if (flg) {
				nodeData.emplace_back(currentNode.edges[i]);
			}
		}*/

		/*if(nodeData.size() > 300){
			break;
		}*/

		// 基準ノードをリセット
		/*score = openData[0].getS();
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
		}*/
	}

	Node* tmp = currentNode;
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
#include "reader.h";

#include <iostream>;

#include <algorithm>;
#include <stack>;



/*
//	Storlek på metadata = storlek på 2d vectorn std::vector<std::vector<>>
//
//	Infinity?? #47 not connected
//
*/

void static depthFirstSearch(adjacency_list_t& graphList);
void static findNeighbours(std::map<node_id_t, std::vector<std::pair<node_id_t, weight_t>>>& tempNeighbours, std::vector<edge>& tempEdges);
void dfsRecursive(std::vector<bool>& isVisitedTemp, int& currentNodeTemp, std::map<node_id_t, std::vector<std::pair<node_id_t, weight_t>>>& neighboursTemp, std::vector<std::pair<node_id_t, weight_t>>& travelledPathTemp);

int main() {
	std::string data = "data.txt";
	int startNode = 0;

	adjacency_list_t myGraph = parse_file(data);

	// Nodes and names
	meta_t nodeIdMap = myGraph.first;

	// Current node, neighbour, weight, name
	edge_list_t edgeVec = myGraph.second;

	depthFirstSearch(myGraph);

	return 0;
}



void static depthFirstSearch(adjacency_list_t& graphList) {
	std::map<node_id_t, std::vector<std::pair<node_id_t, weight_t>>> neighbours;
	findNeighbours(neighbours, graphList.second);

	int graphSize = 0;
	int currentNode = 0;

	for (auto& e : neighbours) {
		std::cout << "Node:" << e.first << "\n";
		for (size_t i = 0; i < e.second.size(); i++) {
			std::cout << "   Neighbour: " << e.second[i].first << ", Weight: " << e.second[i].second << "\n";
		}
		std::cout << "\n";
		graphSize++;
	}

	std::cout << '\n' << "*******************************************************\n" << std::endl;

	std::vector<bool> isVisited(graphSize);
	std::vector<std::pair<node_id_t, weight_t>> travelledPath;

	std::cout << travelledPath.size();


	dfsRecursive(isVisited, currentNode, neighbours, travelledPath);

	for (auto& n : travelledPath) {

		std::cout << "Node: " << n.first << " , Weight: " << n.second << std::endl;
	}

}

void dfsRecursive(std::vector<bool>& isVisitedTemp, int& currentNodeTemp, std::map<node_id_t, std::vector<std::pair<node_id_t, weight_t>>>& neighboursTemp, std::vector<std::pair<node_id_t, weight_t>>& travelledPathTemp) {


	if (isVisitedTemp[currentNodeTemp]) {
		return;
	}
	isVisitedTemp[currentNodeTemp] = true;
	//travelledPathTemp.push_back((neighboursTemp[currentNodeTemp][currentNodeTemp]));

	std::cout << "THIS IS CURRENTNODE: " << currentNodeTemp << std::endl;

	for (auto& e : neighboursTemp[currentNodeTemp]) {
		currentNodeTemp = e.first;
		if (!isVisitedTemp[currentNodeTemp]) {
			travelledPathTemp.push_back(std::make_pair(e.first, e.second));

			dfsRecursive(isVisitedTemp, currentNodeTemp, neighboursTemp, travelledPathTemp);

			/*for (auto& n : neighboursTemp[currentNodeTemp]) {
				if (n.first == currentNodeTemp) {
					std::cout << "NO PRINTO" << std::endl;
					travelledPathTemp.push_back(std::make_pair(n.first, n.second));

				}
			}*/
		}
	}



}



void static findNeighbours(std::map<node_id_t, std::vector<std::pair<node_id_t, weight_t>>>& tempNeighbours, std::vector<edge>& tempEdges) {

	int keyNumber = 0;
	for (int i = 0; i < tempEdges.size() - 1; i++) {
		std::vector<std::pair<node_id_t, weight_t>> tempVec;
		keyNumber = tempEdges[i].n1;

		for (int j = 0; j < tempEdges.size() - 1; j++) {

			if (tempEdges[j].n1 == keyNumber) {

				tempVec.push_back(std::make_pair(tempEdges[j].n2, tempEdges[j].weight));
			}
		}
		tempNeighbours.insert({ keyNumber, tempVec });
	}
}
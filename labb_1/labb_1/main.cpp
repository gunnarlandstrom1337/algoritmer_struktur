#include "reader.h";

#include <iostream>;

#include <algorithm>;
#include <stack>;
#include <queue>;
#include <limits>;
#include <functional>;



/*
//	Storlek på metadata = storlek på 2d vectorn std::vector<std::vector<>>
//
//	Infinity?? #47 not connected
//
*/

void static breathFirstSearch(adjacency_list_t& graphList);
void static bfsIterative(std::map<node_id_t, std::vector<std::pair<node_id_t, weight_t>>>& tempNeighbours, int& currentNodeTemp);
void static depthFirstSearch(adjacency_list_t& graphList);
void dfsRecursive(std::vector<bool>& isVisitedTemp, int& currentNodeTemp, std::map<node_id_t, std::vector<std::pair<node_id_t, weight_t>>>& neighboursTemp, std::vector<std::pair<node_id_t, weight_t>>& travelledPathTemp);


void static findNeighbours(std::map<node_id_t, std::vector<std::pair<node_id_t, weight_t>>>& tempNeighbours, std::vector<edge>& tempEdges);
void static dijkstraAlgo(adjacency_list_t& graphList, int& startNode);
int static minDistanceNeighbour(std::vector<double>& distance, std::vector<bool>& shortestPath);

int main() {
	std::string data = "data.txt";
	int startNode = 0;

	adjacency_list_t myGraph = parse_file(data);


	depthFirstSearch(myGraph);
	breathFirstSearch(myGraph);

	int tempStart = 20;
	dijkstraAlgo(myGraph, tempStart);

	return 0;
}


void static dijkstraAlgo(adjacency_list_t& graphList, int& startNode) {
	std::cout << '\n' << "---------------------------------- DIJKSTRA - Travelled Path ----------- \n" << std::endl;
	std::map<node_id_t, std::vector<std::pair<node_id_t, weight_t>>> neighbours;
	findNeighbours(neighbours, graphList.second);

	int graphSize = 0;
	for (auto& e : neighbours) {
		graphSize++;
	}

	std::vector<double> distanceTravelled(graphSize);
	std::vector<bool> isVisited(graphSize);
	std::vector<std::pair<weight_t, node_id_t>> shortestPaths(graphSize);


	std::priority_queue<std::pair<weight_t, node_id_t>, std::vector<std::pair<weight_t, node_id_t>>, std::greater<>> prioQueue;

	const double constexpr infinity = std::numeric_limits<double>::infinity();

	for (int i = 0; i < graphSize; i++) {
		shortestPaths[i].first = infinity;
	}

	prioQueue.push(std::make_pair(distanceTravelled[startNode], startNode));
	shortestPaths[startNode].first = 0;
	shortestPaths[startNode].second = startNode;

	while (!prioQueue.empty()) {

		int currentNode = prioQueue.top().second;
		double currentWeight = prioQueue.top().first;

		prioQueue.pop();

		isVisited[currentNode] = true;

		for (auto& e : neighbours[currentNode]) {

			if (!isVisited[e.first]) {
				prioQueue.push(std::make_pair(e.second, e.first));
				double weight = shortestPaths[currentNode].first;
				if (e.second + weight < shortestPaths[e.first].first) {
					shortestPaths[e.first] = std::make_pair(e.second + weight, e.first);
				}
			}
		}

	}

	for (auto& e : shortestPaths) {

		std::cout << "Index: " << e.second << " , Weight: " << e.first << std::endl;
	}


}

int static minDistanceNeighbour(std::vector<double>& distance, std::vector<bool>& shortestPath) {

	int shortestDistance = INT_MAX;
	int shortestNeighbour = 0;

	for (int i = 0; i < distance.size() - 1; i++) {
		if (shortestPath[i] == false && distance[i] <= shortestDistance) {
			shortestDistance = distance[i];
			shortestNeighbour = i;
		}
	}
	return shortestNeighbour;
}



void static breathFirstSearch(adjacency_list_t& graphList) {
	std::map<node_id_t, std::vector<std::pair<node_id_t, weight_t>>> neighbours;
	findNeighbours(neighbours, graphList.second);
	int currentNode = 0;
	bfsIterative(neighbours, currentNode);
}

void static bfsIterative(std::map<node_id_t, std::vector<std::pair<node_id_t, weight_t>>>& tempNeighbours, int& startNodeTemp) {

	int graphSize = 0;
	for (auto& e : tempNeighbours) {
		graphSize++;
	}
	std::vector<bool> isVisited(graphSize);
	std::vector<std::pair<node_id_t, weight_t>> travelledPath;

	std::queue<std::pair<node_id_t, weight_t>> myQueue;

	isVisited[startNodeTemp] = true;
	myQueue.push(std::make_pair(startNodeTemp, 0.0));

	while (!myQueue.empty()) {
		std::pair<node_id_t, weight_t> currentNode = myQueue.front();
		myQueue.pop();
		travelledPath.push_back(currentNode);

		for (auto& e : tempNeighbours[currentNode.first]) {
			if (!isVisited[e.first]) {
				isVisited[e.first] = true;
				myQueue.push(std::make_pair(e.first, e.second));
			}
		}


	}

	std::cout << '\n' << "---------------------------------- Breath First Search - Travelled Path ----------- \n" << std::endl;

	for (auto& p : travelledPath) {
		std::cout << "Node: " << p.first << " , Weight: " << p.second << std::endl;
	}

	std::cout << '\n' << "---------------------------------- Breath First Search - Is Visited? ----------- \n" << std::endl;

	for (size_t i = 0; i < isVisited.size() - 1; i++) {
		std::cout << "Node: " << i << " visited: " << isVisited[i] << std::endl;

	}



}



void static depthFirstSearch(adjacency_list_t& graphList) {
	std::map<node_id_t, std::vector<std::pair<node_id_t, weight_t>>> neighbours;
	findNeighbours(neighbours, graphList.second);

	int graphSize = 0;
	std::cout << '\n' << "------------------------------- NODES AND NEIGHBOURS FOUND IN data.txt ------ \n" << std::endl;
	for (auto& e : neighbours) {
		std::cout << "Node:" << e.first << "\n";
		for (size_t i = 0; i < e.second.size(); i++) {
			std::cout << "   Neighbour: " << e.second[i].first << ", Weight: " << e.second[i].second << "\n";
		}
		std::cout << "\n";
		graphSize++;
	}


	std::vector<bool> isVisited(graphSize);
	std::vector<std::pair<node_id_t, weight_t>> travelledPath;


	int currentNode = 5;
	travelledPath.push_back(std::make_pair(currentNode, 0));

	dfsRecursive(isVisited, currentNode, neighbours, travelledPath);

	std::cout << '\n' << "---------------------------------- Depth First Search - Travelled Path ----------- \n" << std::endl;

	for (auto& n : travelledPath) {

		std::cout << "Node: " << n.first << " , Weight: " << n.second << std::endl;
	}

	std::cout << '\n' << "----------------------------------- Depth First Search - Is Visited? ---------- \n" << std::endl;

	for (size_t i = 0; i < isVisited.size() - 1; i++) {
		std::cout << "Node: " << i << " visited: " << isVisited[i] << std::endl;

	}


}

void dfsRecursive(std::vector<bool>& isVisitedTemp, int& currentNodeTemp, std::map<node_id_t, std::vector<std::pair<node_id_t, weight_t>>>& neighboursTemp, std::vector<std::pair<node_id_t, weight_t>>& travelledPathTemp) {


	if (isVisitedTemp[currentNodeTemp]) {
		return;
	}
	isVisitedTemp[currentNodeTemp] = true;

	for (auto& e : neighboursTemp[currentNodeTemp]) {
		currentNodeTemp = e.first;
		if (!isVisitedTemp[currentNodeTemp]) {
			travelledPathTemp.push_back(std::make_pair(e.first, e.second));

			dfsRecursive(isVisitedTemp, currentNodeTemp, neighboursTemp, travelledPathTemp);

		}
	}



}



void static findNeighbours(std::map<node_id_t, std::vector<std::pair<node_id_t, weight_t>>>& tempNeighbours, std::vector<edge>& tempEdges) {

	int keyNumber = 0;

	for (int i = 0; i < tempEdges.size(); i++) {
		std::vector<std::pair<node_id_t, weight_t>> tempVec;
		keyNumber = tempEdges[i].n1;




		for (int j = 0; j < tempEdges.size(); j++) {

			if (tempEdges[j].n1 == keyNumber) {

				tempVec.push_back(std::make_pair(tempEdges[j].n2, tempEdges[j].weight));
			}
		}
		tempNeighbours.insert({ keyNumber, tempVec });
	}
}
#ifndef SEARCHALGOS_H
#define SEACHALGOS_H

#include <vector>


struct Node {
	int value;
	Node* left;
	Node* right;

	Node(int value) : value(value), left(nullptr), right(nullptr) {}
};


using iterator = std::vector<int>::iterator;

Node* balancedBST(iterator first, iterator last);

using func = void (*)(iterator first, iterator last);


int linearSearch(iterator first, iterator last, int key);
int binarySearch(iterator first, iterator last, int key);
Node* binaryTreeSearch(Node* root, int target);



#endif // !SEARCHALGOS_H


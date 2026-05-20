#include "searchAlgos.h"
#include <iostream>
#include "HashTable.h"


int linearSearch(iterator first, iterator last, int key)
{
	unsigned int tempCounter = 0;
	while (first != last) {
		if (*first == key) {
			//std::cout << "Found number: " << key << " , at index: " << tempCounter << " , using Linear Search" << std::endl;
			return tempCounter;
		}
		first++;
		tempCounter++;
	}

	//std::cout << "Number not found." << std::endl;
	return -1;
}

int binarySearch(iterator first, iterator last, int key)
{

	iterator begin = first;
	while (first < last) {

		iterator mid = first + ((last - first) / 2);


		if (*mid == key) {
			//std::cout << "Your number: " << key << " , was found at index: " << mid - begin << " , using Binary Search" << std::endl;
			return mid - begin;
		}
		else if (*mid < key) {
			first = mid + 1;
		}
		else if (*mid > key) {
			last = mid;
		}
	}
	//std::cout << "Number not found." << std::endl;
	return -1;
}

Node* binaryTreeSearch(Node* root, int target)
{
	Node* current = root;

	while (current != nullptr)
	{
		if (target == current->value) {
			//std::cout << "Target value: " << target << " , FOUND in the BST" << std::endl;
			return current;
		}
		if (target < current->value) {
			current = current->left;
		}
		else {
			current = current->right;
		}
	}

	//std::cout << "Target value: " << target << " , not found in BST." << std::endl;
	return nullptr;
}


Node* balancedBST(iterator first, iterator last) {
	if (first >= last)
		return nullptr;

	auto mid = first + (last - first) / 2;

	Node* root = new Node(*mid);

	root->left = balancedBST(first, mid);
	root->right = balancedBST(mid + 1, last);

	return root;
}
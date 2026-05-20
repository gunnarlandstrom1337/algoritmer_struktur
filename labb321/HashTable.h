#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <vector>


struct HashNode {
	int value;
	HashNode* next;
	HashNode(int value, HashNode* nextNode) : value(value), next(nextNode) {}
};


class HashTable
{
private:
	std::vector<HashNode*> table;
	int tableSize;

	int hashFunction(int value) const;

public:
	HashTable(int size);

	void insert(int value);

	bool hashTableSearch(int value);

};


#endif // !1
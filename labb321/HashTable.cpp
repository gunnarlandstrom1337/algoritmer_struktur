#include "HashTable.h"
#include <iostream>

int HashTable::hashFunction(int value) const
{
	return value % tableSize;
}

HashTable::HashTable(int size)
{
	tableSize = size;
	table.resize(size, nullptr);
}

void HashTable::insert(int value)
{
	int hash = hashFunction(value);

	HashNode* newNode = new HashNode{value , table[hash]};

	table[hash] = newNode;
}

bool HashTable::hashTableSearch(int value)
{
    int hash = hashFunction(value);

    HashNode* current = table[hash];

    while (current != nullptr)
    {
        if (current->value == value) {
            //std::cout << "Hashtable lookup successful!, your target: " << value << " , was found." << std::endl;
            return true;
        }
        current = current->next;
    }

    return false;
}

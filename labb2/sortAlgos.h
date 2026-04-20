#ifndef SORTALGOS_H

#define SORTALGOS_H
#include <vector>


using iterator = std::vector<int>::iterator;


class sortAlgos
{
public:
	void quickSortPartition(iterator first, iterator last);
	void quickSortMedian(iterator first, iterator last);
	void insertionSort(iterator first, iterator last);
	void selectionSort(iterator first, iterator last);

	iterator static partition(iterator first, iterator last);



};


#endif
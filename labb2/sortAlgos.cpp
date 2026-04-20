#include "sortAlgos.h"
#include <algorithm>
#include <iostream>

void sortAlgos::quickSortPartition(iterator first, iterator last)
{
	iterator mid;
	while (first != last) {
		mid = partition(first, last);
		quickSortPartition(mid+1, last);
		last = mid;
	}

}

iterator sortAlgos::partition(iterator first, iterator last) {

	auto const pivot = last-1;
	auto highSearch = first;
	auto lowSearch = last - 2;
	if (first == lowSearch) return first;

	while (highSearch < lowSearch) {
			std::cout << "This is Pivot value: " << *pivot << std::endl;
		if (*highSearch < *pivot){
			std::cout << "This is HighPointer value: " << *highSearch << std::endl;
			highSearch++;
			continue;
		}
		if (*lowSearch > *pivot) {
			std::cout << "This is LowPointer value: " << *lowSearch << std::endl;
			lowSearch--;
			continue;
		}
		
		std::iter_swap(highSearch, lowSearch);
	}
	std::iter_swap(highSearch, pivot);
	return pivot;
}



void sortAlgos::quickSortMedian(iterator first, iterator last)
{
}

void sortAlgos::insertionSort(iterator first, iterator last)
{
	if (first == last) {
		return;
	}
	iterator currentIterator = first+1;

	while (currentIterator != last) {

		if (*currentIterator < *(currentIterator-1)) {
			auto tempValue = *currentIterator;
			*currentIterator = *(currentIterator - 1);
			iterator insertionIterator = currentIterator - 1;

			while (insertionIterator != first) {
				if (*(insertionIterator - 1) > tempValue) {
					*insertionIterator = *(insertionIterator - 1);
				}
				else {
					break;
				}
				insertionIterator--;
			}
			*insertionIterator = tempValue;
		}
		currentIterator++;
	}
}

void sortAlgos::selectionSort(iterator first, iterator last)
{


	while (first != last){

		iterator minIdx = first;
		iterator tempIterator = first+1;
		while(tempIterator != last) {
			if (*tempIterator < *minIdx) {
				minIdx = tempIterator;
			}
			tempIterator++;
		}
		std::iter_swap(first,minIdx);
		first++;
	}
}


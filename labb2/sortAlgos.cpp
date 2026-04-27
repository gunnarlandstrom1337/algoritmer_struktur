#include "sortAlgos.h"
#include <algorithm>
#include <iterator>

void quickSortPartition(iterator first, iterator last)
{
	iterator mid;
	while (first != last) {
		mid = partition(first, last);
		quickSortPartition(mid + 1, last);
		last = mid;
	}
}

iterator partition(iterator first, iterator last) {

	auto const pivot = last - 1;
	auto highSearch = first;
	auto lowSearch = pivot - 1;

	while (highSearch < lowSearch) {
		while (*highSearch <= *pivot && highSearch != pivot - 1) {
			highSearch++;
		}
		while (*lowSearch >= *pivot && lowSearch != highSearch) {
			lowSearch--;
		}
		if (highSearch >= lowSearch) break;
		std::iter_swap(highSearch, lowSearch);
		highSearch++;
	}

	if (*highSearch < *pivot) return pivot;
	std::iter_swap(highSearch, pivot);

	return highSearch;
}

void medianOfThree(iterator first, iterator last)
{
	iterator lowValue = first;
	iterator medianValue;
	iterator highValue = last - 1;
	int tempValue = std::distance(first, last) / 2;

	medianValue = first + tempValue;

	if (*medianValue < *lowValue) { 
		std::iter_swap(lowValue, medianValue);
	}
	if (*highValue < *lowValue) {
		std::iter_swap(highValue, lowValue);
	}
	if (*medianValue < *highValue) {
		std::iter_swap(medianValue, highValue);
	}
}



void quickSortMedian(iterator first, iterator last)
{

	iterator mid;
	while (first != last) {
		medianOfThree(first, last);
		mid = partition(first, last);
		quickSortMedian(mid + 1, last);
		last = mid;
	}
}

void insertionSort(iterator first, iterator last)
{
	if (first == last) {
		return;
	}
	iterator currentIterator = first + 1;

	while (currentIterator != last) {

		if (*currentIterator < *(currentIterator - 1)) {
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

void selectionSort(iterator first, iterator last)
{
	while (first != last) {
		iterator minIdx = first;
		iterator tempIterator = first + 1;
		while (tempIterator != last) {
			if (*tempIterator < *minIdx) {
				minIdx = tempIterator;
			}
			tempIterator++;
		}
		std::iter_swap(first, minIdx);
		first++;
	}
}


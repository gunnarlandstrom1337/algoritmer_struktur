/*
•	Quicksort. Pivot i partitioneringssteget är höger element. Hoare [2]
•	Quicksort. Pivot enligt median-of-three. Hoare [2]
•	std::sort, eller motsvarande standardalgoritm som gäller för det språk du


	std::chrono
	std::chrono::steady_clock::now()
*/

#include <chrono>
#include <iostream>
#include "sortAlgos.h"
#include <vector>
#include <ctime>
#include <algorithm>


int main() {

	sortAlgos sortThis;
	std::srand(time(NULL));
	int N = 10;
	std::vector<int> randomData(N);



	int MY_RANGE_MAX = 10;
	for (int i = 0; i < N; i++) {

		randomData[i] = (1.0 * rand() / RAND_MAX)* MY_RANGE_MAX;
	}

	sortThis.quickSortPartition(randomData.begin(), randomData.end());
	
		for (auto& e : randomData) {
			std::cout << e << std::endl;
		}

	for (auto& e : randomData) {

		std::cout << e << std::endl;
	}


	std::cout << "\nIs sorted: " << std::is_sorted(randomData.begin(), randomData.end()) << std::endl;

	return 0;
}
#include <iostream>
#include <vector>
#include <ctime>
#include <algorithm>
#include "sortAlgos.h"
#include "generatingNumbers.h"
#include "timeCheck.h"
#include <map>
#include <cmath>
#include <fstream>

using doubleiterator = std::vector<double>::iterator;
double calculateStandardDeviation(doubleiterator first, doubleiterator last);


// O(NlogN)
// Median of three
// QuickSort
// Std::sort

// O(N^2)
// Insertion sort random
// Insertion sort descsending
// Selection sort
// Quicksort -  Constant
// Quicksort MoT - Constant
// Quicksort - Descending
// Quicksort - Ascending

// O(N)
// Insertion sort Ascending
// Std::sort
// QuickSort MoT - Ascending
// QuickSort MoT - Descending

// Crashing high amount
// QuickSort - Descending
// QuickSort - Ascending
// QuickSort - Constant



int main() {

	std::srand(time(NULL));

	int samples = 5;

	int sortSlices = 20'000;
	int K = 5'000'000;
	double timeResult;
	int N = 20'000;

	std::ofstream myFile("LinearData.data");

	if (myFile.is_open()) {
	myFile << "N:	" << "	T[ms]	" << "	Stdev[ms]	 " << " Samples " << std::endl;
	}


	for (; N < K+sortSlices; N += sortSlices) {
	std::map<std::string, std::vector<double>> timeVecRandom;

		std::vector<int> rand(N);
		std::vector<int> constant(N);
		std::vector<int> desc(N);
		std::vector<int> asc(N);

		// Random
		std::vector<double> timeVecRandQuickMedian;
		std::vector<double> timeVecRandQuickRight;
		std::vector<double> timeVecRandStdSort;
		std::vector<double> timeVecRandSelection;
		std::vector<double> timeVecRandInsertion;

		for (int i = 0; i != samples; i++) {
			//timeVecRandQuickMedian.push_back(timeResult = compareRand(rand.begin(), rand.end(), quickSortMedian));
			//timeVecRandQuickRight.push_back(timeResult = compareRand(rand.begin(), rand.end(), quickSortPartition));
			//timeVecRandStdSort.push_back(timeResult = compareRand(rand.begin(), rand.end(), std::sort));
			//timeVecRandSelection.push_back(timeResult = compareRand(rand.begin(), rand.end(), selectionSort));
			//timeVecRandInsertion.push_back(timeResult = compareRand(rand.begin(), rand.end(), insertionSort));
		}
		//timeVecRandom.insert(std::make_pair("QuickSort MoT - Random", timeVecRandQuickMedian));
		//timeVecRandom.insert(std::make_pair("QuickSort - Random", timeVecRandQuickRight));
		//timeVecRandom.insert(std::make_pair("Std::sort - Random", timeVecRandStdSort));
		//timeVecRandom.insert(std::make_pair("Selection Sort - Random", timeVecRandSelection));
		//timeVecRandom.insert(std::make_pair("Insertion Sort - Random", timeVecRandInsertion));

		// Ascending
		std::vector<double> timeVecAscQuickMedian;
		std::vector<double> timeVecAscQuickRight;
		std::vector<double> timeVecAscStdSort;
		std::vector<double> timeVecAscSelection;
		std::vector<double> timeVecAscInsertion;
		std::vector<std::vector<double>> timeVecAscending;

		for (int i = 0; i != samples; i++) {
			//timeVecAscSelection.push_back(timeResult = compareAsc(asc.begin(), asc.end(), selectionSort));
		
			//timeVecAscQuickRight.push_back(timeResult = compareAsc(asc.begin(), asc.end(), quickSortPartition));
			timeVecAscInsertion.push_back(timeResult = compareAsc(asc.begin(), asc.end(), insertionSort));
			timeVecAscQuickMedian.push_back(timeResult = compareAsc(asc.begin(), asc.end(), quickSortMedian));
			timeVecAscStdSort.push_back(timeResult = compareAsc(asc.begin(), asc.end(), std::sort));
		
		}
		//timeVecRandom.insert(std::make_pair("SelectionSort - Ascending", timeVecAscSelection));
		//timeVecRandom.insert(std::make_pair("QuickSort - Ascending", timeVecAscQuickRight));
		timeVecRandom.insert(std::make_pair("InsertionSort - Ascending", timeVecAscInsertion));
		timeVecRandom.insert(std::make_pair("QuickSort MoT - Ascending", timeVecAscQuickMedian));
		timeVecRandom.insert(std::make_pair("Std::sort - Ascending", timeVecAscStdSort));


		// Descending
		std::vector<double> timeVecDescQuickMedian;
		std::vector<double> timeVecDescQuickRight;
		std::vector<double> timeVecDescStdSort;
		std::vector<double> timeVecDescInsertion;
		std::vector<double> timeVecDescSelection;

		for (int i = 0; i != samples; i++) {
			//timeVecDescSelection.push_back(timeResult = compareDesc(desc.begin(), desc.end(), selectionSort));
			//timeVecDescQuickRight.push_back(timeResult = compareDesc(desc.begin(), desc.end(), quickSortPartition));
			timeVecDescQuickMedian.push_back(timeResult = compareDesc(desc.begin(), desc.end(), quickSortMedian));
			//timeVecDescInsertion.push_back(timeResult = compareDesc(desc.begin(), desc.end(), insertionSort));
			//timeVecDescStdSort.push_back(timeResult = compareDesc(desc.begin(), desc.end(), std::sort));
		}
		//timeVecRandom.insert(std::make_pair("QuickSort - Descending", timeVecDescQuickRight));
		timeVecRandom.insert(std::make_pair("QuickSort MoT - Descending", timeVecDescQuickMedian));
		//timeVecRandom.insert(std::make_pair("SelectionSort - Descending", timeVecDescSelection));
		//timeVecRandom.insert(std::make_pair("InsertionSort - Descending", timeVecDescInsertion));
		//timeVecRandom.insert(std::make_pair("Std::sort - Descending", timeVecDescStdSort));

		// Constant
		std::vector<double> timeVecConstQuickMedian;
		std::vector<double> timeVecConstQuickRight;
		std::vector<double> timeVecConstStdSort;
		std::vector<double> timeVecConstSelection;
		std::vector<double> timeVecConstInsertion;

		for (int i = 0; i != samples; i++) {
			//timeVecConstQuickRight.push_back(timeResult = compareConst(constant.begin(), constant.end(), quickSortPartition));
			//timeVecConstQuickMedian.push_back(timeResult = compareConst(constant.begin(), constant.end(), quickSortMedian));
			//timeVecConstSelection.push_back(timeResult = compareConst(constant.begin(), constant.end(), selectionSort));
		
			timeVecConstStdSort.push_back(timeResult = compareConst(constant.begin(), constant.end(), std::sort));
			timeVecConstInsertion.push_back(timeResult = compareConst(constant.begin(), constant.end(), insertionSort));
		
		}
		//timeVecRandom.insert(std::make_pair("QuickSort - Constant", timeVecConstQuickRight));
		//timeVecRandom.insert(std::make_pair("QuickSort MoT - Constant", timeVecConstQuickMedian));
		//timeVecRandom.insert(std::make_pair("SelectionSort - Constant", timeVecConstSelection));
		timeVecRandom.insert(std::make_pair("Std::sort - Constant", timeVecConstStdSort));
		timeVecRandom.insert(std::make_pair("InsertionSort - Constant", timeVecConstInsertion));

		double tempValue = 0;
		double stdDev = 0;
		for (auto& e : timeVecRandom) {
			//std::cout << "	*****" << e.first << "*****\n" << std::endl;
			for (auto& f : e.second) {
				tempValue += f;
			}
			stdDev = calculateStandardDeviation(e.second.begin(), e.second.end());
			//std::cout << "N:	" << "	T[ms]	" << "	Stdev[ms]	 " << " Samples " << std::endl;
			if (myFile.is_open()) {
			myFile << N << "		" << tempValue / samples << "		" << stdDev << "		" << samples << "	" << e.first << "\n" << std::endl;
			}
			//std::cout << N << "		" << tempValue / samples << "		" << stdDev << "		" << samples << "\n" << std::endl;

			tempValue = 0;
		}
	}
	myFile.close();
	return 0;
}

double calculateStandardDeviation(doubleiterator first, doubleiterator last)
{
	double sum = 0;
	double mean = 0;
	double standardDeviation = 0;
	doubleiterator temp = first;
	size_t size = last - first;

	for (; temp != last; temp++) {
		sum += *temp;
	}

	mean = sum / size;

	for (; first != last; first++) {
		standardDeviation += std::pow(*first - mean, 2);
	}

	return std::sqrt(standardDeviation / (size - 1));
}
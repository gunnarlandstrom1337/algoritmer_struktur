#include <iostream>
#include <vector>
#include <ctime>
#include <algorithm>
#include "sortAlgos.h"
#include "generatingNumbers.h"
#include "timeCheck.h"
#include <map>
#include <cmath>

using doubleiterator = std::vector<double>::iterator;
double calculateStandardDeviation(doubleiterator first, doubleiterator last);


int main() {

	using nano = std::chrono::nanoseconds;
	std::srand(time(NULL));
	int timeSlices = 10;
	int samples = 10;

	int N = 1'000'000;
	double timeResult;




	std::vector<int> rand(N);
	std::vector<int> constant(N);
	std::vector<int> desc(N);
	std::vector<int> asc(N);

	// Random
	std::vector<double> timeVecRandQuickMedian;
	std::vector<double> timeVecRandQuickRight;
	std::vector<double> timeVecRandStdSort;
	std::vector<double> timeVecRandSelection;
	std::map<std::string, std::vector<double>> timeVecRandom;

	for (int i = 0; i != samples; i++) {
		timeVecRandQuickMedian.push_back(timeResult = compareRand(rand.begin(), rand.end(), quickSortMedian));
		timeVecRandQuickRight.push_back(timeResult = compareRand(rand.begin(), rand.end(), quickSortPartition));
		timeVecRandStdSort.push_back(timeResult = compareRand(rand.begin(), rand.end(), std::sort));
	}
	timeVecRandom.insert(std::make_pair("QuickSort - Median", timeVecRandQuickMedian));
	timeVecRandom.insert(std::make_pair("QuickSort - Right", timeVecRandQuickRight));
	timeVecRandom.insert(std::make_pair("Std::sort", timeVecRandStdSort));

	// Ascending
	std::vector<double> timeVecAscQuickMedian;
	std::vector<double> timeVecAscQuickRight;
	std::vector<double> timeVecAscStdSort;
	std::vector<double> timeVecAscSelection;
	std::vector<std::vector<double>> timeVecAscending;


	for (int i = 0; i != samples; i++) {
		timeVecAscQuickMedian.push_back(timeResult = compareRand(asc.begin(), asc.end(), quickSortMedian));
		timeVecAscQuickRight.push_back(timeResult = compareRand(asc.begin(), asc.end(), quickSortPartition));
		timeVecAscStdSort.push_back(timeResult = compareRand(asc.begin(), asc.end(), std::sort));
	}

	// Descending
	std::vector<double> timeVecDescQuickMedian;
	std::vector<double> timeVecDescQuickRight;
	std::vector<double> timeVecDescStdSort;
	std::vector<double> timeVecDescSelection;
	std::vector<std::vector<double>> timeVecDescending;

	for (int i = 0; i != samples; i++) {
		timeVecDescQuickMedian.push_back(timeResult = compareRand(desc.begin(), desc.end(), quickSortMedian));
		timeVecDescQuickRight.push_back(timeResult = compareRand(desc.begin(), desc.end(), quickSortPartition));
		timeVecDescStdSort.push_back(timeResult = compareRand(desc.begin(), desc.end(), std::sort));
	}

	// Constant
	std::vector<double> timeVecConstQuickMedian;
	std::vector<double> timeVecConstQuickRight;
	std::vector<double> timeVecConstStdSort;
	std::vector<double> timeVecConstSelection;
	std::vector<std::vector<double>> timeVecConstant;

	for (int i = 0; i != samples; i++) {
		timeVecConstQuickMedian.push_back(timeResult = compareRand(constant.begin(), constant.end(), quickSortMedian));
		timeVecConstQuickRight.push_back(timeResult = compareRand(constant.begin(), constant.end(), quickSortPartition));
		timeVecConstStdSort.push_back(timeResult = compareRand(constant.begin(), constant.end(), std::sort));
	}

	double tempValue = 0;
	double stdDev = 0;
	for (auto& e : timeVecRandom) {
	std::cout << "	*****" << e.first << "*****\n" << std::endl;
		for (auto& f : e.second) {
			tempValue += f;
		}
		stdDev = calculateStandardDeviation(e.second.begin(), e.second.end());
		std::cout << "N:	" << "	T[ms]	" << "	Stdev[ms]	 " << " Samples " << std::endl;
		std::cout << N << "		" << tempValue / samples << "		" << stdDev << "		" << samples << "\n" << std::endl;
		tempValue = 0;
	}

	return 0;
}

double calculateStandardDeviation(doubleiterator first, doubleiterator last)
{
	double sum = 0;
	double mean = 0;
	double standardDeviation = 0;
	doubleiterator temp = first;
	size_t size = last-first;

	for (; temp != last;temp++) {
		sum += *temp;
	}

	mean = sum / size;

	for (; first != last; first++) {
		standardDeviation += std::pow(*first - mean, 2);
	}

	return std::sqrt(standardDeviation/size);
}
#include <iostream>
#include "generatePrimes.h"
#include "searchAlgos.h"
#include <vector>
#include "HashTable.h"
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <chrono>
#include <fstream>

static void inorder(Node* root);
static void printVec(std::vector<int>& vec);

template<typename Func>
double benchmark(Func searchFunction, int iterations);

struct Stats {
	double average;
	double stddev;
};

static Stats calculateStats(const std::vector<double>& vec);


int main() {

	srand(time(NULL));
	const int ITERATIONS = 2000;
	double savedTimeHash = 0;
	double savedTimeLinear = 0;
	double savedTimeBinary = 0;
	double savedTimeBST = 0;

	for (int power = 3; power < 25; power++) {


		int N = std::pow(2, power) - 1;

		std::vector<int> myPrimeVec(N);

		myPrimeVec = generatePrimeNumbers(N);


		// CREATE BST
		Node* root = balancedBST(myPrimeVec.begin(), myPrimeVec.end());

		// CREATE HASH TABLE
		HashTable myHashish(N * 2);

		for (int& num : myPrimeVec)
		{
			myHashish.insert(num);
		}

		// IN ORDER TRAVERSAL OF BST
		//inorder(root);
		//printVec(myPrimeVec);

		// SEARCHING

		std::vector<double> hashVec;
		//std::vector<double> linearVec;
		std::vector<double> binaryVec;
		std::vector<double> bstVec;

		for (int i = 0; i < ITERATIONS; i++) {

			size_t randomValue = rand() % myPrimeVec[myPrimeVec.size() - 1];
			size_t searchNumber = randomValue;

			//std::cout << "\n THIS IS RANDOM VALUE:: " << randomValue << std::endl << std::endl;


			// HASH SEARCH
			//myHashish.hashTableSearch(searchNumber);

			savedTimeHash = benchmark([&]() {
				return myHashish.hashTableSearch(searchNumber);
				}, ITERATIONS);

			// LINEAR SEARCH
			//linearSearch(myPrimeVec.begin(), myPrimeVec.end(), searchNumber);

			/*
			savedTimeLinear = benchmark([&]() {
				return linearSearch(myPrimeVec.begin(), myPrimeVec.end(), searchNumber);
				}, ITERATIONS);
			*/

			// BINARY SEARCH
			//binarySearch(myPrimeVec.begin(), myPrimeVec.end(), searchNumber);

			savedTimeBinary = benchmark([&]() {
				return binarySearch(myPrimeVec.begin(), myPrimeVec.end(), searchNumber);
				}, ITERATIONS);

			// SEARCHING BST
			//Node* target = binaryTreeSearch(root, searchNumber);

			savedTimeBST = benchmark([&]() {
				return binaryTreeSearch(root, searchNumber) != nullptr;
				}, ITERATIONS);

			hashVec.push_back(savedTimeHash);
			//linearVec.push_back(savedTimeLinear);
			binaryVec.push_back(savedTimeBinary);
			bstVec.push_back(savedTimeBST);


		}

		std::ofstream outFile("resultsNoLinear.data", std::ios::app);

		//Stats linearStats = calculateStats(linearVec);
		Stats binaryStats = calculateStats(binaryVec);
		Stats bstStats = calculateStats(bstVec);
		Stats hashStats = calculateStats(hashVec);

		outFile << "N = " << N << "\n";
		//outFile << "Linear Search Avg: " << linearStats.average << " ns | StdDev: " << linearStats.stddev << " ns\n";

		outFile << "Binary Search Avg: " << binaryStats.average << " ns | StdDev: " << binaryStats.stddev << " ns\n";

		outFile << "BST Search Avg: " << bstStats.average << " ns | StdDev: " << bstStats.stddev << " ns\n";

		outFile << "Hash Search Avg: " << hashStats.average << " ns | StdDev: " << hashStats.stddev << " ns\n\n";



	}
	return 0;
}



static void printVec(std::vector<int>& vec) {

	for (auto& e : vec) {
		std::cout << e << std::endl;
	}


}

static void inorder(Node* root)
{
	if (root == nullptr)
		return;

	inorder(root->left);

	std::cout << root->value << " " << std::endl;;

	inorder(root->right);
}

template<typename Func>
double benchmark(Func searchFunction, int iterations)
{
	using namespace std::chrono;

	long long totalTime = 0;

	volatile bool found; // prevents optimization

	for (int i = 0; i < iterations; ++i)
	{
		auto start = high_resolution_clock::now();

		found = searchFunction();

		auto stop = high_resolution_clock::now();

		totalTime += duration_cast<nanoseconds>(stop - start).count();
	}

	return static_cast<double>(totalTime) / iterations;
}

static Stats calculateStats(const std::vector<double>& vec)
{
	double total = 0.0;

	for (double t : vec)
	{
		total += t;
	}

	double mean = total / vec.size();

	double variance = 0.0;

	for (double t : vec)
	{
		double diff = t - mean;
		variance += diff * diff;
	}

	variance /= (vec.size() - 1);

	return { mean, std::sqrt(variance) };
}
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
static double calculateAverage(const std::vector<double>& vec);

template<typename Func>
double benchmark(Func searchFunction);

int main() {

	srand(time(NULL));
	const int ITERATIONS = 500;
	double savedTimeHash = 0;
	double savedTimeLinear = 0;
	double savedTimeBinary = 0;
	double savedTimeBST = 0;

	for (int power = 3; power < 17; power++) {


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
		std::vector<double> linearVec;
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
				});

			// LINEAR SEARCH
			//linearSearch(myPrimeVec.begin(), myPrimeVec.end(), searchNumber);

			savedTimeLinear = benchmark([&]() {
				return linearSearch(myPrimeVec.begin(), myPrimeVec.end(), searchNumber);
				});

			// BINARY SEARCH
			//binarySearch(myPrimeVec.begin(), myPrimeVec.end(), searchNumber);

			savedTimeBinary = benchmark([&]() {
				return binarySearch(myPrimeVec.begin(), myPrimeVec.end(), searchNumber);
				});

			// SEARCHING BST
			//Node* target = binaryTreeSearch(root, searchNumber);

			savedTimeBST = benchmark([&]() {
				return binaryTreeSearch(root, searchNumber) != nullptr;
				});

			hashVec.push_back(savedTimeHash);
			linearVec.push_back(savedTimeLinear);
			binaryVec.push_back(savedTimeBinary);
			bstVec.push_back(savedTimeBST);


		}

		std::ofstream outFile("results.txt",std::ios::app);

		outFile << "N = " << N << "\n";

		outFile << "Linear Search Avg: " << calculateAverage(linearVec) << " ns\n";

		outFile << "Binary Search Avg: " << calculateAverage(binaryVec) << " ns\n";

		outFile << "BST Search Avg: " << calculateAverage(bstVec) << " ns\n";

		outFile << "Hash Search Avg: " << calculateAverage(hashVec) << " ns\n\n";

		outFile.close();




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
double benchmark(Func searchFunction)
{

		auto start = std::chrono::high_resolution_clock::now();

		bool found = searchFunction();

		auto stop = std::chrono::high_resolution_clock::now();

		auto duration = std::chrono::duration_cast<std::chrono::nanoseconds> (stop - start);


	return duration.count();
}

static double calculateAverage(const std::vector<double>& vec)
{
	double total = 0;

	for (double t : vec)
	{
		total += t;
	}

	return total / vec.size();
}
#include "timeCheck.h"


double compareAsc(iterator first, iterator last, func mySortFunc)
{
	generateAscending(first, last);

	auto start = std::chrono::steady_clock::now();
	mySortFunc(first, last);
	auto end = std::chrono::steady_clock::now();

	generateAscending(first, last);

	double time = std::chrono::duration<double, std::milli>(end - start).count();
	return time;
}

double compareDesc(iterator first, iterator last, func mySortFunc)
{
	generateDescending(first, last);

	auto start = std::chrono::steady_clock::now();
	mySortFunc(first, last);
	auto end = std::chrono::steady_clock::now();

	generateDescending(first, last);

	double time = std::chrono::duration<double, std::milli>(end - start).count();
	return time;
}

double compareRand(iterator first, iterator last, func mySortFunc)
{
	generateRandom(first, last);

	auto start = std::chrono::steady_clock::now();
	mySortFunc(first, last);
	auto end = std::chrono::steady_clock::now();

	generateRandom(first, last);

	double time = std::chrono::duration<double, std::milli>(end - start).count();
	return time;
}

double compareConst(iterator first, iterator last, func mySortFunc)
{
	generateConstant(first, last);

	auto start = std::chrono::steady_clock::now();
	mySortFunc(first, last);
	auto end = std::chrono::steady_clock::now();

	generateConstant(first, last);

	double time = std::chrono::duration<double, std::milli>(end - start).count();
	return time;
}

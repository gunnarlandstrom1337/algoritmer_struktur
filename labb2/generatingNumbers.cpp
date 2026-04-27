#include "generatingNumbers.h"
#include <iostream>

void generateDescending(iterator first, iterator last)
{
	size_t counter = 0;

	for (size_t i = last-first; counter != last-first;)
	{

		first[counter] = --i;
		counter++;
	}
}

void generateAscending(iterator first, iterator last)
{
	for (size_t i = 0; i != last-1-first; i++)
	{
		first[i] = i;
	}
}

void generateRandom(iterator first, iterator last)
{
	int MY_RANGE_MAX = 100000;
	for (size_t i = 0; i != last-1-first; i++)
	{
		first[i] = (1.0 * rand() / RAND_MAX) * MY_RANGE_MAX;
	}
}

void generateConstant(iterator first, iterator last)
{
	const int value = 7;
	for (size_t i = 0; i != last - first; i++)
	{
		first[i] = value;
	}
}

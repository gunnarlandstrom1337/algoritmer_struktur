#include "generatePrimes.h"
#include <vector>


//std::vector<int> generatePrimeNumbers(unsigned int n)
//{
//    std::vector<int> myPrimes;
//    bool isPrime;
//
//    myPrimes.push_back(2);
//    int primeCheck = 3;
//
//	while (myPrimes.size() < n) {
//        isPrime = true;
//
//		for (int i = 0; i < myPrimes.size(); i++) {
//			if (primeCheck % myPrimes[i] == 0) {
//				isPrime = false;
//				break;
//			}
//		}
//		if (isPrime) {
//			myPrimes.push_back(primeCheck);
//		}
//		primeCheck += 2;
//	}
//    return myPrimes;
//}



std::vector<int> generatePrimeNumbers(unsigned int count)
{
    if (count == 0)
        return {};

    // Guaranteed large enough for 10k+ primes
    unsigned int limit = count * 20;

    while (true)
    {
        std::vector<bool> isPrime(limit + 1, true);

        isPrime[0] = false;
        isPrime[1] = false;

        for (unsigned int i = 2; i * i <= limit; i++)
        {
            if (isPrime[i])
            {
                for (unsigned int j = i * i; j <= limit; j += i)
                {
                    isPrime[j] = false;
                }
            }
        }

        std::vector<int> primes;

        for (unsigned int i = 2; i <= limit; i++)
        {
            if (isPrime[i])
            {
                primes.push_back(i);

                if (primes.size() == count)
                    return primes;
            }
        }

        // Not enough primes? Expand and try again
        limit *= 2;
    }
}
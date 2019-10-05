#include<iostream>
#include<cmath>

using namespace std;

unsigned nthPrime(unsigned n) {
	int maxPrime = 2;
	int primeCount = 1;

	bool isPrime;
	int x = 3;

	while (primeCount < n) {
		isPrime = 1;
		for (int i = 2; i <= static_cast<int>(sqrt(x)); ++i) {
			if (x % i == 0) {
				isPrime = 0;
				break;
			}
		}

		if (isPrime == 1) {
			maxPrime = x;
			primeCount++;
		}

		x++;
	}
	
	return maxPrime;
}
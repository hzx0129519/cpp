#include <iostream>
using namespace std;

unsigned gcdFinder(unsigned a, unsigned b)
{
	if (b == 0)
		return a;
	return gcdFinder(b, a % b);

}
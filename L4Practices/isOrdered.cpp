#include<iostream>

using namespace std;

bool isOrdered(const int* v, unsigned n) {

	for (int i = 0; i < n - 1; ++i) {
		if (v[i] > v[i + 1]) return false;
	}
	return true;
}

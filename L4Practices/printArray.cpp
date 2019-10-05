#include<iostream>

using namespace std;

void printArray(const int* v, unsigned n){

	for (int i = 0; i < n; ++i) {
		cout << v[i] <<", ";
	}
}

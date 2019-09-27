#include<iostream>
#include"Header.h"


using namespace std;

int main() {
	//Problem 1
	cout << isOdd(24) << endl << endl;

	//Problem 2
	testFormula(0.3);
	cout << endl;


	//Problem 3
	int x[5] = { 10, 20, 30, 40, 50 };
	const int* v = x;
	printArray(v, 4);
	cout << endl << endl;

	//Problem 4
	cout << isOrdered(v, 4) << endl;

	return 0;
}
#if 0
cout << isOdd(24) << endl;
#endif
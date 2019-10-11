#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <stdio.h>


using namespace std;

void swapnum(int *i, int *j) {
	int* temp;
	temp = i;
	i = j;
	j = temp;
	cout << *temp << endl;
	cout << *i << endl;
	cout << *j << endl;
}

int main(void) {
	int a = 45;
	int b = 35;

	swapnum(&a, &b);
	printf("A is %d and B is %d\n", a, b);

	int x = 5;
	int* p;
	p = &x;
	int& r = x;
	cout << &p << " " << &x << endl;     
	cout << &r << " " << &x << endl;
	return 0;
}
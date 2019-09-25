#include<iostream>
#include<iomanip> // for formatting the output
#include<cmath> // for calculation 

using namespace std;

struct myArray {
	const size_t initial_size = 2;
	const size_t growth_factor = 2;
	size_t length = 0;
	size_t capacity = initial_size;

	int *v; // vector
};

int getInteger(const char* promptMsg) {
	int x;
	do {
		cout << promptMsg << endl;
		cin >> x;
	} while (cin.bad());
	return x;
}

void printArray(const myArray& n) {
	for (size_t i = 0; i < n.length; ++i)
		cout << n.v[i] << ",";
	cout << endl;
}

void growVector(myArray& n){
	int* temp = new int[n.capacity *= n.growth_factor];
	for (size_t i = 0; i < n.length; ++i)
		temp[i] = n.v[i];
	delete[] n.v;
	n.v = temp;
}

void pushBack(myArray& n, int x) {
	if (n.length == n.capacity)
		growVector(n);
	n.v[n.length++] = x;
}


int main() {
	myArray numbers;
	numbers.v = new int[numbers.capacity];
	
	while (true) {
		int x = getInteger("Please input a numebr (program terminated once a -ve number is entered)");
		if (x < 0) break;

		pushBack(numbers, x);
	}

	printArray(numbers);

	return 0;
}

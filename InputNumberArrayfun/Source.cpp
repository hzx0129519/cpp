#include<iostream>
#include<iomanip> // for formatting the output
#include<cmath> // for calculation 

using namespace std;

struct myArray {
	const size_t initial_size = 1;
	const size_t growth_factor = 2;
	size_t length = 0;
	size_t capacity = initial_size;

	int *v; // vector
};

int main() {
	int x; 
	myArray numbers;
	
	while (true) {
		cout << "Please input a numebr (program terminated once a -ve number is entered)" << endl;
		cin >> x;
		if (x < 0) 
			break;

		if (numbers.length == numbers.capacity) {
			int *temp = new int[numbers.capacity *= numbers.growth_factor];
			for (size_t i = 0; i < numbers.length; ++i)
				temp[i] = numbers.v[i];
			delete[] numbers.v;
			numbers.v = temp;
		}
		numbers.v[numbers.length++] = x;
	}

	for (size_t i = 0; i < numbers.length; ++i) 
		cout << numbers.v[i] << ",";

	cout << endl;

	return 0;
}

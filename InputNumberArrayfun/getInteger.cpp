#include <iostream>

using namespace std;

int getInteger(const char* promptMsg) {
	int x;
	do {
		cout << promptMsg << endl;
		cin >> x;
	} while (cin.bad());
	return x;
}
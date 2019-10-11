#include <iostream>
#include <algorithm>
#include "Position_n_Rect.h"
#include "Hanoi.h"
#include "Matrix.h"

using namespace std;

	int main()
	{
		//implementation of Position_n_Rect
		cout << "    Implementation of Position_n_Rect:" << endl;
		const double x= 1.4, y = 9.4;
		Position a(x,y), b(5, 2);
		Rectangle rect(a, b);

		rect.shift(2, 1);
		print("topleft of rect", rect.getTopLeft());
		cout << "width/height/area/perimeter: " << rect.width() << "/" << rect.height() << "/" << rect.area() << "/" << rect.perimeter() << endl << endl;

		//implementation of Hanoi
		cout << "    Implementation of Hanoi:" << endl;
		tower t1('a');
		tower t2('b');
		tower t3('c');
	
		const unsigned nDiscs = 3;
		t1.init(nDiscs);
		cout << move(nDiscs, t1, t2, t3) << " moves needed to solve a Hanoi with " << nDiscs << " discs" << endl << endl;

		//implementation of Matrix

		Matrix m1(3, 2, 0.0);	//use constructor 2
		Matrix m2(m1);			//use copy constructor 

		for (unsigned i = 0, n = min(m2.nRows(), m2.nColumns()); i < n; ++i)
			m2(i, i) = 1;		// use () operator overload 
		Matrix m3;				//use constructor 1
		m3 = m2;				// use = operator overload		
		m3 = m3;				// no need to do anything in this case !

		const Matrix& cm = m3;	// const reference to m3
		for (unsigned i = 0; i < cm.nRows(); ++i) {
			for (unsigned j = 0; j < cm.nColumns(); ++j) {
				cout << cm(i, j) << " "; // use () operator overload, object is a const!
			}
			cout << endl;
		}

		return 0;
	}
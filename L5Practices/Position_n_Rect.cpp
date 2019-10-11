#include "Position_n_Rect.h"
#include <iostream>
using namespace std;

// Position class 
	double Position::getX() const { return m_x; }
	double Position::getY() const { return m_y; }

	void Position::set(double x, double y) { m_x = x; m_y = y; }

// Rectangle class
	double Rectangle::width() const { return (m_bottomRight.getX() - m_topLeft.getX()); }
	double Rectangle::height() const { return (m_topLeft.getY() - m_bottomRight.getY()); }
	double Rectangle::area() const { return width() * height(); }
	double Rectangle::perimeter() const { return 2 * (width() + height()); }
	Position Rectangle::getTopLeft() const { return m_topLeft; }
	Position Rectangle::getBottomRight() const { return m_bottomRight; }

	void Rectangle::shift(int dx, int dy) {
		m_bottomRight.set(m_bottomRight.getX() + dx, m_bottomRight.getY() + dy);
		m_topLeft.set(m_topLeft.getX() + dx, m_topLeft.getY()+ dy);
	}
// Outside class function
void print(const char* name, const Position& p) {
		cout << name << ":(" << p.getX() << "," << p.getY() << ")" << endl;
	}
#pragma once

// Position class dealing with a pair of x,y 
class Position {
	double m_x, m_y;
public:
	Position() : m_x(0), m_y(0) {};						//constructor
	Position(double x, double y) : m_x(x), m_y(y) {};	
	double getX() const;								//read-only function
	double getY() const;								
	void set(double x, double y);						//modifier function
};

//Print coordination function 
void print(const char* name, const Position& p);

// Rectangle class dealing with 2 positions 
class Rectangle {
	Position m_topLeft, m_bottomRight;

public:
	
	Rectangle(const Position& topLeft, const Position& bottomRight)	// constructor
		: m_topLeft(topLeft)
		, m_bottomRight(bottomRight)
	{}
	Rectangle(const Position& topLeft, int width, int height)
		: m_topLeft(topLeft)
		, m_bottomRight(topLeft.getX() + width, topLeft.getY() - height)
	{}

	double width() const;			//read-only functions 
	double height() const;
	double area() const;
	double perimeter() const;
	Position getTopLeft() const;
	Position getBottomRight() const;

	void shift(int dx, int dy);		//modifiers methods
};
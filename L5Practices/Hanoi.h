#pragma once
#include <stack>
using namespace std;

class tower {
	char m_towerID;
	std::stack<unsigned> m_slots;

public:
	tower(char id) : m_towerID(id) {}

	void push(unsigned discID) { m_slots.push(discID); }
	void pop() { m_slots.pop(); }
	void init(unsigned nDiscs) {
		for (unsigned i = 0; i < nDiscs; i++) this->push(nDiscs -i);
	}

	char name() const { return m_towerID; }	//read-only
	unsigned top() const { return m_slots.top(); } //read-only
	unsigned size() const { return m_slots.size(); }
};

unsigned move(unsigned nDiscs, tower& t1, tower& t2, tower& t3) {
	unsigned nMoves = 0; 
	if (nDiscs > 1) {
		nMoves += move(nDiscs - 1, t1, t3, t2);
		nMoves += move(1, t1, t2, t3);
		nMoves += move(nDiscs - 1, t3, t2, t1);
	}
	else {
		unsigned discID = t1.top();
		t1.pop();
		t2.push(discID);
		++nMoves;
		cout << "Disc " << discID << " moves "
			<< t1.name() << "-->" << t2.name()
			<< endl;
	}
	return nMoves;
}
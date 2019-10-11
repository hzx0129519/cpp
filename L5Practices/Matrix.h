#pragma once
#include <cstring>

using namespace std;

class Matrix
{
	double* m_data;
	unsigned m_nRows, m_nCols;
	unsigned index(unsigned i, unsigned j) const { return (i * m_nCols + j); }

public:
	// default constructor 1
	Matrix() : m_nRows(0), m_nCols(0), m_data(NULL) {}

	// another constructor 2 
	Matrix(unsigned m, unsigned n, double val)
		: m_nRows(m)
		, m_nCols(n)
		, m_data(new double[m * n])
	{
		for (double* p = m_data; p != (m_data + m * n); ++p)
			* p = val;
	}

	// copy constructor
	Matrix(const Matrix& mat)
		: m_nRows(mat.m_nRows)
		, m_nCols(mat.m_nCols)
		, m_data(new double[mat.m_nRows * mat.m_nCols])
	{
		unsigned nBytesToCopy = sizeof(double) * mat.m_nRows * mat.m_nCols;
		memcpy(m_data, mat.m_data, nBytesToCopy);
	}

	// destructor
	~Matrix() { delete[] m_data; }

	unsigned nRows() const { return m_nRows; }
	unsigned nColumns() const { return m_nCols; }

	// ()operater overload
	double& operator()(unsigned i, unsigned j) { return m_data[index(i, j)]; }	//read and write
	const double& operator()(unsigned i, unsigned j) const { return m_data[index(i, j)]; }	//read only

	// =operator overload
	Matrix& operator= (const Matrix& mat) {
		if (this != &mat) {
			delete[] m_data;	//release memory 
			m_data = NULL;		//for saftety
			m_data = new double[mat.m_nRows * mat.m_nCols];
			m_nRows = mat.m_nRows;
			m_nCols = mat.m_nCols;
			unsigned nBytesToCopy = sizeof(double) * mat.m_nRows * mat.m_nCols;
			memcpy(m_data, mat.m_data, nBytesToCopy);
		}
		return *this;
	}
};

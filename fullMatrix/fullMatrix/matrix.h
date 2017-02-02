// header guard
#ifndef MATRIX_H
#define MATRIX_H

#include <fstream>

class Matrix
{
private:
	int rows;
	int cols;
	int **mat;

	// helper function
	void initializeMatrix(int rows, int cols);

public:
	Matrix();
	Matrix(int r, int c);
	Matrix(const char* filename);

	// copy constructor
	Matrix(const Matrix& m);

	// TODO: define operator=
	// mult function
	Matrix mult(const Matrix& b);

	// output func
	void print() const;

	// destructor
	~Matrix();
};

#endif
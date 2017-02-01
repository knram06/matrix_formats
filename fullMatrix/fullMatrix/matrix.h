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
	Matrix(std::ifstream& inputFh, const char* filename);

};

#endif